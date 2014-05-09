/*
 *  MedeaOptimWorldObserver.cpp
 *
 *  Created by Nicolas on 19/1/2011
 *
 */

#include "Observers/AgentObserver.h"
#include "Observers/WorldObserver.h"

#include "mEDEA-optim/include/MedeaOptimWorldObserver.h"
#include "World/World.h"


MedeaOptimWorldObserver::MedeaOptimWorldObserver( World* __world ) : WorldObserver( __world )
{
	_world = __world;

	// ==== loading project-specific properties 

	gProperties.checkAndGetPropertyValue("gSwarmOnlineObsUsed",&MedeaOptimSharedData::gSwarmOnlineObsUsed,true);
	gProperties.checkAndGetPropertyValue("gDynamicSigma",&MedeaOptimSharedData::gDynamicSigma,true);
	gProperties.checkAndGetPropertyValue("gSigmaMin",&MedeaOptimSharedData::gSigmaMin,true);
	gProperties.checkAndGetPropertyValue("gProbAdd",&MedeaOptimSharedData::gProbAdd,true);
	gProperties.checkAndGetPropertyValue("gProbSub",&MedeaOptimSharedData::gProbSub,true);
	gProperties.checkAndGetPropertyValue("gDynaStep",&MedeaOptimSharedData::gDynaStep,true);
	gProperties.checkAndGetPropertyValue("gSigmaRef",&MedeaOptimSharedData::gSigmaRef,true);
	gProperties.checkAndGetPropertyValue("gSigmaMax",&MedeaOptimSharedData::gSigmaMax,true);
	gProperties.checkAndGetPropertyValue("gProbRef",&MedeaOptimSharedData::gProbRef,true);
	gProperties.checkAndGetPropertyValue("gProbMax",&MedeaOptimSharedData::gProbMax,true);
	gProperties.checkAndGetPropertyValue("gEvaluationTime",&MedeaOptimSharedData::gEvaluationTime,true);
	gProperties.checkAndGetPropertyValue("gDriftEvaluationRate",&MedeaOptimSharedData::gDriftEvaluationRate,true);
	gProperties.checkAndGetPropertyValue("gInitLock",&MedeaOptimSharedData::gInitLock,true);
	gProperties.checkAndGetPropertyValue("gDriftLock",&MedeaOptimSharedData::gDriftLock,true);
	gProperties.checkAndGetPropertyValue("gMaxKeyRange",&MedeaOptimSharedData::gMaxKeyRange,true);
	gProperties.checkAndGetPropertyValue("gDeltaKey",&MedeaOptimSharedData::gDeltaKey,true);
	gProperties.checkAndGetPropertyValue("gSynchronization",&MedeaOptimSharedData::gSynchronization,true);

	gProperties.checkAndGetPropertyValue("g_xStart_EnergyZone",&MedeaOptimSharedData::g_xStart_EnergyZone,true);
	gProperties.checkAndGetPropertyValue("g_yStart_EnergyZone",&MedeaOptimSharedData::g_yStart_EnergyZone,true);
	gProperties.checkAndGetPropertyValue("g_xEnd_EnergyZone",&MedeaOptimSharedData::g_xEnd_EnergyZone,true);
	gProperties.checkAndGetPropertyValue("g_yEnd_EnergyZone",&MedeaOptimSharedData::g_yEnd_EnergyZone,true);

	gProperties.checkAndGetPropertyValue("gZoneEnergy_maxHarvestValue",&MedeaOptimSharedData::gZoneEnergy_maxHarvestValue,true);
	gProperties.checkAndGetPropertyValue("gZoneEnergy_minHarvestValue",&MedeaOptimSharedData::gZoneEnergy_minHarvestValue,true);
	gProperties.checkAndGetPropertyValue("gZoneEnergy_maxFullCapacity",&MedeaOptimSharedData::gZoneEnergy_maxFullCapacity,true);
	gProperties.checkAndGetPropertyValue("gZoneEnergy_saturateCapacityLevel",&MedeaOptimSharedData::gZoneEnergy_saturateCapacityLevel,true);
	
	gProperties.checkAndGetPropertyValue("gEnergyMax",&MedeaOptimSharedData::gEnergyMax,true);
	gProperties.checkAndGetPropertyValue("gEnergyInit",&MedeaOptimSharedData::gEnergyInit,true);
	gProperties.checkAndGetPropertyValue("gEnergyRevive",&MedeaOptimSharedData::gEnergyRevive,true);
	
	gProperties.checkAndGetPropertyValue("gMaxPenalizationRate",&MedeaOptimSharedData::gMaxPenalizationRate,true);
	if ( MedeaOptimSharedData::gMaxPenalizationRate < 0 || MedeaOptimSharedData::gMaxPenalizationRate > 1 )
	{
		std::cerr << "gMaxPenalizationRate should be defined btw O and 1" << std::endl;
		exit(-1);
	}
	
	gProperties.checkAndGetPropertyValue("gDynamicRespawn",&MedeaOptimSharedData::gDynamicRespawn,true); // forced, in this setup.

	gProperties.checkAndGetPropertyValue("gAlphaCorrelationValue",&MedeaOptimSharedData::gAlphaCorrelationValue,true); // forced, in this setup.	
	

	// ====

	if ( !gRadioNetwork)
	{
		std::cout << "Error : gRadioNetwork == false. The swarm online observer need the radio network" << std::endl;
		exit(1);
	}
	
	if ( !MedeaOptimSharedData::gSwarmOnlineObsUsed)
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

	_activeAgents_genStart = gNbOfAgents;
	_activeAgents_genEnd = -1;


	std::cout << std::endl << "#### Experiment starts now. ####" << std::endl;
	//if ( !gVerbose )
	{
		std::cout << "[" << _activeAgents_genStart << "," ; // gen #0
	}

}

MedeaOptimWorldObserver::~MedeaOptimWorldObserver()
{
	// nothing to do.
}

void MedeaOptimWorldObserver::reset()
{
	// nothing to do.
}

void MedeaOptimWorldObserver::step()
{

	if( _lifeIterationCount == MedeaOptimSharedData::gEvaluationTime-2 ) // log survivors at the beginning of the last iteration of the current generation (before renewal and re-activation of revived (not active) agents)
	{
		// * monitoring: count number of active agents.

		_activeAgents_genEnd = 0;
		
		for ( int i = 0 ; i != gAgentCounter ; i++ )
		{
			if ( (dynamic_cast<MedeaOptimAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel()))->getActiveStatus() == true )
			{
				_activeAgents_genEnd++;
			}
		}
		
		//if ( !gVerbose )
		{
			std::cout << _activeAgents_genEnd << "]"; // NOTE: this counts agents active at beginning of next generation (ie. those that ended the previous generation with genomeList>0, including survivalists and revived-but-inactive agents.
		}											// this is what was original tracked for logging in PPSN, MCMDS and possibly medea:altruist(early 2011)

	}


	// ***
	// * update iteration and generation counters + switch btw experimental setups if required
	// ***
	
	_lifeIterationCount++;


	if( _lifeIterationCount >= MedeaOptimSharedData::gEvaluationTime ) // go to next generation.
	{
		// * monitoring: count number of active agents.

		_activeAgents_genStart = 0;
		
		for ( int i = 0 ; i != gAgentCounter ; i++ )
		{
			if ( (dynamic_cast<MedeaOptimAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel()))->getActiveStatus() == true )
			{
				_activeAgents_genStart++;
			}
		}

		//if ( !gVerbose )
		{
			std::cout << "[" << _activeAgents_genStart << ","; // NOTE: this counts agents active at beginning of next generation (ie. those that ended the previous generation with genomeList>0, including survivalists and revived-but-inactive agents.
		}											// this is what was original tracked for logging in PPSN, MCMDS and possibly medea:altruist(early 2011)
	
		gLogFile << "Info(" << gWorld->getIterations() << ") : active count is " << _activeAgents_genStart << std::endl;
	
	
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

void MedeaOptimWorldObserver::updateExperimentalSettings()
{
		// only one experiment in this project (based on experiment 1 in original medea@PPSN).
}

// ***
// * Update environment status wrt. nature and availability of energy resources (update at each iteration)
// ***
void MedeaOptimWorldObserver::updateEnvironmentResources()
{
	if ( MedeaOptimSharedData::gDynamicRespawn == true )
	{	
	
		// * case: Experiment 1 -- update the energy point respawn lag.
		// sets automaticaly the energy point respawn lag if respawn is selected (ie. gDynamicRespawn = true)

		int activeCount = 0;
		for ( int i = 0 ; i != gAgentCounter ; i++ )
		{
			if ( (dynamic_cast<MedeaOptimAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel()))->getActiveStatus() == true )  
				activeCount++;
		}
		
		// TODO: move parameters to properties file.
		// TODO: WARNING, IGNORE / OVERWRITE gEnergyPointRespawnLagMaxValue
		// (!n)-NOTE: as of 20100527, this code works, but is not modular. create dedicated method for computing update?
		if ( activeCount < 50 )
		{
			gEnergyPointRespawnLagMaxValue = 400;  
		}
		else
		{
			gEnergyPointRespawnLagMaxValue = 72.0 * (double)activeCount - 3200.0; // linear increase from 400 to 4000
			//gEnergyPointRespawnLagMaxValue = 8.0 * (double)activeCount; // linear increase from 400 to 800
		}
	} 
}


// * 
// * update energy level for each agents (ONLY active agents) (only in experimental setups featuring energy items)
// *
void MedeaOptimWorldObserver::updateAllAgentsEnergyLevel()
{	
	
		for ( int i = 0 ; i != gAgentCounter ; i++ ) // for each agent
		{
			MedeaOptimAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaOptimAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
			
			// * check energy level. Becomes inactive if zero.
			
			if ( currentAgentWorldModel->getEnergyLevel() <= 0 )
			{
				currentAgentWorldModel->setDeltaEnergy(0);
				currentAgentWorldModel->setActiveStatus(false);
			}
	
			// * if active, check if agent harvests energy. (experimental setup dependant)
			
			if ( currentAgentWorldModel->getActiveStatus() == true )
			{
					// * update agent energy (if needed) - agent should be on an active energy point location to get energy
				
					Point2d posRobot(currentAgentWorldModel->_xReal,currentAgentWorldModel->_yReal);
					if ( gEnergyMode && currentAgentWorldModel->getActiveStatus())
					{
						for(std::vector<EnergyPoint>::iterator it = gEnergyPoints.begin(); it != gEnergyPoints.end(); it++)
						{
							if( (getEuclidianDistance (posRobot,it->getPosition()) < gEnergyPointRadius) && (it->getActiveStatus()))
							{
								// energy point harvested!
							
								float loadingEnergy = gEnergyPointValue;
			
								// update energy level
								
								// **** SPECIFIC CODE FOR MEDEA-OPTIM ***

								double convertToFitnessRatio = currentAgentWorldModel->_genome[currentAgentWorldModel->_genome.size()-1]; // last gene value
								double range = currentAgentWorldModel->_maxValue - currentAgentWorldModel->_minValue;
								convertToFitnessRatio = ( convertToFitnessRatio + range/2.0 ) / range; // btw 0 and 1
	
	
								// 1 - In all cases. Fitness value only depends on converted energy
								
								currentAgentWorldModel->setDeltaEnergy(currentAgentWorldModel->getDeltaEnergy() + loadingEnergy); // in all cases (used only for logging purpose)

								double energyToFitness = loadingEnergy * convertToFitnessRatio; // converted energy
								currentAgentWorldModel->setFitness( currentAgentWorldModel->getFitness() + energyToFitness );

								// 2 - Energy consumed as battery energy differs according to current scheme and ratio.
								
								double energyToBattery = 0;
								if ( MedeaOptimSharedData::gAlphaCorrelationValue >= 0 )
								{	// case #1 : alpha = [0,1] -- if alpha=1, convert to fitness is "free". 
									energyToBattery = ( 1.0 - convertToFitnessRatio ) + convertToFitnessRatio * MedeaOptimSharedData::gAlphaCorrelationValue;
								}
									else
								{ // case #2 : alpha = [-1,0[
									energyToBattery = ( 1.0 - convertToFitnessRatio ) + MedeaOptimSharedData::gAlphaCorrelationValue;
									if ( energyToBattery < 0.0 )
										energyToBattery = 0.0;
								}

								energyToBattery = energyToBattery * loadingEnergy; // re-normalize to energy value.
								currentAgentWorldModel->setEnergyLevel( currentAgentWorldModel->getEnergyLevel() + energyToBattery );

								// **** SPECIFIC CODE FOR MEDEA-OPTIM ***

								// If no alpha (older version -- PPSN)
								/*
								// convert into battery (consume)
								currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel() + loadingEnergy);
								currentAgentWorldModel->setDeltaEnergy(currentAgentWorldModel->getDeltaEnergy() + loadingEnergy);
								// convert into fitness (convert)
								currentAgentWorldModel->setFitness(currentAgentWorldModel->getFitness()+1.0);
								*/
								
								//saturate
								if ( currentAgentWorldModel->getEnergyLevel() > MedeaOptimSharedData::gEnergyMax ) // assume: need MedeaOptimSharedData::gEvaluationTime to live full life
									currentAgentWorldModel->setEnergyLevel(MedeaOptimSharedData::gEnergyMax);
			
								gLogFile << "Info(" << gWorld->getIterations() << ") : " << currentAgentWorldModel->_agentId
									<< "(" << posRobot.x << "," << posRobot.y << ")" 
									<< " get an energy point at " << it->getPosition().x << "," << it->getPosition().y << " :: Value : " << loadingEnergy  << std::endl;
			
								it->setActiveStatus(false);
							}
						}
				}
			}
			
			
			// * update agent energy consumption -- if inactive, "revive" the agent (ie. it ran out of energy)
			
			// decrease the energyLevel and deltaEnergyLevel
			
			if ( currentAgentWorldModel->getEnergyLevel() > 0.0 ) 
			{
				currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel()-1); 
			}
			currentAgentWorldModel->setDeltaEnergy(currentAgentWorldModel->getDeltaEnergy()-1); 
	
	
			// "revive" agent with empty genomes if ran out of energy.
			
			if  ( currentAgentWorldModel->getEnergyLevel()  <= 0.0 )
			{
				gLogFile << "Info(" << gWorld->getIterations() << ") : Human intervention on robot " << currentAgentWorldModel->_agentId << " (Energy)" << std::endl;
				// reformulate (check python script compatibility before): gLogFile << "Info(" << gWorld->getIterations() << ") : robot " << _wm->_agentId << " was revived (human intervention)" << std::endl;
	
				//if (currentAgentWorldModel->_agentId == gAgentIndexFocus && gVerbose) // debug
				//{
				//	std::cout << "agent #" << gAgentIndexFocus << " is revived (energy was 0)." << std::endl;
				//}
	
				// Display the current state of the controller
				gLogFile << "#GIteration: " << gWorld->getIterations() << " #Robot: " << currentAgentWorldModel->_agentId
					<< " #Energy: " <<  currentAgentWorldModel->getEnergyLevel()
					<< " #DeltaEnergy: " << currentAgentWorldModel->getDeltaEnergy()
					<< " #GenomeListSize: " << currentAgentWorldModel->_genomesList.size() <<std::endl;
				
				currentAgentWorldModel->resetActiveGenome();
				
				currentAgentWorldModel->setFitness(0.0);
			
				currentAgentWorldModel->setEnergyLevel(MedeaOptimSharedData::gEnergyRevive);
					
				currentAgentWorldModel->setActiveStatus(false); // true: restart, false: no-restart
			
				currentAgentWorldModel->_genomesList.empty();
			}
		}	
	
}


int MedeaOptimWorldObserver::getLifeIterationCount()
{
	return _lifeIterationCount;
}
