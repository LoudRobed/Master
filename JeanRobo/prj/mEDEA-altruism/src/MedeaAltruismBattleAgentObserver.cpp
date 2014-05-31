/*
 *  MedeaAltruismBattleAgentObserver.cpp
 *  Roborobo
 *
 *  Created by Jean-Marc on 15/12/09.
 *
 */


#include "mEDEA-altruism/include/MedeaAltruismBattleAgentObserver.h"

#include "World/World.h"
#include "Utilities/Misc.h"
#include "RoboroboMain/roborobo.h"
#include "BehaviorControlArchitectures/EnergyPerceptronControlArchitecture.h"
#include "mEDEA-altruism/include/MedeaAltruismPerceptronControlArchitecture.h"
#include "mEDEA-altruism/include/MedeaAltruismAgentWorldModel.h"
#include <cmath>


#include "mEDEA-altruism/include/MedeaAltruismBattleWorldObserver.h"

MedeaAltruismBattleAgentObserver::MedeaAltruismBattleAgentObserver( RobotAgentWorldModel *__wm )
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

	_side = -1;
}

MedeaAltruismBattleAgentObserver::~MedeaAltruismBattleAgentObserver()
{
	// nothing to do.
}

void MedeaAltruismBattleAgentObserver::reset()
{
	_wm->_idlenessTracker.reset();
}

void MedeaAltruismBattleAgentObserver::step()
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
				MedeaAltruismBattleAgentObserver* targetAgentObserver = dynamic_cast<MedeaAltruismBattleAgentObserver*>(gWorld->getAgent(i)->getObserver());
				if ( ! targetAgentObserver )
				{
					std::cerr << "Error from robot " << _wm->_agentId << " : the observer of robot " << i << " isn't a MedeaAltruismBattleAgentObserver" << std::endl;
					exit(1);
				}
				if((targetAgentObserver->_wm->getActiveStatus() ) || targetAgentObserver->_wm->getWaitForGenome())
				{
					targetAgentObserver->writeGenome(_wm->_currentGenome, _wm->_agentId + 1000 * _wm->getDateOfBirth());
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



void MedeaAltruismBattleAgentObserver::checkGenomeList()
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



void MedeaAltruismBattleAgentObserver::pickRandomGenome()
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
		_wm->setNewGenomeStatus(true); 
		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " take " << (*it).first << std::endl;
		_wm->_genomesList.clear();
	}
}

void MedeaAltruismBattleAgentObserver::randomElitismGenomeSelection()
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
		_wm->setNewGenomeStatus(true); 
		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " t " << itRandom->first << std::endl;		
		
		_wm->_genomesList.clear();
	}
}

void MedeaAltruismBattleAgentObserver::tournamentGenomeSelection()
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
		_wm->setNewGenomeStatus(true); 

		_wm->_sigmaList.clear();

		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " t " << idLowest << std::endl;
	}
}




void MedeaAltruismBattleAgentObserver::writeGenome(std::vector<double> genome, int senderId)
{
	_wm->_genomesList[senderId] = genome;
}




void MedeaAltruismBattleAgentObserver::loadGenome(std::vector<double> inGenome)
{
	std::cout << std::flush ;
	_wm->_currentGenome.clear();
	for ( unsigned int i = 0 ; i != inGenome.size() ; i++ )
	{
		_wm->_currentGenome.push_back(inGenome[i]);
	}
	_wm->setNewGenomeStatus(true);
	_wm->_genomesList.clear();
//	MedeaAltruismPerceptronControlArchitecture* currentBehavior = dynamic_cast<MedeaAltruismPerceptronControlArchitecture*>(gWorld->getAgent(_wm->_agentId)->getBehavior());
	_wm->setDeltaEnergy(10.0);
	_wm->setActiveStatus(true); // true: restart, false: no-restart
}

int MedeaAltruismBattleAgentObserver::getSide()
{
	return _side;
}
