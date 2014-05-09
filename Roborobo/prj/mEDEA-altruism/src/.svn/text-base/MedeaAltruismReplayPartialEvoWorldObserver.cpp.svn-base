/*
 *  MedeaAltruismReplayPartialEvoWorldObserver.cpp
 *  roborobo-online
 *
 *  Created by Jean-Marc on 20/04/10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *  modified on 25/10/2010
 *  moved in partial evo by Jean-Marc on 09/12/2010
 *
 */

#include "Observers/AgentObserver.h"
#include "Observers/WorldObserver.h"

#include "World/World.h"

#include "mEDEA-altruism/include/MedeaAltruismReplayPartialEvoWorldObserver.h"
#include "mEDEA-altruism/include/MedeaAltruismReplayPartialEvoAgentObserver.h"


MedeaAltruismReplayPartialEvoWorldObserver::MedeaAltruismReplayPartialEvoWorldObserver( World *__world ) :
	WorldObserver( __world )
{
	_world = __world;

	// ==== loading project-specific properties 

	gProperties.checkAndGetPropertyValue("gSwarmOnlineObsUsed",&MedeaAltruismSharedData::gSwarmOnlineObsUsed,true);
	gProperties.checkAndGetPropertyValue("gDynamicSigma",&MedeaAltruismSharedData::gDynamicSigma,true);
	gProperties.checkAndGetPropertyValue("gSigmaMin",&MedeaAltruismSharedData::gSigmaMin,true);
	gProperties.checkAndGetPropertyValue("gProbAdd",&MedeaAltruismSharedData::gProbAdd,true);
	gProperties.checkAndGetPropertyValue("gProbSub",&MedeaAltruismSharedData::gProbSub,true);
	gProperties.checkAndGetPropertyValue("gDynaStep",&MedeaAltruismSharedData::gDynaStep,true);
	gProperties.checkAndGetPropertyValue("gSigmaRef",&MedeaAltruismSharedData::gSigmaRef,true);
	gProperties.checkAndGetPropertyValue("gSigmaMax",&MedeaAltruismSharedData::gSigmaMax,true);
	gProperties.checkAndGetPropertyValue("gProbRef",&MedeaAltruismSharedData::gProbRef,true);
	gProperties.checkAndGetPropertyValue("gProbMax",&MedeaAltruismSharedData::gProbMax,true);
	gProperties.checkAndGetPropertyValue("gEvaluationTime",&MedeaAltruismSharedData::gEvaluationTime,true);
	gProperties.checkAndGetPropertyValue("gDriftEvaluationRate",&MedeaAltruismSharedData::gDriftEvaluationRate,true);
	gProperties.checkAndGetPropertyValue("gInitLock",&MedeaAltruismSharedData::gInitLock,true);
	gProperties.checkAndGetPropertyValue("gDriftLock",&MedeaAltruismSharedData::gDriftLock,true);
	gProperties.checkAndGetPropertyValue("gMaxKeyRange",&MedeaAltruismSharedData::gMaxKeyRange,true);
	gProperties.checkAndGetPropertyValue("gDeltaKey",&MedeaAltruismSharedData::gDeltaKey,true);
	gProperties.checkAndGetPropertyValue("gSynchronization",&MedeaAltruismSharedData::gSynchronization,true);

	gProperties.checkAndGetPropertyValue("g_xStart_EnergyZone",&MedeaAltruismSharedData::g_xStart_EnergyZone,true);
	gProperties.checkAndGetPropertyValue("g_yStart_EnergyZone",&MedeaAltruismSharedData::g_yStart_EnergyZone,true);
	gProperties.checkAndGetPropertyValue("g_xEnd_EnergyZone",&MedeaAltruismSharedData::g_xEnd_EnergyZone,true);
	gProperties.checkAndGetPropertyValue("g_yEnd_EnergyZone",&MedeaAltruismSharedData::g_yEnd_EnergyZone,true);

	gProperties.checkAndGetPropertyValue("gZoneEnergy_maxHarvestValue",&MedeaAltruismSharedData::gZoneEnergy_maxHarvestValue,true);
	gProperties.checkAndGetPropertyValue("gZoneEnergy_minHarvestValue",&MedeaAltruismSharedData::gZoneEnergy_minHarvestValue,true);
	gProperties.checkAndGetPropertyValue("gZoneEnergy_maxFullCapacity",&MedeaAltruismSharedData::gZoneEnergy_maxFullCapacity,true);
	gProperties.checkAndGetPropertyValue("gZoneEnergy_saturateCapacityLevel",&MedeaAltruismSharedData::gZoneEnergy_saturateCapacityLevel,true);
	
	gProperties.checkAndGetPropertyValue("gEnergyMax",&MedeaAltruismSharedData::gEnergyMax,true);
	gProperties.checkAndGetPropertyValue("gEnergyInit",&MedeaAltruismSharedData::gEnergyInit,true);
	gProperties.checkAndGetPropertyValue("gEnergyRevive",&MedeaAltruismSharedData::gEnergyRevive,true);
	
	gProperties.checkAndGetPropertyValue("gMaxPenalizationRate",&MedeaAltruismSharedData::gMaxPenalizationRate,true);
	if ( MedeaAltruismSharedData::gMaxPenalizationRate < 0 || MedeaAltruismSharedData::gMaxPenalizationRate > 1 )
	{
		std::cerr << "gMaxPenalizationRate should be defined btw O and 1" << std::endl;
		exit(-1);
	}
	
	gProperties.checkAndGetPropertyValue("gDynamicRespawn",&MedeaAltruismSharedData::gDynamicRespawn,true); // forced, in this setup.
	gProperties.checkAndGetPropertyValue("gThresholdIncreaseRespawn",&MedeaAltruismSharedData::gThresholdIncreaseRespawn,true); 
	gProperties.checkAndGetPropertyValue("gLowestBoundRespawn",&MedeaAltruismSharedData::gLowestBoundRespawn,true); 
	gProperties.checkAndGetPropertyValue("gHighestBoundRespawn",&MedeaAltruismSharedData::gHighestBoundRespawn,true); 
		

	// ====

	if ( !gRadioNetwork)
	{
		std::cout << "Error : gRadioNetwork == false. The swarm online observer need the radio network" << std::endl;
		exit(1);
	}
	
	if ( !MedeaAltruismSharedData::gSwarmOnlineObsUsed)
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



	_firstStep = true;
	loadGenome();
	movementQuantity = 0.0;
}

MedeaAltruismReplayPartialEvoWorldObserver::~MedeaAltruismReplayPartialEvoWorldObserver()
{
	// nothing to do.
}

void MedeaAltruismReplayPartialEvoWorldObserver::reset()
{
	// nothing to do.
}

void MedeaAltruismReplayPartialEvoWorldObserver::step()
{
	if (_firstStep)
	{
		for (int i = 0 ; i != gAgentCounter ; i++)
		{
			MedeaAltruismReplayPartialEvoAgentObserver* agentObserver = dynamic_cast<MedeaAltruismReplayPartialEvoAgentObserver*>(gWorld->getAgent(i)->getObserver());
			if ( ! agentObserver)
			{
				std::cerr << " Error from MedeaAltruismReplayPartialEvoWorldObserver : the observer of robot 0 isn't a MedeaAltruismReplayPartialEvoAgentObserver " << std ::endl;
				exit(1);
			}
			agentObserver->loadGenome(_genomeToReplay);
			MedeaAltruismReplayPartialEvoAgentWorldModel* agentWorldModel = dynamic_cast<MedeaAltruismReplayPartialEvoAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
			if (agentWorldModel)
			{
				agentWorldModel->setPrevX(agentWorldModel->getXReal());
				agentWorldModel->setPrevY(agentWorldModel->getYReal());
			}
		}
		_firstStep = false ;
	}

	_lifeIterationCount++;

	if( _lifeIterationCount >= MedeaAltruismSharedData::gEvaluationTime ) // go to next generation.
	{
		// * monitoring: count number of active agents.

		int activeCount = 0;
		for ( int i = 0 ; i != gAgentCounter ; i++ )
		{
			if ( (dynamic_cast<MedeaAltruismReplayPartialEvoAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel()))->getActiveStatus() == true )
				activeCount++;
		}
		if ( !gVerbose )
		{
			std::cout << "[" << activeCount << "]";
		}
		gLogFile << gWorld->getIterations() << " : activeCount " << activeCount << std::endl;

		gLogFile << gWorld->getIterations() << " : movQu " << movementQuantity << std::endl;
		movementQuantity = 0.0;

		int energyPointActiveCount = 0;
		for(std::vector<EnergyPoint>::iterator it = gEnergyPoints.begin(); it != gEnergyPoints.end(); it++)
		{
			if (it->getActiveStatus() == true)
			{
				energyPointActiveCount ++;
			}
		}
		gLogFile << gWorld->getIterations() << " : EP activeCount " << energyPointActiveCount << std::endl;
	
	
		// * update iterations and generations counters

		_lifeIterationCount = 0;
		_generationCount++;

	}

	// * update energy level for each agents (ONLY active agents)
	
	updateAllAgentsEnergyLevel();

	for ( int i = 0 ; i != gAgentCounter ; i++ )
	{
		double dx = 0.0;
		double dy = 0.0;
		MedeaAltruismReplayPartialEvoAgentWorldModel* agentWorldModel = dynamic_cast<MedeaAltruismReplayPartialEvoAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
		dx = agentWorldModel->getPrevX() - agentWorldModel->getXReal();
		dy = agentWorldModel->getPrevY() - agentWorldModel->getYReal();
		movementQuantity += sqrt(pow(dx,2)+pow(dy,2))/gAgentCounter;
		agentWorldModel->setPrevX(agentWorldModel->getXReal());
		agentWorldModel->setPrevY(agentWorldModel->getYReal());
	}
}

void MedeaAltruismReplayPartialEvoWorldObserver::loadGenome()
{
	int nbHiddenNeurons;
	gProperties.checkAndGetPropertyValue("nbHiddenNeurons",&nbHiddenNeurons,true);
	int nbInput = 8 + 5 ; //sensors + floorSensor + energyDirection + energyLevel + energyDirection + bias
	int nbOutput = 3 ; // rotation + velocity + energyHarvestingRate
	int nbGene = ( nbInput * nbHiddenNeurons ) + ( nbHiddenNeurons * nbOutput) + nbOutput ; // from input to hidden layer + from hiddenLayer to output + from bias to output
	for (int i=0 ; i< nbGene ; i++)
	{
		double gene = 0;
		std::stringstream out;
		std::string s = "";
		s += "genomeToReplay[";
		out<<i;
		s+=out.str();
		s +="]";

		if ( gProperties.hasProperty ( s ) )
			convertFromString<double>(gene, gProperties.getProperty( s ), std::dec);
		else
		{
			std::cout << "[error] MedeaAltruismReplayPartialEvoWorldObserver :: The gene " << i << " is missing from genomeToRead "<< std::endl;
			exit(1);
		}
		_genomeToReplay.push_back(gene);
	}
}


// * 
// * update energy level for each agents (ONLY active agents) (only in experimental setups featuring energy items)
// *
void MedeaAltruismReplayPartialEvoWorldObserver::updateAllAgentsEnergyLevel()
{	
	
	for ( int i = 0 ; i != gAgentCounter ; i++ ) // for each agent
	{
		MedeaAltruismReplayPartialEvoAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaAltruismReplayPartialEvoAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
		
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
							<< " get " << loadingEnergy  << " Before " << currentAgentWorldModel->getEnergyLevel() <<std::endl;

						// update energy level
						currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel() + loadingEnergy);
						currentAgentWorldModel->setDeltaEnergy(currentAgentWorldModel->getDeltaEnergy() + loadingEnergy);
						currentAgentWorldModel->increaseTotalEnergyHarvested(loadingEnergy);
	
						//saturate
						if ( currentAgentWorldModel->getEnergyLevel() > MedeaAltruismSharedData::gEnergyMax ) // assume: need MedeaAltruismSharedData::gEvaluationTime to live full life
							currentAgentWorldModel->setEnergyLevel(MedeaAltruismSharedData::gEnergyMax);
	
	
						it->setRespawnLag((loadingEnergy/gEnergyPointValue)*MedeaAltruismSharedData::gHighestBoundRespawn);
						it->setActiveStatus(false);
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
			gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId << " Restart" << std::endl;
			// reformulate (check python script compatibility before): gLogFile << "Info(" << gWorld->getIterations() << ") : robot " << _wm->_agentId << " was revived (human intervention)" << std::endl;

			if (currentAgentWorldModel->_agentId == gAgentIndexFocus && gVerbose) // debug
			{
				std::cout << "agent #" << gAgentIndexFocus << " is revived (energy was 0)." << std::endl;
			}
			
			currentAgentWorldModel->resetActiveGenome();
		
			currentAgentWorldModel->setEnergyLevel(MedeaAltruismSharedData::gEnergyRevive); // !n : too few?

			currentAgentWorldModel->setActiveStatus(false); // true: restart, false: no-restart
			currentAgentWorldModel->setWaitingAfterLifeSynchronization(true);
		
			currentAgentWorldModel->_genomesList.empty();
		}
	}	
}


int MedeaAltruismReplayPartialEvoWorldObserver::getLifeIterationCount()
{
	return _lifeIterationCount;
}
