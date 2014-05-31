/*
 *  MedeaAltUtilityAgentObserver.cpp
 *  Roborobo
 *
 *  imported from Jean-Marc on 15/12/09
 *  current dev: Nicolas on 1/4/2009
 *
 */


#include "mEDEA-altruism-utility/include/MedeaAltUtilityAgentObserver.h"

#include "World/World.h"
#include "Utilities/Misc.h"
#include "RoboroboMain/roborobo.h"
#include "mEDEA-altruism-utility/include/MedeaAltUtilityPerceptronControlArchitecture.h"
#include <cmath>


#include "mEDEA-altruism-utility/include/MedeaAltUtilityWorldObserver.h"


// *** *** *** *** ***


MedeaAltUtilityAgentObserver::MedeaAltUtilityAgentObserver( RobotAgentWorldModel *__wm )
{
	_wm = (MedeaAltUtilityAgentWorldModel*)__wm;

	_wm->_minValue = -1.0;
	_wm->_maxValue = 1.0;

	_wm->_currentSigma = MedeaAltUtilitySharedData::gSigmaRef;

	gProperties.checkAndGetPropertyValue("nbHiddenNeurons",&_wm->_nbHiddenNeurons,true);
	
	_wm->resetActiveGenome();
	
	if ( gVerbose )
	{
		std::cout << "robot #" << _wm->_agentId << "\n" ;	
	}
}

MedeaAltUtilityAgentObserver::~MedeaAltUtilityAgentObserver()
{
	// nothing to do.
}

void MedeaAltUtilityAgentObserver::reset()
{
	// nothing to do 
}

void MedeaAltUtilityAgentObserver::step()
{
	// debug verbose
	if ( gVerbose && gInspectAgent && gAgentIndexFocus == _wm->_agentId )
	{
		std::cout << "target: " << _wm->getEnergyPointDirectionAngleValue() << std::endl;
	}

	// * genome spreading (current agent broadcasts its genome to all neighbors - ie. write its own genome in genomeList on neighboring agents)
	// note: could be move in WorldObserver to go from N^2 to Summation(N) complexity
	
	if ( _wm->getActiveStatus() == true )  	// broadcast only if agent is active (ie. not just revived) and deltaE>0.
	{
		for (int i = 0 ; i < gAgentCounter ; i++)
		{
			if ( ( i != _wm->_agentId ) && ( gRadioNetworkArray[_wm->_agentId][i] ) ) //&& (_wm->getEnergyLevel() > 0.0) ) --> always true as status is active
			{
				MedeaAltUtilityAgentObserver* targetAgentObserver = dynamic_cast<MedeaAltUtilityAgentObserver*>(gWorld->getAgent(i)->getObserver());
				if ( ! targetAgentObserver )
				{
					std::cerr << "Error from robot " << _wm->_agentId << " : the observer of robot " << i << " isn't a MedeaAltUtilityObserver" << std::endl;
					exit(1);
				}
				if ( MedeaAltUtilitySharedData::gDynamicSigma == true )
				{
					float dice = float(rand() %100) / 100.0;
					float sigmaSendValue = 0.0;
					if ( ( dice >= 0.0 ) && ( dice < MedeaAltUtilitySharedData::gProbAdd) )
					{
						sigmaSendValue = _wm->_currentSigma * ( 1 + MedeaAltUtilitySharedData::gDynaStep );
						if (sigmaSendValue > MedeaAltUtilitySharedData::gSigmaMax)
						{
							sigmaSendValue = MedeaAltUtilitySharedData::gSigmaMax;
						}
					}
					else if ( ( dice >= MedeaAltUtilitySharedData::gProbAdd ) && ( dice < MedeaAltUtilitySharedData::gProbAdd+MedeaAltUtilitySharedData::gProbSub) )
					{
						sigmaSendValue = _wm->_currentSigma * ( 1 - MedeaAltUtilitySharedData::gDynaStep );
						if (sigmaSendValue < MedeaAltUtilitySharedData::gSigmaMin)
						{
							sigmaSendValue = MedeaAltUtilitySharedData::gSigmaMin;
						}
					}
					else
					{
						std::cerr << "Error : In SwarmOnlineObserver, the rand value is out of bound. The sum of MedeaAltUtilitySharedData::gProbRef and MedeaAltUtilitySharedData::gProbMax is probably not equal to one" << std::endl;
						exit(1);
					}
					targetAgentObserver->writeGenome(_wm->_currentGenome, _wm->_agentId, sigmaSendValue);
				}
				else
				{
					targetAgentObserver->writeGenome(_wm->_currentGenome, _wm->_agentId, _wm->_currentSigma);
				}
			}
		}
	}

	// * Genome selection/replacement

	if( dynamic_cast<MedeaAltUtilityWorldObserver*>(gWorld->getWorldObserver())->getLifeIterationCount() >= MedeaAltUtilitySharedData::gEvaluationTime-1 ) // at the end of a generation
	{
		if (_wm->_agentId == gAgentIndexFocus && gVerbose) // debug
		{
			std::cout << "agent #" << gAgentIndexFocus << " is renewed" << std::endl;
			std::cout << "agent #" << gAgentIndexFocus << " imported " << _wm->_genomesList.size() << " genomes. Energy is " << _wm->getEnergyLevel() << ". Status is "  << _wm->getActiveStatus() << "." <<std::endl;
		}

		// Display the current state of the controller
		gLogFile << gWorld->getIterations() << " : #Robot: " << _wm->_agentId
				 << " #Energy: " <<  _wm->getEnergyLevel()
				 << " #DeltaEnergy: " << _wm->getDeltaEnergy()
				 << " #GenomeListSize: " << _wm->_genomesList.size() 
				 << " #TotalEnergyHarvested: " << _wm->getTotalEnergyHarvested() <<std::endl;
			
		// note: at this point, agent got energy, wether because it was revived or because of remaining energy.
		if (_wm->getWaitingAfterLifeSynchronization() == false )
		{
			if (_wm->_genomesList.size() > 0)
			{
				// case: 1+ genome(s) imported, random pick.
				
				pickRandomGenome();
				_wm->setActiveStatus(true); // !N.20100407 : revive takes imported genome if any
			}
			else
			{
				// case: no imported genome - wait for new genome.
				
				gLogFile << gWorld->getIterations() << " : robot nb." << _wm->_agentId
				//					<< " is trying a whole new genome" << std::endl;
									<< " is waiting for a new genome" << std::endl;

				_wm->resetActiveGenome(); // optional -- could be set to zeroes.
				_wm->setActiveStatus(false); // inactive robot *must* import a genome from others (ie. no restart).
			}
			
			//log the genome
			
			if ( _wm->getActiveStatus() == true )
			{
				gLogFile << gWorld->getIterations() <<" : robot nb."<< _wm->_agentId << " use genome :";
				for(unsigned int i=0; i<_wm->_genome.size(); i++)
				{
					gLogFile << std::fixed << std::showpoint << _wm->_genome[i] << " ";
				}
				gLogFile << std::endl;
			}
		}
		else
		{
			gLogFile << gWorld->getIterations() << " : robot nb."<< _wm->_agentId << " was waiting for synchronisation. Now ready to load genomes" << std::endl;
			_wm->setWaitingAfterLifeSynchronization(false);
			_wm->setActiveStatus(false);
			_wm->_genomesList.clear();
		}

		//Re-initialize the main parameters

		if ( MedeaAltUtilitySharedData::gExperimentNumber == 1 || MedeaAltUtilitySharedData::gExperimentNumber == 2 )
		{
			_wm->setDeltaEnergy(0.0); // !n : used to be 10.0
		}
		_wm->resetTotalEnergyHarvested();
	}	
}



void MedeaAltUtilityAgentObserver::pickRandomGenome()
{
		if(_wm->_genomesList.size() != 0)
		{
			int randomIndex = rand()%_wm->_genomesList.size();
			std::map<int, std::vector<double> >::iterator it = _wm->_genomesList.begin();
			while (randomIndex !=0 )
			{
				it ++;
				randomIndex --;
			}

			_wm->_currentGenome = (*it).second;
			if ( MedeaAltUtilitySharedData::gDynamicSigma == true )
			{
				mutateWithBouncingBounds(_wm->_sigmaList[(*it).first]);
			}
			else
			{
				mutateWithBouncingBounds(-1.00);
			}
			
			_wm->setNewGenomeStatus(true); 
			gLogFile << gWorld->getIterations() << " : robot nb." << _wm->_agentId << " take the genome from the robot nb." << (*it).first << std::endl;
			
			if (_wm->_agentId == 1 && gVerbose) // debug
				std::cout << "  Sigma is " << _wm->_sigmaList[(*it).first] << "." << std::endl;
			
			
			_wm->_genomesList.clear();
		}
}



void MedeaAltUtilityAgentObserver::writeGenome(std::vector<double> genome, int senderId, float sigma)
{
	_wm->_genomesList[senderId] = genome;
	if ( MedeaAltUtilitySharedData::gDynamicSigma == true)
	{
		_wm->_sigmaList[senderId] = sigma;
	}
	/*
	if (_wm->_agentId ==  gAgentIndexFocus ) // debug
	{
		std::cout << "agent #"  << gAgentIndexFocus << " list size is " << _wm->_genomesList.size() << std::endl;
	}
    */
}


void MedeaAltUtilityAgentObserver::mutateWithBouncingBounds( float sigma)
{
	_wm->_genome.clear();
	
	if ( MedeaAltUtilitySharedData::gDynamicSigma == true)
	{
		_wm->_currentSigma = sigma;
	}
	else
	{
		float randValue = float(rand() %100) / 100.0;
		if ( ( randValue >= 0.0 ) && ( randValue < MedeaAltUtilitySharedData::gProbRef) )
		{
			_wm->_currentSigma = MedeaAltUtilitySharedData::gSigmaRef;
		}
		else if ( ( randValue >= MedeaAltUtilitySharedData::gProbRef ) && ( randValue < MedeaAltUtilitySharedData::gProbMax+MedeaAltUtilitySharedData::gProbRef) )
		{
			_wm->_currentSigma = MedeaAltUtilitySharedData::gSigmaMax;
		}
		else
		{
			std::cerr << "Error : In SwarmOnlineObserver, the rand value is out of bound. The sum of MedeaAltUtilitySharedData::gProbRef and MedeaAltUtilitySharedData::gProbMax is probably not equal to one" << std::endl;
			exit(1);
		}
	}
	
	for (unsigned int i = 0 ; i != _wm->_currentGenome.size() ; i++ )
	{
		double value = _wm->_currentGenome[i] + getGaussianRand(0,_wm->_currentSigma);
		// bouncing upper/lower bounds
		if ( value < _wm->_minValue )
		{
			double range = _wm->_maxValue - _wm->_minValue;
			double overflow = - ( (double)value - _wm->_minValue );
			overflow = overflow - 2*range * (int)( overflow / (2*range) );
			if ( overflow < range )
				value = _wm->_minValue + overflow;
			else // overflow btw range and range*2
				value = _wm->_minValue + range - (overflow-range);
		}
		else
			if ( value > _wm->_maxValue )
			{
				double range = _wm->_maxValue - _wm->_minValue;
				double overflow = (double)value - _wm->_maxValue;
				overflow = overflow - 2*range * (int)( overflow / (2*range) );
				if ( overflow < range )
					value = _wm->_maxValue - overflow;
				else // overflow btw range and range*2
					value = _wm->_maxValue - range + (overflow-range);
			}
		
		_wm->_genome.push_back(value);
	}
	
	_wm->_currentGenome = _wm->_genome;
	gLogFile << std::fixed << std::showpoint << gWorld->getIterations() << " : robot nb." << _wm->_agentId << " has mutate the genome with sigma : " << _wm->_currentSigma << std::endl;
}
