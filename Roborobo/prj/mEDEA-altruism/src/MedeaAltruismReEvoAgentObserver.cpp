/*
 *  MedeaAltruismReEvoAgentObserver.cpp
 *  Roborobo
 *
 *  imported from Jean-Marc on 15/12/09
 *  current dev: Nicolas on 1/4/2009
 *  modification for ReEvo : Jean-Marc 2/4/2011
 *
 */


#include "mEDEA-altruism/include/MedeaAltruismReEvoAgentObserver.h"

#include "World/World.h"
#include "Utilities/Misc.h"
#include "RoboroboMain/roborobo.h"
#include "mEDEA-altruism/include/MedeaAltruismPerceptronControlArchitecture.h"
#include <cmath>


#include "mEDEA-altruism/include/MedeaAltruismReEvoWorldObserver.h"
#include "mEDEA-altruism/include/MedeaAltruismSharedData.h"


// *** *** *** *** ***


MedeaAltruismReEvoAgentObserver::MedeaAltruismReEvoAgentObserver( RobotAgentWorldModel *__wm )
{
	_wm = (MedeaAltruismAgentWorldModel*)__wm;

	_wm->_minValue = -3.0;
	_wm->_maxValue = 3.0;

	_wm->_currentSigma = MedeaAltruismSharedData::gSigmaRef;
	_wm->_genomesList.clear();
	_wm->_sigmaList.clear();

	gProperties.checkAndGetPropertyValue("nbHiddenNeurons",&_wm->_nbHiddenNeurons,true);
	gProperties.checkAndGetPropertyValue("gNbMaxGenomeSelection",&nbMaxGenomeSelection,true);
	
	_wm->resetActiveGenome();
	
	if ( gVerbose )
	{
		std::cout << "robot #" << _wm->_agentId << "\n" ;	
	}
}

MedeaAltruismReEvoAgentObserver::~MedeaAltruismReEvoAgentObserver()
{
	// nothing to do.
}

void MedeaAltruismReEvoAgentObserver::reset()
{
	// nothing to do 
}

void MedeaAltruismReEvoAgentObserver::step()
{
	// log the state of the initialization
	if( gWorld->getIterations() == 0 ) 
	{
		if (_wm->getActiveStatus() == false )
		{
				gLogFile << gWorld->getIterations() << " : robot nb." << _wm->_agentId
								 << " is waiting for a new genome" << std::endl;
		}
		else
		{
				gLogFile << gWorld->getIterations() <<" : "<< _wm->_agentId << " use ";
				for(unsigned int i=0; i<_wm->_currentGenome.size(); i++)
				{
					gLogFile << std::fixed << std::showpoint << _wm->_currentGenome[i] << " ";
				}
				gLogFile << std::endl;
		}
	}

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
				MedeaAltruismReEvoAgentObserver* targetAgentObserver = dynamic_cast<MedeaAltruismReEvoAgentObserver*>(gWorld->getAgent(i)->getObserver());
				if ( ! targetAgentObserver )
				{
					std::cerr << "Error from robot " << _wm->_agentId << " : the observer of robot " << i << " isn't a SwarmOnlineObserver" << std::endl;
					exit(1);
				}
				if ( MedeaAltruismSharedData::gDynamicSigma == true )
				{
					float dice = float(rand() %100) / 100.0;
					float sigmaSendValue = 0.0;
					if ( ( dice >= 0.0 ) && ( dice < MedeaAltruismSharedData::gProbAdd) )
					{
						sigmaSendValue = _wm->_currentSigma * ( 1 + MedeaAltruismSharedData::gDynaStep );
						if (sigmaSendValue > MedeaAltruismSharedData::gSigmaMax)
						{
							sigmaSendValue = MedeaAltruismSharedData::gSigmaMax;
						}
					}
					else if ( ( dice >= MedeaAltruismSharedData::gProbAdd ) && ( dice < MedeaAltruismSharedData::gProbAdd+MedeaAltruismSharedData::gProbSub) )
					{
						sigmaSendValue = _wm->_currentSigma * ( 1 - MedeaAltruismSharedData::gDynaStep );
						if (sigmaSendValue < MedeaAltruismSharedData::gSigmaMin)
						{
							sigmaSendValue = MedeaAltruismSharedData::gSigmaMin;
						}
					}
					else
					{
						std::cerr << "Error : In SwarmOnlineObserver, the rand value is out of bound. The sum of MedeaAltruismSharedData::gProbRef and MedeaAltruismSharedData::gProbMax is probably not equal to one" << std::endl;
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

	if( dynamic_cast<MedeaAltruismReEvoWorldObserver*>(gWorld->getWorldObserver())->getLifeIterationCount() >= MedeaAltruismSharedData::gEvaluationTime-1 ) // at the end of a generation
	{
		if (_wm->_agentId == gAgentIndexFocus && gVerbose) // debug
		{
			std::cout << "agent #" << gAgentIndexFocus << " is renewed" << std::endl;
			std::cout << "agent #" << gAgentIndexFocus << " imported " << _wm->_genomesList.size() << " genomes. Energy is " << _wm->getEnergyLevel() << ". Status is "  << _wm->getActiveStatus() << "." <<std::endl;
		}

		// Display the current state of the controller
		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId
				 << " Energy " <<  _wm->getEnergyLevel()
				 << " DeltaE " << _wm->getDeltaEnergy()
				 << " GenomeListSize " << _wm->_genomesList.size() <<std::endl;
			
		// note: at this point, agent got energy, wether because it was revived or because of remaining energy.
		if (_wm->getWaitingAfterLifeSynchronization() == false )
		{
			if (_wm->_genomesList.size() > 0)
			{
				// case: 1+ genome(s) imported, random pick.
				
				//randomElitismGenomeSelection();
				//tournamentGenomeSelection();
				pickRandomGenome();
				_wm->setActiveStatus(true); // !N.20100407 : revive takes imported genome if any
			}
			else
			{
				// case: no imported genome - wait for new genome.
				
				gLogFile << gWorld->getIterations() << " : robot nb." << _wm->_agentId
									<< " is waiting for a new genome" << std::endl;

				_wm->resetActiveGenome(); // optional -- could be set to zeroes.
				_wm->setActiveStatus(false); // inactive robot *must* import a genome from others (ie. no restart).
			}
			
			//log the genome
			
			if ( _wm->getActiveStatus() == true )
			{
				gLogFile << gWorld->getIterations() <<" : "<< _wm->_agentId << " use ";
				for(unsigned int i=0; i<_wm->_currentGenome.size(); i++)
				{
					gLogFile << std::fixed << std::showpoint << _wm->_currentGenome[i] << " ";
				}
				gLogFile << std::endl;
			}
		}
		else
		{
			gLogFile << gWorld->getIterations() << " : "<< _wm->_agentId << " listen" << std::endl;
			_wm->setWaitingAfterLifeSynchronization(false);
			_wm->setActiveStatus(false);
			_wm->_genomesList.clear();
			_wm->_sigmaList.clear();
		}

		//Re-initialize the main parameters

		_wm->setDeltaEnergy(0.0); 
	}	
}

void MedeaAltruismReEvoAgentObserver::loadGenome(std::vector<double> inGenome)
{
	std::cout << std::flush ;
	_wm->_currentGenome.clear();
	for ( unsigned int i = 0 ; i != inGenome.size() ; i++ )
	{
		//force egoism
		if ( i >= 75 && i <= 79 )
		{
			_wm->_currentGenome.push_back(0.0);
		}
		else if ( i == 82 ) 
		{
			_wm->_currentGenome.push_back(3.0);
		}
		else
		{
			_wm->_currentGenome.push_back(inGenome[i]);
		}
	}
	_wm->setNewGenomeStatus(true);
}


void MedeaAltruismReEvoAgentObserver::randomElitismGenomeSelection()
{
		if(_wm->_genomesList.size() != 0)
		{
			std::map<int, double> genotypicRelatedness;
			//compute the genotypic relatedness with the current genome for each genome in the list
			for (std::map<int, std::vector<double> >::iterator it = _wm->_genomesList.begin() ; it != _wm->_genomesList.end() ; it++)
			{
				double distance=0.0;
				for(unsigned int i=0;i < it->second.size() ; i++)
				{
					distance += pow(_wm->_currentGenome[i]-it->second[i],2);
				}
				distance = sqrt(distance) ;
				if (genotypicRelatedness.size() < unsigned(nbMaxGenomeSelection) )
				{
					genotypicRelatedness[it->first] = distance;
				}
				else
				{
					double highest = distance;
					int idHighest = it->first;
					//search if there is one genome with a highest genotypic distance
					for (std::map<int,double>::iterator itSearchHighest = genotypicRelatedness.begin() ; itSearchHighest != genotypicRelatedness.end() ; itSearchHighest++)
					{
						if (itSearchHighest->second > highest)
						{
							highest = itSearchHighest->second;
							idHighest = itSearchHighest->first;
						}
					}
					if (idHighest != it->first )
					{
						genotypicRelatedness.erase(idHighest);
						genotypicRelatedness[it->first] = distance;
					}
				}
			}

			//random selection
			int randomIndex = rand()%genotypicRelatedness.size();
			std::map<int, double>::iterator itRandom = genotypicRelatedness.begin();
			while (randomIndex !=0 )
			{
				itRandom ++;
				randomIndex --;
			}

			_wm->_currentGenome = _wm->_genomesList[itRandom->first];
			if ( MedeaAltruismSharedData::gDynamicSigma == true )
			{
				mutateWithBouncingBounds(_wm->_sigmaList[itRandom->first]);
			}
			else
			{
				mutateWithBouncingBounds(-1.00);
			}
			
			_wm->setNewGenomeStatus(true); 
			gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " take " << itRandom->first << std::endl;
			
			if (_wm->_agentId == 1 && gVerbose) // debug
				std::cout << "  Sigma is " << _wm->_sigmaList[itRandom->first] << "." << std::endl;
			
			
			_wm->_genomesList.clear();
			_wm->_sigmaList.clear();
		}
}

void MedeaAltruismReEvoAgentObserver::tournamentGenomeSelection()
{
		if(_wm->_genomesList.size() != 0)
		{
			std::map<int, std::vector<double> > genomesSample;

			//random selection
			int genomesListSize = _wm->_genomesList.size();
			for (int i = 0 ; (i< nbMaxGenomeSelection) && (i < genomesListSize) ; i++)
			{
				int randomIndex = rand()%_wm->_genomesList.size();
				std::map<int, std::vector<double> >::iterator itRandom = _wm->_genomesList.begin();
				while (randomIndex !=0 )
				{
					itRandom ++;
					randomIndex --;
				}
				genomesSample[itRandom->first] = itRandom->second;
				_wm->_genomesList.erase(itRandom);
			}

			//find the closest genome in the genome sample
			double lowest = 0.0;
			std::map<int, std::vector<double> >::iterator it = genomesSample.begin(); 
			for(unsigned int i=0;i < it->second.size() ; i++)
			{
				lowest += pow(_wm->_currentGenome[i]-it->second[i],2);
			}
			lowest = sqrt(lowest);
			int idLowest = it->first;
			it++;
			for ( ; it != genomesSample.end() ; it++)
			{
				double distance=0.0;
				for(unsigned int i=0;i < it->second.size() ; i++)
				{
					distance += pow(_wm->_currentGenome[i]-it->second[i],2);
				}
				distance = sqrt(distance);
				if ( distance < lowest)
				{
					lowest = distance;
					idLowest = it->first;
				}
			}

			_wm->_currentGenome = genomesSample[idLowest];
			if ( MedeaAltruismSharedData::gDynamicSigma == true )
			{
				mutateWithBouncingBounds(_wm->_sigmaList[idLowest]);
			}
			else
			{
				mutateWithBouncingBounds(-1.00);
			}
			_wm->setNewGenomeStatus(true); 
			_wm->_genomesList.clear();
			_wm->_sigmaList.clear();

			gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " take " << idLowest << std::endl;
			if (_wm->_agentId == 1 && gVerbose) // debug
					std::cout << "  Sigma is " << _wm->_sigmaList[idLowest] << "." << std::endl;

		}
}

void MedeaAltruismReEvoAgentObserver::pickRandomGenome()
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
			if ( MedeaAltruismSharedData::gDynamicSigma == true )
			{
				mutateWithBouncingBounds(_wm->_sigmaList[(*it).first]);
			}
			else
			{
				mutateWithBouncingBounds(-1.00);
			}
			
			_wm->setNewGenomeStatus(true); 
			gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " take " << (*it).first << std::endl;
			
			if (_wm->_agentId == 1 && gVerbose) // debug
				std::cout << "  Sigma is " << _wm->_sigmaList[(*it).first] << "." << std::endl;
			
			
			_wm->_genomesList.clear();
			_wm->_sigmaList.clear();
		}
}



void MedeaAltruismReEvoAgentObserver::writeGenome(std::vector<double> genome, int senderId, float sigma)
{
	//if (_wm->_genomesList.size() < 1)
	//{
	_wm->_genomesList[senderId] = genome;
	if ( MedeaAltruismSharedData::gDynamicSigma == true)
	{
		_wm->_sigmaList[senderId] = sigma;
	}
	//}
	/*
	if (_wm->_agentId ==  gAgentIndexFocus ) // debug
	{
		std::cout << "agent #"  << gAgentIndexFocus << " list size is " << _wm->_genomesList.size() << std::endl;
	}
    */
}


void MedeaAltruismReEvoAgentObserver::mutateWithBouncingBounds( float sigma)
{
	if ( MedeaAltruismSharedData::gDynamicSigma == true)
	{
		_wm->_currentSigma = sigma;
	}
	else
	{
		float randValue = float(rand() %100) / 100.0;
		if ( ( randValue >= 0.0 ) && ( randValue < MedeaAltruismSharedData::gProbRef) )
		{
			_wm->_currentSigma = MedeaAltruismSharedData::gSigmaRef;
		}
		else if ( ( randValue >= MedeaAltruismSharedData::gProbRef ) && ( randValue < MedeaAltruismSharedData::gProbMax+MedeaAltruismSharedData::gProbRef) )
		{
			_wm->_currentSigma = MedeaAltruismSharedData::gSigmaMax;
		}
		else
		{
			std::cerr << "Error : In SwarmOnlineObserver, the rand value is out of bound. The sum of MedeaAltruismSharedData::gProbRef and MedeaAltruismSharedData::gProbMax is probably not equal to one" << std::endl;
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
		
		_wm->_currentGenome[i] = value;
	}
	
	gLogFile << std::fixed << std::showpoint << gWorld->getIterations() << " : " << _wm->_agentId << " sigma " << _wm->_currentSigma << std::endl;
}
