/*
 *  MedeaAggregationBattleAgentObserver.cpp
 *  Roborobo
 *
 *  imported from Jean-Marc on 15/12/09
 *  current dev: Nicolas on 1/4/2009
 *
 */


#include "mEDEA-aggregation/include/MedeaAggregationBattleAgentObserver.h"

#include "World/World.h"
#include "Utilities/Misc.h"
#include "RoboroboMain/roborobo.h"
#include "mEDEA-aggregation/include/MedeaAggregationControlArchitecture.h"
#include <cmath>


#include "mEDEA-aggregation/include/MedeaAggregationBattleWorldObserver.h"


// *** *** *** *** ***


MedeaAggregationBattleAgentObserver::MedeaAggregationBattleAgentObserver( RobotAgentWorldModel *__wm )
{
	_wm = (MedeaAggregationAgentWorldModel*)__wm;

	_wm->_minValue = -0.0;
	_wm->_maxValue = 0.0;

	_wm->_currentSigma = MedeaAggregationSharedData::gSigmaRef;
	_wm->setLifeTime(1);
	_wm->setStatus(MedeaAggregationAgentWorldModel::ACTIVE);
	_wm->_genomesList.clear();
	_wm->_sigmaList.clear();

	gProperties.checkAndGetPropertyValue("nbHiddenNeurons",&_wm->_nbHiddenNeurons,true);
	gProperties.checkAndGetPropertyValue("gNbMaxGenomeSelection",&nbMaxGenomeSelection,true);
	
	_wm->resetActiveGenome(_wm->_nbGenes);
	_wm->setMaturity(0);
	_wm->_idlenessTracker.reset();
	_wm->setFirstStep(true);

	iterationDown = 0;
	iterationUp = 0;
	
	if ( gVerbose )
	{
		std::cout << "robot #" << _wm->_agentId << "\n" ;	
	}

}

MedeaAggregationBattleAgentObserver::~MedeaAggregationBattleAgentObserver()
{
	// nothing to do.
}

void MedeaAggregationBattleAgentObserver::reset()
{
	_wm->_idlenessTracker.reset();
}

void MedeaAggregationBattleAgentObserver::step()
{

	if(_wm->getFirstStep() == true)
	{
		RobotAgentConnectable* agent = dynamic_cast<RobotAgentConnectable*>(gWorld->getAgent(_wm->_agentId));
		if (agent == 0)
		{
			std::cerr << "With Aggregation Basic project, RobotAgentConnectable should be used" << std::endl;
			exit(1);
		}
		GripperConnectionMechanism* connection = new GripperConnectionMechanism(agent);

		_wm->setUpGripper(connection);
		_wm->setGripperStatus(GripperConnectionMechanism::HIGH);
		_wm->setFirstStep(false);
	}

	// debug verbose
	if ( gVerbose && gInspectAgent && gAgentIndexFocus == _wm->_agentId )
	{
		std::cout << "target: " << _wm->getEnergyPointDirectionAngleValue() << std::endl;
	}

	// at the end of a generation
	if( (_wm->getLifeTime() >= MedeaAggregationSharedData::gEvaluationTime) && (_wm->getStatus() == MedeaAggregationAgentWorldModel::ACTIVE || (_wm->getStatus() == MedeaAggregationAgentWorldModel::LISTEN)))
	 
	{		
		//display area covered only if agent active at the end of its evaluation time (end of generation)
		if (_wm->getStatus() == MedeaAggregationAgentWorldModel::ACTIVE)
		{
			gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " lf " << _wm->getLifeTime() << std::endl;
			gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " a " << (_wm->_idlenessTracker.getAverageBoxesIdleness() / _wm->getLifeTime()) * 100000 << std::endl;
			gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " tu " << iterationUp << std::endl;
			gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " td " << iterationDown << std::endl;
		}
		iterationUp = 0;
		iterationDown = 0;
		checkGenomeList(); //if the genome list is empty, the robot will wait during one generation. Otherwise it will be active during one generation
		_wm->setLifeTime(0);
		_wm->_idlenessTracker.reset();
	}
	
	// at the end of the dead time, the robot state is switched to listen
	if(_wm->getLifeTime() >= (MedeaAggregationSharedData::gEvaluationTime*MedeaAggregationSharedData::gDeadTime) && _wm->getStatus() == MedeaAggregationAgentWorldModel::DEAD )
	{
		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " listen" << std::endl;
		_wm->setStatus(MedeaAggregationAgentWorldModel::LISTEN);
		_wm->_idlenessTracker.reset();
	}
	
	//agent is mature if it has survive (gEnergyRevive+10) iterations
	if( (_wm->getStatus() == MedeaAggregationAgentWorldModel::ACTIVE) && _wm->getMaturity() > 0)
	{
		_wm->setMaturity(_wm->getMaturity()+1);
		if(_wm->getMaturity() > MedeaAggregationSharedData::gEnergyRevive +10 )
		{
			_wm->setMaturity(0); 
			gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " m" << std::endl;
		}
		
	}


	// broadcast only if agent is active and mature 
	if ( _wm->getStatus() == MedeaAggregationAgentWorldModel::ACTIVE && _wm->getMaturity()<=0)
	{
		for (int i = 0 ; i < gAgentCounter ; i++)
		{
			if ( ( i != _wm->_agentId ) && ( gRadioNetworkArray[_wm->_agentId][i] ) ) 
			{
				MedeaAggregationBattleAgentObserver* targetAgentObserver = dynamic_cast<MedeaAggregationBattleAgentObserver*>(gWorld->getAgent(i)->getObserver());
				if ( ! targetAgentObserver )
				{
					std::cerr << "Error from robot " << _wm->_agentId << " : the observer of robot " << i << " isn't a SwarmOnlineObserver" << std::endl;
					exit(1);
				}

				if((targetAgentObserver->_wm->getStatus() == MedeaAggregationAgentWorldModel::ACTIVE ) || (targetAgentObserver->_wm->getStatus() == MedeaAggregationAgentWorldModel::LISTEN))
				{
					targetAgentObserver->writeGenome(_wm->_currentGenome, _wm->_agentId + 1000 * _wm->getDateOfBirth());
				}
			}
		}
	}

	if ( _wm->getStatus() == MedeaAggregationAgentWorldModel::ACTIVE)
	{
		if (_wm->getGripperStatus() == GripperConnectionMechanism::LOW)
		{
			iterationDown ++;
		}
		if (_wm->getGripperStatus() == GripperConnectionMechanism::HIGH)
		{
			iterationUp ++;
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



void MedeaAggregationBattleAgentObserver::checkGenomeList()
{
	int activeCount = 0;
			for ( int i = 0 ; i != gAgentCounter ; i++ )
			{
				if ( (dynamic_cast<MedeaAggregationAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel()))->getStatus() == MedeaAggregationAgentWorldModel::ACTIVE )
				{
					activeCount++;
				}
			}
	// Display the current state of the controller
	gLogFile << gWorld->getIterations() << " : " << _wm->_agentId
			 << " E " <<  _wm->getEnergyLevel()
			 << " DE " << _wm->getDeltaEnergy()
			 << " GenomeLS " << _wm->_genomesList.size() <<std::endl;
	gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " GenomeLSNorm " << std::fixed << std::showpoint << (double)_wm->_genomesList.size()/(double)activeCount << std::endl;
		
	if (_wm->_genomesList.size() > 0)
	{
		_wm->setDateOfBirth(gWorld->getIterations());
		if (MedeaAggregationSharedData::selectionScheme.compare("randomElitism") == 0)
		{
			randomElitismGenomeSelection();
		}
		else if (MedeaAggregationSharedData::selectionScheme.compare("kinTournament") == 0)
		{
			tournamentGenomeSelection();
		}
		else if (MedeaAggregationSharedData::selectionScheme.compare("pureRandom") == 0)
		{
			pickRandomGenome();
		}
		else
		{
			gLogFile << "selection scheme unknown" << std::endl;
			exit(1);
		}
		_wm->setStatus(MedeaAggregationAgentWorldModel::ACTIVE);

		//log the genome
		gLogFile << gWorld->getIterations() <<" : "<< _wm->_agentId << " use ";
		for(unsigned int i=0; i<_wm->_currentGenome.size(); i++)
		{
			gLogFile << std::fixed << std::showpoint << _wm->_currentGenome[i] << " ";
		}
		gLogFile << std::endl;
	}
	else
	{
		// case: no imported genome - wait for new genome.
		
		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " wait " << std::endl;

		_wm->resetActiveGenome(_wm->_nbGenes); 
		_wm->setStatus(MedeaAggregationAgentWorldModel::LISTEN);//The robot is waiting for genome but not active yet
	}
	
	//Re-initialize the main parameters
	_wm->setDeltaEnergy(0.0); 

}



void MedeaAggregationBattleAgentObserver::pickRandomGenome()
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
		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " t " << (*it).first << " s " << _wm->_currentSigma << std::endl;
		
		if (_wm->_agentId == 1 && gVerbose) // debug
			std::cout << "  Sigma is " << _wm->_sigmaList[(*it).first] << "." << std::endl;
		
		_wm->_genomesList.clear();
	}
	//never reached
}

void MedeaAggregationBattleAgentObserver::randomElitismGenomeSelection()
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
		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " t " << itRandom->first << " s " << _wm->_currentSigma << std::endl;
		
		if (_wm->_agentId == 1 && gVerbose) // debug
			std::cout << "  Sigma is " << _wm->_sigmaList[itRandom->first] << "." << std::endl;
		
		
		_wm->_genomesList.clear();
	}
}

void MedeaAggregationBattleAgentObserver::tournamentGenomeSelection()
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
		_wm->_genomesList.clear();

		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " t " << idLowest << " s " << _wm->_currentSigma << std::endl;
		if (_wm->_agentId == 1 && gVerbose) // debug
				std::cout << "  Sigma is " << _wm->_sigmaList[idLowest] << "." << std::endl;

	}
}



void MedeaAggregationBattleAgentObserver::writeGenome(std::vector<double> genome, int senderId)
{
	_wm->_genomesList[senderId] = genome;
}


void MedeaAggregationBattleAgentObserver::loadGenome(std::vector<double> inGenome)
{
	std::cout << std::flush ;
	_wm->_currentGenome.clear();
	for ( unsigned int i = 0 ; i != inGenome.size() ; i++ )
	{
		_wm->_currentGenome.push_back(inGenome[i]);
	}
	_wm->setNewGenomeStatus(true);
	_wm->_genomesList.clear();

	_wm->setDeltaEnergy(10.0);
	_wm->setStatus(MedeaAggregationAgentWorldModel::ACTIVE);
}
