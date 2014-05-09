/*
 *  MedeaAltUtilityWorldObserver.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 24/05/10.
 *  Copyright 2010.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */

#include "Observers/AgentObserver.h"
#include "Observers/WorldObserver.h"

#include "mEDEA-altruism-utility/include/MedeaAltUtilityWorldObserver.h"

#include "World/World.h"


MedeaAltUtilityWorldObserver::MedeaAltUtilityWorldObserver( World* __world ) : WorldObserver( __world )
{
	_world = __world;

	// ==== loading project-specific properties 

	gProperties.checkAndGetPropertyValue("gSwarmOnlineObsUsed",&MedeaAltUtilitySharedData::gSwarmOnlineObsUsed,true);
	gProperties.checkAndGetPropertyValue("gDynamicSigma",&MedeaAltUtilitySharedData::gDynamicSigma,true);
	gProperties.checkAndGetPropertyValue("gSigmaMin",&MedeaAltUtilitySharedData::gSigmaMin,true);
	gProperties.checkAndGetPropertyValue("gProbAdd",&MedeaAltUtilitySharedData::gProbAdd,true);
	gProperties.checkAndGetPropertyValue("gProbSub",&MedeaAltUtilitySharedData::gProbSub,true);
	gProperties.checkAndGetPropertyValue("gDynaStep",&MedeaAltUtilitySharedData::gDynaStep,true);
	gProperties.checkAndGetPropertyValue("gSigmaRef",&MedeaAltUtilitySharedData::gSigmaRef,true);
	gProperties.checkAndGetPropertyValue("gSigmaMax",&MedeaAltUtilitySharedData::gSigmaMax,true);
	gProperties.checkAndGetPropertyValue("gProbRef",&MedeaAltUtilitySharedData::gProbRef,true);
	gProperties.checkAndGetPropertyValue("gProbMax",&MedeaAltUtilitySharedData::gProbMax,true);
	gProperties.checkAndGetPropertyValue("gEvaluationTime",&MedeaAltUtilitySharedData::gEvaluationTime,true);
	gProperties.checkAndGetPropertyValue("gDriftEvaluationRate",&MedeaAltUtilitySharedData::gDriftEvaluationRate,true);
	gProperties.checkAndGetPropertyValue("gInitLock",&MedeaAltUtilitySharedData::gInitLock,true);
	gProperties.checkAndGetPropertyValue("gDriftLock",&MedeaAltUtilitySharedData::gDriftLock,true);
	gProperties.checkAndGetPropertyValue("gMaxKeyRange",&MedeaAltUtilitySharedData::gMaxKeyRange,true);
	gProperties.checkAndGetPropertyValue("gDeltaKey",&MedeaAltUtilitySharedData::gDeltaKey,true);
	gProperties.checkAndGetPropertyValue("gSynchronization",&MedeaAltUtilitySharedData::gSynchronization,true);

	gProperties.checkAndGetPropertyValue("gExperimentNumber",&MedeaAltUtilitySharedData::gExperimentNumber,true);
	gProperties.checkAndGetPropertyValue("gExperiment1_genStart",&MedeaAltUtilitySharedData::gExperiment1_genStart,true);
	gProperties.checkAndGetPropertyValue("gExperiment2_genStart",&MedeaAltUtilitySharedData::gExperiment2_genStart,true);

	gProperties.checkAndGetPropertyValue("g_xStart_EnergyZone",&MedeaAltUtilitySharedData::g_xStart_EnergyZone,true);
	gProperties.checkAndGetPropertyValue("g_yStart_EnergyZone",&MedeaAltUtilitySharedData::g_yStart_EnergyZone,true);
	gProperties.checkAndGetPropertyValue("g_xEnd_EnergyZone",&MedeaAltUtilitySharedData::g_xEnd_EnergyZone,true);
	gProperties.checkAndGetPropertyValue("g_yEnd_EnergyZone",&MedeaAltUtilitySharedData::g_yEnd_EnergyZone,true);

	gProperties.checkAndGetPropertyValue("gZoneEnergy_maxHarvestValue",&MedeaAltUtilitySharedData::gZoneEnergy_maxHarvestValue,true);
	gProperties.checkAndGetPropertyValue("gZoneEnergy_minHarvestValue",&MedeaAltUtilitySharedData::gZoneEnergy_minHarvestValue,true);
	gProperties.checkAndGetPropertyValue("gZoneEnergy_maxFullCapacity",&MedeaAltUtilitySharedData::gZoneEnergy_maxFullCapacity,true);
	gProperties.checkAndGetPropertyValue("gZoneEnergy_saturateCapacityLevel",&MedeaAltUtilitySharedData::gZoneEnergy_saturateCapacityLevel,true);
	
	gProperties.checkAndGetPropertyValue("gEnergyMax",&MedeaAltUtilitySharedData::gEnergyMax,true);
	gProperties.checkAndGetPropertyValue("gEnergyInit",&MedeaAltUtilitySharedData::gEnergyInit,true);
	gProperties.checkAndGetPropertyValue("gEnergyRevive",&MedeaAltUtilitySharedData::gEnergyRevive,true);
	
	gProperties.checkAndGetPropertyValue("gMaxPenalizationRate",&MedeaAltUtilitySharedData::gMaxPenalizationRate,true);
	if ( MedeaAltUtilitySharedData::gMaxPenalizationRate < 0 || MedeaAltUtilitySharedData::gMaxPenalizationRate > 1 )
	{
		std::cerr << "gMaxPenalizationRate should be defined btw O and 1" << std::endl;
		exit(-1);
	}
	
	gProperties.checkAndGetPropertyValue("gDynamicRespawn",&MedeaAltUtilitySharedData::gDynamicRespawn,true); // forced, in this setup.
	gProperties.checkAndGetPropertyValue("gThresholdIncreaseRespawn",&MedeaAltUtilitySharedData::gThresholdIncreaseRespawn,true); 
	gProperties.checkAndGetPropertyValue("gLowestBoundRespawn",&MedeaAltUtilitySharedData::gLowestBoundRespawn,true); 
	gProperties.checkAndGetPropertyValue("gHighestBoundRespawn",&MedeaAltUtilitySharedData::gHighestBoundRespawn,true); 
		

	// ====

	if ( !gRadioNetwork)
	{
		std::cout << "Error : gRadioNetwork == false. The swarm online observer need the radio network" << std::endl;
		exit(1);
	}
	
	if ( !MedeaAltUtilitySharedData::gSwarmOnlineObsUsed)
	{
		std::cout << "Error : gSwarmOnlineObsUsed == false. The swarm online observer need some variables. Define this option to true or use another observer" << std::endl;
		exit(1);
	}

	if ( !gEnergyMode )
	{
		std::cout << "Error : gEnergyMode should be true to use SwarmOnlineObserver" << std::endl;
		exit(1);
	}
	
	// * iteration and generation counters
	
	_lifeIterationCount = -1;
	_generationCount = -1;

	std::cout << std::endl << "#### Experiment no.0 starts now. ####" << std::endl;
}

MedeaAltUtilityWorldObserver::~MedeaAltUtilityWorldObserver()
{
	// nothing to do.
}

void MedeaAltUtilityWorldObserver::reset()
{
	// nothing to do.
}

void MedeaAltUtilityWorldObserver::step()
{

	// ***
	// * update iteration and generation counters + switch btw experimental setups if required
	// ***
	
	_lifeIterationCount++;

	if( _lifeIterationCount >= MedeaAltUtilitySharedData::gEvaluationTime ) // go to next generation.
	{
		// * monitoring: count number of active agents.

		int activeCount = 0;
		for ( int i = 0 ; i != gAgentCounter ; i++ )
		{
			if ( (dynamic_cast<MedeaAltUtilityAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel()))->getActiveStatus() == true )
				activeCount++;
		}
		if ( !gVerbose )
		{
			std::cout << "[" << activeCount << "]";
		}
		gLogFile << gWorld->getIterations() << " : active count is " << activeCount << std::endl;

		int energyPointActiveCount = 0;
		for(std::vector<EnergyPoint>::iterator it = gEnergyPoints.begin(); it != gEnergyPoints.end(); it++)
		{
			if (it->getActiveStatus() == true)
			{
				energyPointActiveCount ++;
			}
		}
		gLogFile << gWorld->getIterations() << " : active energy point count is " << energyPointActiveCount << std::endl;
	
	
		// * update iterations and generations counters

		_lifeIterationCount = 0;
		_generationCount++;
		
	
		// * Switch btw experiment setups, if required	
	
		updateExperimentalSettings();

	}


	// * Update environment status wrt. nature and availability of energy resources (update at each iteration)

	updateEnvironmentResources();

	// * update energy level for each agents (ONLY active agents)
	
	updateAllAgentsEnergyLevel();
}


// ***
// * Check and update (ONLY IF REQUIRED) experimental setup.
// ***

void MedeaAltUtilityWorldObserver::updateExperimentalSettings()
{
		if ( _generationCount == MedeaAltUtilitySharedData::gExperiment1_genStart ) 
		{
			std::cout << std::endl << "#### Experiment no.1 starts now. ####" << std::endl;
			MedeaAltUtilitySharedData::gExperimentNumber = 1;
		}
		else
		{
			if ( _generationCount == MedeaAltUtilitySharedData::gExperiment2_genStart )
			{
				std::cout << std::endl << "#### Experiment no.2 starts now. ####" << std::endl;
				
				// * setup new experiment number
			
				MedeaAltUtilitySharedData::gExperimentNumber = 2;
			
				// * remove energy points.
			
				for(std::vector<EnergyPoint>::iterator it = gEnergyPoints.begin(); it != gEnergyPoints.end(); it++)
				{
					it->hide();
				}
				gEnergyPoints.clear();
			
				// * setup new energy zone
			
				Uint32 colorShown = 0xeab71fff;
				Uint32 colorZone  = 0xAAAAAAFF; // for floor sensor.
			
				for (Sint16 xColor = MedeaAltUtilitySharedData::g_xStart_EnergyZone ; xColor < MedeaAltUtilitySharedData::g_xEnd_EnergyZone ; xColor++)
				{
					for (Sint16 yColor = Sint16 (MedeaAltUtilitySharedData::g_yStart_EnergyZone) ; yColor < Sint16 (MedeaAltUtilitySharedData::g_yEnd_EnergyZone) ; yColor ++)
					{
							pixelColor(gBackgroundImage, xColor, yColor, colorShown);
							pixelColor(gZoneImage, xColor, yColor, colorZone);
					}
				}
			}
		}
}

// ***
// * Update environment status wrt. nature and availability of energy resources (update at each iteration)
// ***
void MedeaAltUtilityWorldObserver::updateEnvironmentResources()
{
	if ( MedeaAltUtilitySharedData::gExperimentNumber == 1 && MedeaAltUtilitySharedData::gDynamicRespawn == true )
	{	
	
		// * case: Experiment 1 -- update the energy point respawn lag.
		// sets automaticaly the energy point respawn lag if respawn is selected (ie. gDynamicRespawn = true)

		int activeCount = 0;
		for ( int i = 0 ; i != gAgentCounter ; i++ )
		{
			if ( (dynamic_cast<MedeaAltUtilityAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel()))->getActiveStatus() == true )  
				activeCount++;
		}
		
		// TODO: WARNING, IGNORE / OVERWRITE gEnergyPointRespawnLagMaxValue
		// (!n)-NOTE: as of 20100527, this code works, but is not modular. create dedicated method for computing update?
		if ( activeCount < MedeaAltUtilitySharedData::gThresholdIncreaseRespawn )
			//gEnergyPointRespawnLagMaxValue = 8.0 * (double)activeCount; // linear increase from 400 to 800
		{
			gEnergyPointRespawnLagMaxValue = MedeaAltUtilitySharedData::gLowestBoundRespawn;  
		}
		else
		{
			float slope = float(MedeaAltUtilitySharedData::gHighestBoundRespawn - MedeaAltUtilitySharedData::gLowestBoundRespawn)/float(gNbOfAgents-MedeaAltUtilitySharedData::gThresholdIncreaseRespawn);
			gEnergyPointRespawnLagMaxValue = slope * (double)(activeCount - MedeaAltUtilitySharedData::gThresholdIncreaseRespawn) + MedeaAltUtilitySharedData::gLowestBoundRespawn; // linear increase
		}
	} 
	else
	{	
		if ( MedeaAltUtilitySharedData::gExperimentNumber == 2 )
		{
		
			// * case: Experiment 2 -- monitor number of agents in the energy zone and update available energy.
		
			int agentsOnZone = 0;
			for ( int i = 0 ; i != gAgentCounter ; i++ )
			{
				int x = (int)(gWorld->getAgent(i)->getWorldModel()->getXReal());
				int y = (int)(gWorld->getAgent(i)->getWorldModel()->getYReal());
				// std::cout << "x =" << x << " , y = " << y << std::endl;
	
				if ( x >= MedeaAltUtilitySharedData::g_xStart_EnergyZone && y >= MedeaAltUtilitySharedData::g_yStart_EnergyZone && x <= MedeaAltUtilitySharedData::g_xEnd_EnergyZone && y <= MedeaAltUtilitySharedData::g_yEnd_EnergyZone )
					agentsOnZone++;
			}
		
			if ( gVerbose )
				std::cout << "There are " << agentsOnZone << " agents on the energy zone" <<  std::endl;
		
			if ( agentsOnZone <= MedeaAltUtilitySharedData::gZoneEnergy_maxFullCapacity )
			{
				// best case
				MedeaAltUtilitySharedData::gZoneEnergy_harvestValue = MedeaAltUtilitySharedData::gZoneEnergy_maxHarvestValue;
			}
			else
			{
				if ( agentsOnZone <= MedeaAltUtilitySharedData::gZoneEnergy_saturateCapacityLevel )
				{
					double energyValueSpan = MedeaAltUtilitySharedData::gZoneEnergy_maxHarvestValue - MedeaAltUtilitySharedData::gZoneEnergy_minHarvestValue;
					int agentsOverheadCount = MedeaAltUtilitySharedData::gZoneEnergy_saturateCapacityLevel - MedeaAltUtilitySharedData::gZoneEnergy_maxFullCapacity;
					double costPerAgents = energyValueSpan / (double)agentsOverheadCount;
					MedeaAltUtilitySharedData::gZoneEnergy_harvestValue = MedeaAltUtilitySharedData::gZoneEnergy_maxHarvestValue - costPerAgents * ( agentsOnZone- MedeaAltUtilitySharedData::gZoneEnergy_maxFullCapacity ) ;
				}
				else 
				{
					// worst case
					MedeaAltUtilitySharedData::gZoneEnergy_harvestValue = MedeaAltUtilitySharedData::gZoneEnergy_minHarvestValue;
				}
			}
		}
	}
}


// * 
// * update energy level for each agents (ONLY active agents) (only in experimental setups featuring energy items)
// *
void MedeaAltUtilityWorldObserver::updateAllAgentsEnergyLevel()
{	
	
	if ( MedeaAltUtilitySharedData::gExperimentNumber == 1 || MedeaAltUtilitySharedData::gExperimentNumber == 2 ) // only for exp. 1 and 2
	{
		for ( int i = 0 ; i != gAgentCounter ; i++ ) // for each agent
		{
			MedeaAltUtilityAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaAltUtilityAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
			
			// * check energy level. Becomes inactive if zero.
			
			if ( currentAgentWorldModel->getEnergyLevel() <= 0 )
			{
				currentAgentWorldModel->setDeltaEnergy(0);
				currentAgentWorldModel->setActiveStatus(false);
				currentAgentWorldModel->setWaitingAfterLifeSynchronization(true);
			}
	
			// * if active, check if agent harvests energy. (experimental setup dependant)
			
			if ( currentAgentWorldModel->getActiveStatus() == true )
			{
				if ( MedeaAltUtilitySharedData::gExperimentNumber == 1 ) 
				{
					// * update agent energy (if needed) - agent should be on an active energy point location to get energy
				
					Point2d posRobot(currentAgentWorldModel->_xReal,currentAgentWorldModel->_yReal);
					if ( gEnergyMode && currentAgentWorldModel->getActiveStatus())
					{
						for(std::vector<EnergyPoint>::iterator it = gEnergyPoints.begin(); it != gEnergyPoints.end(); it++)
						{
							if( (getEuclidianDistance (posRobot,it->getPosition()) < gEnergyPointRadius) && (it->getActiveStatus()))
							{
								float loadingEnergy = currentAgentWorldModel->getEnergyHarvestingRate() * gEnergyPointValue;
								//float loadingEnergy = 5*(1.0/(2.0*sqrt(2.0*M_PI)))*gEnergyPointValue; // test?
								//float loadingEnergy = 5*(1.0/(2.0*sqrt(2.0*M_PI)))*exp(-(pow((_key - it->getKey()),2.0)/(pow(2.0,2.0))))*gEnergyPointValue;
			
								gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId
									<< " get an energy point of " << loadingEnergy  << ". Before he was at " << currentAgentWorldModel->getEnergyLevel() <<std::endl;

								// update energy level
								currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel() + loadingEnergy);
								currentAgentWorldModel->setDeltaEnergy(currentAgentWorldModel->getDeltaEnergy() + loadingEnergy);
								currentAgentWorldModel->increaseTotalEnergyHarvested(loadingEnergy);
			
								//saturate
								if ( currentAgentWorldModel->getEnergyLevel() > MedeaAltUtilitySharedData::gEnergyMax ) // assume: need MedeaAltUtilitySharedData::gEvaluationTime to live full life
									currentAgentWorldModel->setEnergyLevel(MedeaAltUtilitySharedData::gEnergyMax);
			
			
								it->setRespawnLag(currentAgentWorldModel->getEnergyHarvestingRate()*MedeaAltUtilitySharedData::gHighestBoundRespawn);
								it->setActiveStatus(false);
							}
						}
					}
				}
				else 
				{
					if ( MedeaAltUtilitySharedData::gExperimentNumber == 2 ) 
					{
						// * update agent energy, only if it stands in the energy zone.
					
						if ( currentAgentWorldModel->_xReal >= MedeaAltUtilitySharedData::g_xStart_EnergyZone && currentAgentWorldModel->_xReal <= MedeaAltUtilitySharedData::g_xEnd_EnergyZone && currentAgentWorldModel->_yReal >= MedeaAltUtilitySharedData::g_yStart_EnergyZone && currentAgentWorldModel->_yReal <= MedeaAltUtilitySharedData::g_yEnd_EnergyZone )
						{
							float loadingEnergy = MedeaAltUtilitySharedData::gZoneEnergy_harvestValue;
							
							// update energy level
							currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel() + loadingEnergy);
							currentAgentWorldModel->setDeltaEnergy(currentAgentWorldModel->getDeltaEnergy() + loadingEnergy);
			
							// saturate
							if ( currentAgentWorldModel->getEnergyLevel() > MedeaAltUtilitySharedData::gEnergyMax ) // assume: need MedeaAltUtilitySharedData::gEvaluationTime to live full life
								currentAgentWorldModel->setEnergyLevel(MedeaAltUtilitySharedData::gEnergyMax);
			
							Point2d posRobot(currentAgentWorldModel->_xReal,currentAgentWorldModel->_yReal);				
							gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId
									<< "(" << posRobot.x << "," << posRobot.y << ")" 
									<< " get an energy point at 0,0 :: Value : " << loadingEnergy  << std::endl; // hack to comply with python log analyser
						}
					}
				}
			}
			
			
			// * update agent energy consumption -- if inactive, "revive" the agent (ie. it ran out of energy)
			
			// decrease the energyLevel and deltaEnergyLevel

			if (currentAgentWorldModel->getActiveStatus() == true )
			{
			
				if ( currentAgentWorldModel->getEnergyLevel() > 0.0 ) 
				{
					currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel()-1); 
				}
				currentAgentWorldModel->setDeltaEnergy(currentAgentWorldModel->getDeltaEnergy()-1); 
			}
	
	
			// "revive" agent with empty genomes if ran out of energy.
			
			if  ( currentAgentWorldModel->getEnergyLevel()  <= 0.0 )
			{
				gLogFile << gWorld->getIterations() << " : Human intervention on robot " << currentAgentWorldModel->_agentId << " (Energy)" << std::endl;
				// reformulate (check python script compatibility before): gLogFile << "Info(" << gWorld->getIterations() << ") : robot " << _wm->_agentId << " was revived (human intervention)" << std::endl;
	
				if (currentAgentWorldModel->_agentId == gAgentIndexFocus && gVerbose) // debug
				{
					std::cout << "agent #" << gAgentIndexFocus << " is revived (energy was 0)." << std::endl;
				}
	
				// Display the current state of the controller
				gLogFile << gWorld->getIterations() << " : #Robot: " << currentAgentWorldModel->_agentId
					<< " #Energy: " <<  currentAgentWorldModel->getEnergyLevel()
					<< " #DeltaEnergy: " << currentAgentWorldModel->getDeltaEnergy()
					<< " #GenomeListSize: " << currentAgentWorldModel->_genomesList.size() <<std::endl;
				
				currentAgentWorldModel->resetActiveGenome();
			
				currentAgentWorldModel->setEnergyLevel(MedeaAltUtilitySharedData::gEnergyRevive); // !n : too few?
	
				currentAgentWorldModel->setActiveStatus(false); // true: restart, false: no-restart
				currentAgentWorldModel->setWaitingAfterLifeSynchronization(true);
			
				currentAgentWorldModel->_genomesList.empty();
			}
		}	
	}
}


int MedeaAltUtilityWorldObserver::getLifeIterationCount()
{
	return _lifeIterationCount;
}
