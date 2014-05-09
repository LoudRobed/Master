/*
 *  MedeaCommWorldObserver.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 24/05/10.
 *  Copyright 2010.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */

#include "Observers/AgentObserver.h"
#include "Observers/WorldObserver.h"

#include "mEDEA-comm/include/MedeaCommWorldObserver.h"

#include "World/World.h"
#include <algorithm>

MedeaCommWorldObserver::MedeaCommWorldObserver( World* __world ) : WorldObserver( __world )
{
	_world = __world;

	// ==== loading project-specific properties 

	gProperties.checkAndGetPropertyValue("gDynamicSigma",&MedeaCommSharedData::gDynamicSigma,true);
	gProperties.checkAndGetPropertyValue("gSigmaMin",&MedeaCommSharedData::gSigmaMin,true);
	gProperties.checkAndGetPropertyValue("gProbAdd",&MedeaCommSharedData::gProbAdd,true);
	gProperties.checkAndGetPropertyValue("gProbSub",&MedeaCommSharedData::gProbSub,true);
	gProperties.checkAndGetPropertyValue("gDynaStep",&MedeaCommSharedData::gDynaStep,true);
	gProperties.checkAndGetPropertyValue("gSigmaRef",&MedeaCommSharedData::gSigmaRef,true);
	gProperties.checkAndGetPropertyValue("gSigmaMax",&MedeaCommSharedData::gSigmaMax,true);
	gProperties.checkAndGetPropertyValue("gEvaluationTime",&MedeaCommSharedData::gEvaluationTime,true);
	
	gProperties.checkAndGetPropertyValue("gDeadTime",&MedeaCommSharedData::gDeadTime,true);
	gProperties.checkAndGetPropertyValue("gEnergyMax",&MedeaCommSharedData::gEnergyMax,true);
	gProperties.checkAndGetPropertyValue("gEnergyInit",&MedeaCommSharedData::gEnergyInit,true);
	gProperties.checkAndGetPropertyValue("gEnergyRevive",&MedeaCommSharedData::gEnergyRevive,true);

	gProperties.checkAndGetPropertyValue("energyPointValueMax",&MedeaCommSharedData::energyPointValueMax,true);
	gProperties.checkAndGetPropertyValue("singleAccess",&MedeaCommSharedData::singleAccess,true);
	
	gProperties.checkAndGetPropertyValue("fixedCost",&fixedCost,true);
	gProperties.checkAndGetPropertyValue("nbEnergyPoints",&nbEnergyPoints,true);

	gProperties.checkAndGetPropertyValue("maxCostAction",&maxCostAction,true);
	gProperties.checkAndGetPropertyValue("receptionOn",&MedeaCommSharedData::receptionOn,true);
	gProperties.checkAndGetPropertyValue("maxCostCommunication",&maxCostCommunication,true);
	gProperties.checkAndGetPropertyValue("nbReceptionSector",&MedeaCommSharedData::nbReceptionSector,true);
	gProperties.checkAndGetPropertyValue("receptionDistance",&MedeaCommSharedData::receptionDistance,true);
	// ====

	if ( !gRadioNetwork)
	{
		std::cout << "Error : gRadioNetwork == false. The swarm online observer need the radio network" << std::endl;
		exit(1);
	}
	
	// * iteration and generation counters
	
	_lifeIterationCount = -1;
	firstIteration = true;
}

MedeaCommWorldObserver::~MedeaCommWorldObserver()
{
	// nothing to do.
	while (!coopEnergyPoints.empty())
	{
		delete coopEnergyPoints.back();
		coopEnergyPoints.pop_back();
	}
}

void MedeaCommWorldObserver::reset()
{
	// nothing to do.
}

void MedeaCommWorldObserver::step()
{
	if (firstIteration == true)
	{
		for ( int i = 0 ; i != nbEnergyPoints ; i++)
		{
			coopEnergyPoints.push_back(new MedeaCommEnergyPoint());
			InanimateObject * pInaObj = (InanimateObject*) coopEnergyPoints.back();
			gWorld->addObject(pInaObj);
		}
		firstIteration = false;
	}

	// ***
	// * update iteration and generation counters + switch btw experimental setups if required
	// ***
	
	_lifeIterationCount++;

	if( _lifeIterationCount >= MedeaCommSharedData::gEvaluationTime ) // go to next generation.
	{
		// * monitoring: count number of active agents.

		int activeCount = 0;
		for ( int i = 0 ; i != gAgentCounter ; i++ )
		{
			if ( (dynamic_cast<MedeaCommAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel()))->getActiveStatus() == true )
				activeCount++;
		}
		if ( !gVerbose )
		{
			std::cout << "[" << activeCount << "]";
			std::cout << std::flush ;
		}
		gLogFile << gWorld->getIterations() << " : activeCount " << activeCount << std::endl;

		if(activeCount<=0)
		{
			gLogFile.close();
			exit(0);
		}

		int energyPointActiveCount = 0;
		for(std::vector<MedeaCommEnergyPoint*>::iterator it = coopEnergyPoints.begin(); it != coopEnergyPoints.end(); it++)
		{
			if ((*it)->getActiveStatus() == true)
			{
				energyPointActiveCount ++;
			}
		}
		gLogFile << gWorld->getIterations() << " : EP activeCount " << energyPointActiveCount << std::endl;
	
	
		// * update iterations counter
		_lifeIterationCount = 0;
		
	}

	// * update energy level for each agents (ONLY active agents)
	
	updateAllAgentsEnergyLevel();
	updateAllAgentsDistanceToEnergyPoints();
}


// * 
// * update energy level for each agents (ONLY active agents) (only in experimental setups featuring energy items)
// *
void MedeaCommWorldObserver::updateAllAgentsEnergyLevel()
{	
	bool contestAtThisIteration = false;
	for ( int i = 0 ; i != gAgentCounter ; i++ ) // for each agent
	{
		MedeaCommAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaCommAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
		currentAgentWorldModel->setIsInContest(false);
	}

	for(std::vector<MedeaCommEnergyPoint*>::iterator it = coopEnergyPoints.begin(); it != coopEnergyPoints.end(); it++)
	{
		std::vector<int> agentsOnPoint;
		for ( int i = 0 ; i != gAgentCounter ; i++ ) // for each agent
		{
			MedeaCommAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaCommAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());

			// * if active, check if agent harvests energy. (experimental setup dependant)
			if ( currentAgentWorldModel->getActiveStatus() == true )
			{
				Point2d posRobot(currentAgentWorldModel->_xReal,currentAgentWorldModel->_yReal);
				if( (getEuclidianDistance (posRobot,(*it)->getPosition()) < (*it)->getRadius()) && ((*it)->getActiveStatus()) && (currentAgentWorldModel->getAction() > (*it)->getHarvestingThreshold() ) ) 
				{
					agentsOnPoint.push_back(currentAgentWorldModel->_agentId);
					currentAgentWorldModel->setIsInContest(true);
					contestAtThisIteration = true;
				}
			}
		}

		if (agentsOnPoint.size() > 0) 
		{
			if (MedeaCommSharedData::singleAccess == true)
			{
				int mostActive = agentsOnPoint[0];
				MedeaCommAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaCommAgentWorldModel*>(gWorld->getAgent(agentsOnPoint[0])->getWorldModel());
				double highestAction = currentAgentWorldModel->getAction();
				for (unsigned int vectorIndex=1 ; vectorIndex < agentsOnPoint.size() ; vectorIndex ++ )
				{
					currentAgentWorldModel = dynamic_cast<MedeaCommAgentWorldModel*>(gWorld->getAgent(agentsOnPoint[vectorIndex])->getWorldModel());
					double action = currentAgentWorldModel->getAction();
					if ( action > highestAction)
					{
						highestAction = action;
						mostActive = agentsOnPoint[vectorIndex];
					}
				}

				double loadingEnergy = (*it)->getEnergy();
				// update energy level
				currentAgentWorldModel = dynamic_cast<MedeaCommAgentWorldModel*>(gWorld->getAgent(mostActive)->getWorldModel());
				currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel() + loadingEnergy);
				currentAgentWorldModel->setDeltaEnergy(currentAgentWorldModel->getDeltaEnergy() + loadingEnergy);

				gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId << " get " << loadingEnergy << std::endl;

				//saturate
				if ( currentAgentWorldModel->getEnergyLevel() > MedeaCommSharedData::gEnergyMax ) 
					currentAgentWorldModel->setEnergyLevel(MedeaCommSharedData::gEnergyMax);
			}
			else
			{
				for (unsigned int vectorIndex=0 ; vectorIndex < agentsOnPoint.size() ; vectorIndex ++ )
				{
					MedeaCommAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaCommAgentWorldModel*>(gWorld->getAgent(agentsOnPoint[vectorIndex])->getWorldModel());

					double loadingEnergy = (*it)->getEnergy();

					// update energy level
					currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel() + loadingEnergy);
					currentAgentWorldModel->setDeltaEnergy(currentAgentWorldModel->getDeltaEnergy() + loadingEnergy);

					gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId << " get " << loadingEnergy << std::endl;

					//saturate
					if ( currentAgentWorldModel->getEnergyLevel() > MedeaCommSharedData::gEnergyMax ) 
						currentAgentWorldModel->setEnergyLevel(MedeaCommSharedData::gEnergyMax);
				}
			}
		}
	}
		
	//log the contest values
	if (contestAtThisIteration == true)
	{
		gLogFile << gWorld->getIterations() << " : contests " ;
		for ( int i = 0 ; i != gAgentCounter ; i++ ) // for each agent
		{
			MedeaCommAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaCommAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());

			if (currentAgentWorldModel->getIsInContest() == true)
			{
				gLogFile <<  currentAgentWorldModel->getAction() << " " ;
			}
		}
		gLogFile << std::endl;
	}

	//log the action values
	if (gWorld->getIterations() % 10 == 0)
	{
		gLogFile << gWorld->getIterations() << " : actions " ;
		for ( int i = 0 ; i != gAgentCounter ; i++ ) // for each agent
		{
			MedeaCommAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaCommAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
			if (currentAgentWorldModel->getIsInContest() == false) 
			{
				gLogFile <<  currentAgentWorldModel->getAction() << " ";
			}
		}
		gLogFile << std::endl;
	}

	for ( int i = 0 ; i != gAgentCounter ; i++ ) // for each agent
	{
		MedeaCommAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaCommAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
		
		// * update agent energy consumption -- if inactive, "revive" the agent (ie. it ran out of energy)
		
		// decrease the energyLevel and deltaEnergyLevel

		if (currentAgentWorldModel->getActiveStatus() == true )
		{
			if ( currentAgentWorldModel->getEnergyLevel() > 0.0 ) 
			{
				currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel()-1); 
				currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel()-(currentAgentWorldModel->getAction()*maxCostAction)); 
				currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel()-(currentAgentWorldModel->getCommunication()*maxCostCommunication)); 
			}
			currentAgentWorldModel->setDeltaEnergy(currentAgentWorldModel->getDeltaEnergy()-1); 
		}


		// "revive" agent with empty genomes if ran out of energy.
		
		if  ( currentAgentWorldModel->getEnergyLevel()  <= 0.0 )
		{
			gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId << " die" << std::endl;
			
			currentAgentWorldModel->resetActiveGenome();
			currentAgentWorldModel->setMaturity(1);
		
			currentAgentWorldModel->setEnergyLevel(MedeaCommSharedData::gEnergyRevive); 
			currentAgentWorldModel->setDeltaEnergy(0.0); 
			currentAgentWorldModel->setLifeTime(0);

			currentAgentWorldModel->setActiveStatus(false);
			currentAgentWorldModel->setWaitForGenome(false);
		
			currentAgentWorldModel->_genomesList.empty();
		}
	}	
}

void MedeaCommWorldObserver::updateAllAgentsDistanceToEnergyPoints()
{
	for ( int i = 0 ; i != gAgentCounter ; i++ ) // for each agent
	{
		MedeaCommAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaCommAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());

		double angleToClosestEnergyPoint = 0.0;
		double shortestDistance = -1.0;
		//search the closest energy point
		Point2d posRobot(currentAgentWorldModel->_xReal,currentAgentWorldModel->_yReal);
		std::vector<MedeaCommEnergyPoint*>::iterator closestPoint = coopEnergyPoints.begin();
	
		while ( (shortestDistance == -1.0)  && (closestPoint < coopEnergyPoints.end() ))
		{
			if ((*closestPoint)->getActiveStatus() == true) 
			{
				shortestDistance = getEuclidianDistance (posRobot,(*closestPoint)->getPosition());
			}
			else
			{
				closestPoint ++;
			}
		}

		if ( shortestDistance == -1.0 )
		{
			currentAgentWorldModel->setAngleToClosestEnergyPoint(0.0);
			currentAgentWorldModel->setDistanceToClosestEnergyPoint(0.0);
		}

		if (shortestDistance != -1.0 ) 
		{
			for(std::vector<MedeaCommEnergyPoint*>::iterator it = coopEnergyPoints.begin()+1; it < coopEnergyPoints.end(); it++)
			{
				if ((*it)->getActiveStatus() == true)
				{
					double newDistance = getEuclidianDistance (posRobot,(*it)->getPosition());
					if (newDistance < shortestDistance)
					{
						shortestDistance = newDistance;
						closestPoint = it;
					}
				}
			}
			//compute the orientation of the closest energy point ( in degree between 0 and 360 )
			angleToClosestEnergyPoint = (atan2((*closestPoint)->getPosition().y-posRobot.y,(*closestPoint)->getPosition().x-posRobot.x)/M_PI)*180.0;
			angleToClosestEnergyPoint += 360.0 ;
			angleToClosestEnergyPoint = computeModulo(angleToClosestEnergyPoint,360.0);
			if ( angleToClosestEnergyPoint > 180 ) // force btw -180 and 180
				angleToClosestEnergyPoint -= 360.0;

			//compute the angle between the actual orientation of the robot and the orientation of the closest energy point ( in degree between -180 and 180 )
			double diffAngleToClosestEnergyPoint = angleToClosestEnergyPoint -  currentAgentWorldModel->_agentAbsoluteOrientation ;
			if ( diffAngleToClosestEnergyPoint < -180.0 )
			{
				diffAngleToClosestEnergyPoint += 360.0 ; 
			}
			if ( diffAngleToClosestEnergyPoint > 180.0 )
			{
				diffAngleToClosestEnergyPoint -= 360.0 ;
			}
			
			//cast the diffAngle between -1 and 1 and set it
			diffAngleToClosestEnergyPoint = diffAngleToClosestEnergyPoint / 180.0 ; 
			currentAgentWorldModel->setAngleToClosestEnergyPoint(diffAngleToClosestEnergyPoint);
		
			//cast the shortest distance between 0 and 1 and set it
			if ( shortestDistance > gSensorRange )
			{
				shortestDistance = 1.0;
			}
			else
			{
				shortestDistance = shortestDistance / (double)gSensorRange;
			}
			currentAgentWorldModel->setDistanceToClosestEnergyPoint(shortestDistance);
		}
	}
}

int MedeaCommWorldObserver::getLifeIterationCount()
{
	return _lifeIterationCount;
}
