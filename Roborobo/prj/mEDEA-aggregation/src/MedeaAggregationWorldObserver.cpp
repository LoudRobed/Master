/*
 *  MedeaAggregationWorldObserver.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 24/05/10.
 *  Copyright 2010.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */

#include "Observers/AgentObserver.h"
#include "Observers/WorldObserver.h"

#include "mEDEA-aggregation/include/MedeaAggregationWorldObserver.h"

#include "World/World.h"
#include <algorithm>

MedeaAggregationWorldObserver::MedeaAggregationWorldObserver( World* __world ) : WorldObserver( __world )
{
	_world = __world;

	// ==== loading project-specific properties 

	gProperties.checkAndGetPropertyValue("gSwarmOnlineObsUsed",&MedeaAggregationSharedData::gSwarmOnlineObsUsed,true);
	gProperties.checkAndGetPropertyValue("gDynamicSigma",&MedeaAggregationSharedData::gDynamicSigma,true);
	gProperties.checkAndGetPropertyValue("gSigmaMin",&MedeaAggregationSharedData::gSigmaMin,true);
	gProperties.checkAndGetPropertyValue("gProbAdd",&MedeaAggregationSharedData::gProbAdd,true);
	gProperties.checkAndGetPropertyValue("gProbSub",&MedeaAggregationSharedData::gProbSub,true);
	gProperties.checkAndGetPropertyValue("gDynaStep",&MedeaAggregationSharedData::gDynaStep,true);
	gProperties.checkAndGetPropertyValue("gSigmaRef",&MedeaAggregationSharedData::gSigmaRef,true);
	gProperties.checkAndGetPropertyValue("gSigmaMax",&MedeaAggregationSharedData::gSigmaMax,true);
	gProperties.checkAndGetPropertyValue("gProbRef",&MedeaAggregationSharedData::gProbRef,true);
	gProperties.checkAndGetPropertyValue("gProbMax",&MedeaAggregationSharedData::gProbMax,true);
	gProperties.checkAndGetPropertyValue("gEvaluationTime",&MedeaAggregationSharedData::gEvaluationTime,true);
	gProperties.checkAndGetPropertyValue("gDriftEvaluationRate",&MedeaAggregationSharedData::gDriftEvaluationRate,true);
	gProperties.checkAndGetPropertyValue("gInitLock",&MedeaAggregationSharedData::gInitLock,true);
	gProperties.checkAndGetPropertyValue("gDriftLock",&MedeaAggregationSharedData::gDriftLock,true);
	gProperties.checkAndGetPropertyValue("gMaxKeyRange",&MedeaAggregationSharedData::gMaxKeyRange,true);
	gProperties.checkAndGetPropertyValue("gDeltaKey",&MedeaAggregationSharedData::gDeltaKey,true);
	gProperties.checkAndGetPropertyValue("gSynchronization",&MedeaAggregationSharedData::gSynchronization,true);

	gProperties.checkAndGetPropertyValue("g_xStart_EnergyZone",&MedeaAggregationSharedData::g_xStart_EnergyZone,true);
	gProperties.checkAndGetPropertyValue("g_yStart_EnergyZone",&MedeaAggregationSharedData::g_yStart_EnergyZone,true);
	gProperties.checkAndGetPropertyValue("g_xEnd_EnergyZone",&MedeaAggregationSharedData::g_xEnd_EnergyZone,true);
	gProperties.checkAndGetPropertyValue("g_yEnd_EnergyZone",&MedeaAggregationSharedData::g_yEnd_EnergyZone,true);

	gProperties.checkAndGetPropertyValue("gZoneEnergy_maxHarvestValue",&MedeaAggregationSharedData::gZoneEnergy_maxHarvestValue,true);
	gProperties.checkAndGetPropertyValue("gZoneEnergy_minHarvestValue",&MedeaAggregationSharedData::gZoneEnergy_minHarvestValue,true);
	gProperties.checkAndGetPropertyValue("gZoneEnergy_maxFullCapacity",&MedeaAggregationSharedData::gZoneEnergy_maxFullCapacity,true);
	gProperties.checkAndGetPropertyValue("gZoneEnergy_saturateCapacityLevel",&MedeaAggregationSharedData::gZoneEnergy_saturateCapacityLevel,true);
	
	gProperties.checkAndGetPropertyValue("gDeadTime",&MedeaAggregationSharedData::gDeadTime,true);
	gProperties.checkAndGetPropertyValue("gEnergyMax",&MedeaAggregationSharedData::gEnergyMax,true);
	gProperties.checkAndGetPropertyValue("gEnergyInit",&MedeaAggregationSharedData::gEnergyInit,true);
	gProperties.checkAndGetPropertyValue("gEnergyRevive",&MedeaAggregationSharedData::gEnergyRevive,true);
	
	gProperties.checkAndGetPropertyValue("gMaxPenalizationRate",&MedeaAggregationSharedData::gMaxPenalizationRate,true);
	if ( MedeaAggregationSharedData::gMaxPenalizationRate < 0 || MedeaAggregationSharedData::gMaxPenalizationRate > 1 )
	{
		std::cerr << "gMaxPenalizationRate should be defined btw O and 1" << std::endl;
		exit(-1);
	}
	
	gProperties.checkAndGetPropertyValue("gDynamicRespawn",&MedeaAggregationSharedData::gDynamicRespawn,true); // forced, in this setup.
	gProperties.checkAndGetPropertyValue("gThresholdIncreaseRespawn",&MedeaAggregationSharedData::gThresholdIncreaseRespawn,true); 
	gProperties.checkAndGetPropertyValue("gLowestBoundRespawn",&MedeaAggregationSharedData::gLowestBoundRespawn,true); 
	gProperties.checkAndGetPropertyValue("gHighestBoundRespawn",&MedeaAggregationSharedData::gHighestBoundRespawn,true); 
	
	gProperties.checkAndGetPropertyValue("fixedCost",&fixedCost,true);
	gProperties.checkAndGetPropertyValue("exponentialFactor",&exponentialFactor,true);

	gProperties.checkAndGetPropertyValue("selectionScheme",&MedeaAggregationSharedData::selectionScheme,true);
	gProperties.checkAndGetPropertyValue("harvestingScheme",&MedeaAggregationSharedData::harvestingScheme,true);

	gProperties.checkAndGetPropertyValue("energyPointValueMax",&MedeaAggregationSharedData::energyPointValueMax,true);
	gProperties.checkAndGetPropertyValue("nbEnergyPoints",&nbEnergyPoints,true);
	gProperties.checkAndGetPropertyValue("temperature",&temperature,true);
	gProperties.checkAndGetPropertyValue("margin",&margin,true);
	// ====

	if ( !gRadioNetwork)
	{
		std::cout << "Error : gRadioNetwork == false. The swarm online observer need the radio network" << std::endl;
		exit(1);
	}
	
	if ( !MedeaAggregationSharedData::gSwarmOnlineObsUsed)
	{
		std::cout << "Error : gSwarmOnlineObsUsed == false. The swarm online observer need some variables. Define this option to true or use another observer" << std::endl;
		exit(1);
	}

	if ( !gEnergyMode )
	{
		std::cout << "Error : gEnergyMode should be true to use SwarmOnlineObserver" << std::endl;
		exit(1);
	}
	
	// show if agents are in organisms or not

	agentPositiveMaskImageFilename = "data/agent-positive-mask.png";
	agentNegativeMaskImageFilename = "data/agent-negative-mask.png";

	if (gProperties.hasProperty("agentPositiveMaskImageFilename"))
	{
		agentPositiveMaskImageFilename = gProperties.getProperty("agentPositiveMaskImageFilename");
	}
		
	if (gProperties.hasProperty("agentNegativeMaskImageFilename"))
	{
		agentNegativeMaskImageFilename = gProperties.getProperty("agentNegativeMaskImageFilename");
	}

	agentPositiveMaskImage = load_image(agentPositiveMaskImageFilename);
	if (agentPositiveMaskImage == NULL) {
		std::cerr << "Could not load agent positive mask image\n";
	}

	agentNegativeMaskImage = load_image(agentNegativeMaskImageFilename);
	if (agentNegativeMaskImage == NULL) {
		std::cerr << "Could not load agent negative mask image\n";
	}

	SDL_SetColorKey(agentPositiveMaskImage, SDL_SRCCOLORKEY, SDL_MapRGB(agentPositiveMaskImage->format, 0xFF, 0xFF, 0xFF));
	SDL_SetColorKey(agentNegativeMaskImage, SDL_SRCCOLORKEY, SDL_MapRGB(agentNegativeMaskImage->format, 0xFF, 0xFF, 0xFF));
	
	// * iteration and generation counters
	
	_lifeIterationCount = -1;
	firstIteration = true;
}

MedeaAggregationWorldObserver::~MedeaAggregationWorldObserver()
{
	while (!specificEnergyPoints.empty())
	{
		delete specificEnergyPoints.back();
		specificEnergyPoints.pop_back();
	}
}

void MedeaAggregationWorldObserver::reset()
{
	// nothing to do.
}

void MedeaAggregationWorldObserver::step()
{
	if (firstIteration == true)
	{
		if (temperature == -1)
		{
			for ( int i = 0 ; i != nbEnergyPoints ; i++)
			{
				specificEnergyPoints.push_back(new MedeaAggregationEnergyPoint(i,-1,margin));
				specificEnergyPoints.back()->init();
				InanimateObject * pInaObj = (InanimateObject*) specificEnergyPoints.back();
				gWorld->addObject(pInaObj);
			}
		}
		else
		{
			
			for ( int i =0 ; i < nbEnergyPoints ; i++)
			{
				if ( (i % 2) == 0 )
				{
				specificEnergyPoints.push_back(new MedeaAggregationEnergyPoint(i,1,margin));
				specificEnergyPoints.back()->init();
				InanimateObject * pInaObj = (InanimateObject*) specificEnergyPoints.back();
				gWorld->addObject(pInaObj);
				}
				else
				{
				specificEnergyPoints.push_back(new MedeaAggregationEnergyPoint(i,2,margin));
				specificEnergyPoints.back()->init();
				InanimateObject * pInaObj = (InanimateObject*) specificEnergyPoints.back();
				gWorld->addObject(pInaObj);
				}
			}
		}
		firstIteration = false;
	}

	// ***
	// * update iteration and generation counters + switch btw experimental setups if required
	// ***
	
	_lifeIterationCount++;

	if( _lifeIterationCount >= MedeaAggregationSharedData::gEvaluationTime ) // print mEDEA state
	{
		// * monitoring: count number of active agents.

		int activeCount = 0;
		int nbSingleRobot = 0;
		int nbRobotInOrganism = 0;
		gLogFile << gWorld->getIterations() << " : active " ;
		for ( int i = 0 ; i != gAgentCounter ; i++ )
		{
			if ( (dynamic_cast<MedeaAggregationAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel()))->getStatus() == MedeaAggregationAgentWorldModel::ACTIVE )
			{
				activeCount++;
				gLogFile << i << " ";
				if ( dynamic_cast<RobotAgentConnectable*>(gWorld->getAgent(i))->isPartOfOrganism() == true )
				{
					if ( dynamic_cast<RobotAgentConnectable*>(gWorld->getAgent(i))->getOrganism()->size() > 1 )
					{
						nbRobotInOrganism ++;
					}
					else
					{
						nbSingleRobot ++;
					}
				}
				else
				{
					nbSingleRobot ++;
				}
			}
		}
		gLogFile << "\n" ;
		if ( !gVerbose )
		{
			std::cout << "[" << activeCount << "]";
		}
		gLogFile << gWorld->getIterations() << " : activeCount " << activeCount << std::endl;
		gLogFile << gWorld->getIterations() << " : rs " << std::showpoint << std::fixed << (double)nbSingleRobot/(double)activeCount << std::endl;
		gLogFile << gWorld->getIterations() << " : ro " << std::showpoint << std::fixed << (double)nbRobotInOrganism/(double)activeCount << std::endl;
		gLogFile << gWorld->getIterations() << " : os " ;
		std::vector<int> sizes = Organism::getSizes();
		for (unsigned int i = 0 ; i < sizes.size() ; i++)
		{
			if (sizes[i] > 1)
			{
				gLogFile << sizes[i] << " ";
			}
		}
		gLogFile << std::endl;


		if(activeCount<=0)
		{
			gLogFile.close();
			exit(0);
		}

		if (temperature == -1)
		{
			int energyPointActiveCount = 0;
			for(std::vector<MedeaAggregationEnergyPoint*>::iterator it = specificEnergyPoints.begin(); it != specificEnergyPoints.end(); it++)
			{
				if ((*it)->getActiveStatus() == true)
				{
					energyPointActiveCount ++;
				}
			}
			gLogFile << gWorld->getIterations() << " : EP t -1 activeCount " << energyPointActiveCount << std::endl;
		}
		else
		{
			int energyPointActiveCount1 = 0;
			int energyPointActiveCount2 = 0;
			for(std::vector<MedeaAggregationEnergyPoint*>::iterator it = specificEnergyPoints.begin(); it != specificEnergyPoints.end(); it++)
			{
				if ((*it)->getActiveStatus() == true)
				{
					if ((*it)->getHarvestingOrganismSize() == 1) energyPointActiveCount1 ++;
					if ((*it)->getHarvestingOrganismSize() == 2) energyPointActiveCount2 ++;
				}
			}
			gLogFile << gWorld->getIterations() << " : EP t 1 activeCount " << energyPointActiveCount1 << std::endl;
			gLogFile << gWorld->getIterations() << " : EP t 2 activeCount " << energyPointActiveCount2 << std::endl;
		}
	
	
		// * update iterations counter
		_lifeIterationCount = 0;
		
	}

	// * update energy level for each agents (ONLY active agents)
	
	updateAllAgentsEnergyLevel();
	updateAllAgentsDistanceToEnergyPoints();

	// show if agents are in organism or single
	for ( int i = 0 ; i != gAgentCounter ; i++ )
	{
		RobotAgentConnectable* agent = dynamic_cast<RobotAgentConnectable*>(gWorld->getAgent(i));
		if (agent == 0)
		{
			std::cerr << "With mEDEA-aggregation project, RobotAgentConnectable should be used" << std::endl;
			exit(1);
		}

		//TODO: check active status
		//TODO: fall back if mask aren't provided
		//TODO: change mask only if needed
		if (agent->isPartOfOrganism() == true)
		{
			agent->setAgentMask(agentPositiveMaskImage);
		}
		else
		{
			agent->setAgentMask(agentNegativeMaskImage);
		}
	}
}


// * 
// * update energy level for each agents (ONLY active agents) (only in experimental setups featuring energy items)
// *
void MedeaAggregationWorldObserver::updateAllAgentsEnergyLevel()
{	
	
	for ( int i = 0 ; i != gAgentCounter ; i++ ) // for each agent
	{
		MedeaAggregationAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaAggregationAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
		
		// * if active, check if agent harvests energy. (experimental setup dependant)
		
		if ( currentAgentWorldModel->getStatus() == MedeaAggregationAgentWorldModel::ACTIVE )
		{
			// * update agent energy (if needed) - agent should be on an active energy point location to get energy
		
			Point2d posRobot(currentAgentWorldModel->_xReal,currentAgentWorldModel->_yReal);
			if ( gEnergyMode )
			{
				for(std::vector<MedeaAggregationEnergyPoint*>::iterator it = specificEnergyPoints.begin(); it != specificEnergyPoints.end(); it++)
				{
					if( (getEuclidianDistance (posRobot,(*it)->getPosition()) < gEnergyPointRadius) 
							 && ((*it)->getActiveStatus())
							 )
					{
						//If the temperature is set check the size of organism
						//if the size match the point, then the harvesting continue, otherwise we break to another energy point
						if (temperature != -1 )
						{
							int organismSize = 1;
							if ( dynamic_cast<RobotAgentConnectable*>(gWorld->getAgent(i))->isPartOfOrganism() == true )
							{
								organismSize = dynamic_cast<RobotAgentConnectable*>(gWorld->getAgent(i))->getOrganism()->size(); 
							}
							if ( ( ((*it)->getHarvestingOrganismSize() == 1) && (organismSize != 1) )
									||
									(( ((*it)->getHarvestingOrganismSize() > 1) && (organismSize == 1) ) ) )
							{
								continue;
							}
						}

							float loadingEnergy = 0.0;
							if ( MedeaAggregationSharedData::harvestingScheme.compare("dynCost") == 0)
							{
								loadingEnergy = currentAgentWorldModel->getEnergyHarvestingRate() * gEnergyPointValue;
							}
							else if ( MedeaAggregationSharedData::harvestingScheme.compare("fixedCost") == 0)
							{
								loadingEnergy = std::max( 0.0 , std::min( double(gEnergyPointValue), MedeaAggregationSharedData::gEnergyMax - currentAgentWorldModel->getEnergyLevel() ) - fixedCost);
							}
							else
							{
								gLogFile << "harvesting scheme unknown" << std::endl;
								exit(1);
							}
							//float loadingEnergy = 5*(1.0/(2.0*sqrt(2.0*M_PI)))*gEnergyPointValue; // test?
							//float loadingEnergy = 5*(1.0/(2.0*sqrt(2.0*M_PI)))*exp(-(pow((_key - it->getKey()),2.0)/(pow(2.0,2.0))))*gEnergyPointValue;

							/*
							double energyMissing = MedeaAggregationSharedData::gEnergyMax-currentAgentWorldModel->getEnergyLevel();
							double costMeasure = 0.0;

							if ( currentAgentWorldModel->getEnergyLevel() + loadingEnergy < MedeaAggregationSharedData::gEnergyMax )
							{
								if (gEnergyPointValue > energyMissing)
								{
									costMeasure = energyMissing - loadingEnergy;
								}
								else
								{
									costMeasure = gEnergyPointValue - loadingEnergy;
								}
							}
		
							gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId << " c "  << costMeasure << std::endl;
							*/

							// update energy level
							currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel() + loadingEnergy);
							currentAgentWorldModel->setDeltaEnergy(currentAgentWorldModel->getDeltaEnergy() + loadingEnergy);
		
							//saturate
							if ( currentAgentWorldModel->getEnergyLevel() > MedeaAggregationSharedData::gEnergyMax ) // assume: need MedeaAggregationSharedData::gEvaluationTime to live full life
								currentAgentWorldModel->setEnergyLevel(MedeaAggregationSharedData::gEnergyMax);
		
							//double loadingRatio = loadingEnergy/gEnergyPointValue;
							//double exponentialRespawn = exp(loadingRatio*exponentialFactor)*(MedeaAggregationSharedData::gHighestBoundRespawn/exp(exponentialFactor));
							//it->setRespawnLag(exponentialRespawn);

							(*it)->setRespawnLag((loadingEnergy/gEnergyPointValue)*MedeaAggregationSharedData::energyPointRespawnLagMaxValue);
							(*it)->setActiveStatus(false);
					}
				}
			}
		}
		
		
		
		// decrease the energyLevel and deltaEnergyLevel
		if (currentAgentWorldModel->getStatus() == MedeaAggregationAgentWorldModel::ACTIVE )
		{
			if ( currentAgentWorldModel->getEnergyLevel() > 0.0 ) 
			{
				currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel()-1); 
			}
			currentAgentWorldModel->setDeltaEnergy(currentAgentWorldModel->getDeltaEnergy()-1); 
		}
	

		if  ( currentAgentWorldModel->getEnergyLevel()  <= 0.0 )
		{
			gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId << " die" << std::endl;
			gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId << " lf " << currentAgentWorldModel->getLifeTime() << std::endl;
			
			currentAgentWorldModel->resetActiveGenome(currentAgentWorldModel->_nbGenes);
			currentAgentWorldModel->setMaturity(1);
		
			currentAgentWorldModel->setEnergyLevel(MedeaAggregationSharedData::gEnergyRevive); 
			currentAgentWorldModel->setDeltaEnergy(0.0); 
			gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId << " a " << (currentAgentWorldModel->_idlenessTracker.getAverageBoxesIdleness() / currentAgentWorldModel->getLifeTime()) * 100000 << std::endl;
			currentAgentWorldModel->setLifeTime(0);

			currentAgentWorldModel->setStatus(MedeaAggregationAgentWorldModel::DEAD);
		
			currentAgentWorldModel->_genomesList.empty();
			currentAgentWorldModel->setGripperStatus(GripperConnectionMechanism::HIGH);
		}
	}	
}

void MedeaAggregationWorldObserver::updateAllAgentsDistanceToEnergyPoints()
{
	for ( int i = 0 ; i != gAgentCounter ; i++ ) // for each agent
	{
		MedeaAggregationAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaAggregationAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());

		double angleToClosestEnergyPoint = 0.0;
		double shortestDistance = -1.0;
		//search the closest energy point
		Point2d posRobot(currentAgentWorldModel->_xReal,currentAgentWorldModel->_yReal);
		std::vector<MedeaAggregationEnergyPoint*>::iterator closestPoint = specificEnergyPoints.begin();
	
		while ( (shortestDistance == -1.0)  && (closestPoint < specificEnergyPoints.end() ))
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
			for(std::vector<MedeaAggregationEnergyPoint*>::iterator it = specificEnergyPoints.begin()+1; it < specificEnergyPoints.end(); it++)
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

			if ((*closestPoint)->getHarvestingOrganismSize() == 1)
			{
				currentAgentWorldModel->setEnergyPointType(-1.0);
			}
			else
			{
				currentAgentWorldModel->setEnergyPointType(1.0);
			}
		}
	}
}

int MedeaAggregationWorldObserver::getLifeIterationCount()
{
	return _lifeIterationCount;
}
