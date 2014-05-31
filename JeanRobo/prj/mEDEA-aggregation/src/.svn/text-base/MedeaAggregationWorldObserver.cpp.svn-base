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
}

MedeaAggregationWorldObserver::~MedeaAggregationWorldObserver()
{
	// nothing to do.
}

void MedeaAggregationWorldObserver::reset()
{
	// nothing to do.
}

void MedeaAggregationWorldObserver::step()
{

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

		int energyPointActiveCount = 0;
		for(std::vector<EnergyPoint>::iterator it = gEnergyPoints.begin(); it != gEnergyPoints.end(); it++)
		{
			if (it->getActiveStatus() == true)
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
				for(std::vector<EnergyPoint>::iterator it = gEnergyPoints.begin(); it != gEnergyPoints.end(); it++)
				{
					if( (getEuclidianDistance (posRobot,it->getPosition()) < gEnergyPointRadius) && (it->getActiveStatus()))
					{
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
	
						//gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId << " c "  << costMeasure << std::endl;

						// update energy level
						currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel() + loadingEnergy);
						currentAgentWorldModel->setDeltaEnergy(currentAgentWorldModel->getDeltaEnergy() + loadingEnergy);
	
						//saturate
						if ( currentAgentWorldModel->getEnergyLevel() > MedeaAggregationSharedData::gEnergyMax ) // assume: need MedeaAggregationSharedData::gEvaluationTime to live full life
							currentAgentWorldModel->setEnergyLevel(MedeaAggregationSharedData::gEnergyMax);
	
						//double loadingRatio = loadingEnergy/gEnergyPointValue;
						//double exponentialRespawn = exp(loadingRatio*exponentialFactor)*(MedeaAggregationSharedData::gHighestBoundRespawn/exp(exponentialFactor));
						//it->setRespawnLag(exponentialRespawn);
						it->setRespawnLag((loadingEnergy/gEnergyPointValue)*MedeaAggregationSharedData::gHighestBoundRespawn);
						it->setActiveStatus(false);
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
			
			currentAgentWorldModel->resetActiveGenome();
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


int MedeaAggregationWorldObserver::getLifeIterationCount()
{
	return _lifeIterationCount;
}
