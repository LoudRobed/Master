/*
 *  MedeaAltruismAgentObserver.cpp
 *  Roborobo
 *
 *  imported from Jean-Marc on 15/12/09
 *  current dev: Nicolas on 1/4/2009
 *
 */


#include "mEDEA-altruism/include/MedeaAltruismAgentObserver.h"

#include "World/World.h"
#include "Utilities/Misc.h"
#include "RoboroboMain/roborobo.h"
#include "mEDEA-altruism/include/MedeaAltruismPerceptronControlArchitecture.h"
#include <cmath>


#include "mEDEA-altruism/include/MedeaAltruismWorldObserver.h"


// *** *** *** *** ***


MedeaAltruismAgentObserver::MedeaAltruismAgentObserver( RobotAgentWorldModel *__wm )
{
	_wm = (MedeaAltruismAgentWorldModel*)__wm;

	_wm->_minValue = -0.0;
	_wm->_maxValue = 0.0;

	_wm->_currentSigma = MedeaAltruismSharedData::gSigmaRef;
	_wm->setLifeTime(1);
	_wm->setWaitForGenome(true);
	_wm->setActiveStatus(true);
	_wm->_genomesList.clear();
	_wm->_sigmaList.clear();

	gProperties.checkAndGetPropertyValue("nbHiddenNeurons",&_wm->_nbHiddenNeurons,true);
	gProperties.checkAndGetPropertyValue("gNbMaxGenomeSelection",&nbMaxGenomeSelection,true);
	
	_wm->resetActiveGenome();
	_wm->setMaturity(0);
	_wm->_idlenessTracker.reset();
	
	if ( gVerbose )
	{
		std::cout << "robot #" << _wm->_agentId << "\n" ;	
	}
}

MedeaAltruismAgentObserver::~MedeaAltruismAgentObserver()
{
	// nothing to do.
}

void MedeaAltruismAgentObserver::reset()
{
	_wm->_idlenessTracker.reset();
}

void MedeaAltruismAgentObserver::step()
{
	// debug verbose
	if ( gVerbose && gInspectAgent && gAgentIndexFocus == _wm->_agentId )
	{
		std::cout << "target: " << _wm->getEnergyPointDirectionAngleValue() << std::endl;
	}

	// at the end of a generation
	if( 
		(_wm->getLifeTime() >= MedeaAltruismSharedData::gEvaluationTime && _wm->getWaitForGenome() && !(_wm->getActiveStatus()))
		||
		(_wm->getLifeTime() >= MedeaAltruismSharedData::gEvaluationTime && _wm->getActiveStatus())
	) 
	{		
		//display area covered only if agent active at the end of its evaluation time (end of generation)
		if (_wm->getLifeTime() >= MedeaAltruismSharedData::gEvaluationTime && _wm->getActiveStatus())
		{
			gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " lf " << _wm->getLifeTime() << std::endl;
			gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " a " << (_wm->_idlenessTracker.getAverageBoxesIdleness() / _wm->getLifeTime()) * 100000 << std::endl;
		}
		checkGenomeList(); //here we look if the genome list is empty. If yes, the robot will wait again during a generation, 
		_wm->setLifeTime(0);//if not the robot will be activated and able to move again. a both case it'll stay in this state during a generation, that's why lifetime is set back to 0.
		_wm->_idlenessTracker.reset();
	}
	
	// at the end of the dead time (maby redondancy between control variables), the robot state should be in a listened mode (waitforgeneome)
	if(_wm->getLifeTime() >= (MedeaAltruismSharedData::gEvaluationTime*MedeaAltruismSharedData::gDeadTime) && !(_wm->getWaitForGenome()) && !(_wm->getActiveStatus()))
	{
		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " listen" << std::endl;
		_wm->setWaitForGenome(true);
		_wm->setLifeTime(0);
		_wm->_idlenessTracker.reset();
	}
	
	//handle the maturity concept
	if( _wm->getActiveStatus() && _wm->getMaturity() > 0)
	{
		_wm->setMaturity(_wm->getMaturity()+1);
		//gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " m" << _wm->getMaturity() << " : " << MedeaAltruismSharedData::gEnergyRevive << std::endl;
		if(_wm->getMaturity() > MedeaAltruismSharedData::gEnergyRevive +10 )
		{
			_wm->setMaturity(0); //the robot will be able to spread its genome again
			//gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " mature" << std::endl;
		}
		
	}


// broadcast only if agent is active and mature 
	if ( _wm->getActiveStatus() == true && _wm->getMaturity()<=0)
	{
		for (int i = 0 ; i < gAgentCounter ; i++)
		{
			if ( ( i != _wm->_agentId ) && ( gRadioNetworkArray[_wm->_agentId][i] ) ) //&& (_wm->getEnergyLevel() > 0.0) ) --> always true as status is active
			{
				MedeaAltruismAgentObserver* targetAgentObserver = dynamic_cast<MedeaAltruismAgentObserver*>(gWorld->getAgent(i)->getObserver());
				if ( ! targetAgentObserver )
				{
					std::cerr << "Error from robot " << _wm->_agentId << " : the observer of robot " << i << " isn't a SwarmOnlineObserver" << std::endl;
					exit(1);
				}

				if((targetAgentObserver->_wm->getActiveStatus() ) || targetAgentObserver->_wm->getWaitForGenome())
				{
					//gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " transmit to " << targetAgentObserver->_wm->_agentId << std::endl;
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
						targetAgentObserver->writeGenome(_wm->_currentGenome, _wm->_agentId + 1000 * _wm->getDateOfBirth(),sigmaSendValue);
					}
					else
					{
						targetAgentObserver->writeGenome(_wm->_currentGenome, _wm->_agentId + 1000 * _wm->getDateOfBirth() , _wm->_currentSigma);
					}
				}
			}
		}
	}

	_wm->setLifeTime(_wm->getLifeTime()+1);
	Point2d posRobot (_wm->_xReal, _wm->_yReal);
	if ( _wm->_idlenessTracker.addPoint(posRobot) == false )
	{
		std::cerr << "Error : Failed to add the point(" << posRobot.x << "," << posRobot.y << ") to the idlenessTracker" << std::endl;
		exit(1);
	}
}



void MedeaAltruismAgentObserver::checkGenomeList()
{

	if (_wm->_agentId == gAgentIndexFocus && gVerbose) // debug
	{
		std::cout << "agent #" << gAgentIndexFocus << " is renewed" << std::endl;
		std::cout << "agent #" << gAgentIndexFocus << " imported " << _wm->_genomesList.size() << " genomes. Energy is " << _wm->getEnergyLevel() << ". Status is "  << _wm->getActiveStatus() << "." <<std::endl;
	}

	// Display the current state of the controller
	gLogFile << gWorld->getIterations() << " : " << _wm->_agentId
			 << " E " <<  _wm->getEnergyLevel()
			 << " DE " << _wm->getDeltaEnergy()
			 << " GenomeLS " << _wm->_genomesList.size() <<std::endl;
		
	// note: at this point, agent got energy, wether because it was revived or because of remaining energy.
	if (_wm->_genomesList.size() > 0)
	{
		// case: 1+ genome(s) imported, random pick.
		
		_wm->setDateOfBirth(gWorld->getIterations());
		if (MedeaAltruismSharedData::selectionScheme.compare("randomElitism") == 0)
		{
			randomElitismGenomeSelection();
		}
		else if (MedeaAltruismSharedData::selectionScheme.compare("kinTournament") == 0)
		{
			tournamentGenomeSelection();
		}
		else if (MedeaAltruismSharedData::selectionScheme.compare("pureRandom") == 0)
		{
			pickRandomGenome();
		}
		else
		{
			gLogFile << "selection scheme unknown" << std::endl;
			exit(1);
		}
		_wm->setWaitForGenome(true);
		_wm->setActiveStatus(true);

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
		// case: no imported genome - wait for new genome.
		
		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " wait " << std::endl;

		_wm->resetActiveGenome(); // optional -- could be set to zeroes.
		_wm->setWaitForGenome(true); // inactive robot *must* import a genome from others (ie. no restart).

		_wm->setActiveStatus(false);//The robot is waiting for genome but not active yet
	}
	
	//Re-initialize the main parameters
	_wm->setDeltaEnergy(0.0); 

}



void MedeaAltruismAgentObserver::pickRandomGenome()
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
		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " t " << (*it).first << " s " << _wm->_currentSigma << std::endl;
		
		if (_wm->_agentId == 1 && gVerbose) // debug
			std::cout << "  Sigma is " << _wm->_sigmaList[(*it).first] << "." << std::endl;
		

		_wm->_sigmaList.clear();		
		_wm->_genomesList.clear();
	}
	//never reached
}

void MedeaAltruismAgentObserver::randomElitismGenomeSelection()
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
		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " t " << itRandom->first << " s " << _wm->_currentSigma << std::endl;
		
		if (_wm->_agentId == 1 && gVerbose) // debug
			std::cout << "  Sigma is " << _wm->_sigmaList[itRandom->first] << "." << std::endl;
		
		
		_wm->_genomesList.clear();
		_wm->_sigmaList.clear();
	}
}

void MedeaAltruismAgentObserver::tournamentGenomeSelection()
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

		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " t " << idLowest << " s " << _wm->_currentSigma << std::endl;
		if (_wm->_agentId == 1 && gVerbose) // debug
				std::cout << "  Sigma is " << _wm->_sigmaList[idLowest] << "." << std::endl;

	}
}



void MedeaAltruismAgentObserver::writeGenome(std::vector<double> genome, int senderId, float sigma)
{
		_wm->_genomesList[senderId] = genome;
		if ( MedeaAltruismSharedData::gDynamicSigma == true)
		{
			_wm->_sigmaList[senderId] = sigma;
		}

// 		gLogFile <<gWorld->getIterations()<< "agent #"  << _wm->_agentId << " size " << _wm->_genomesList.size() << "get:"<<senderId<<std::endl;

}


void MedeaAltruismAgentObserver::mutateWithBouncingBounds( float sigma)
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
		// bouncing upper/lower bounds if those bounds are set to a value different than 0.0
		if ( ( _wm->_minValue != 0.0 ) && ( _wm->_maxValue != 0.0 ) )
		{
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
		}
		
		_wm->_currentGenome[i] = value;
	}
	
}
