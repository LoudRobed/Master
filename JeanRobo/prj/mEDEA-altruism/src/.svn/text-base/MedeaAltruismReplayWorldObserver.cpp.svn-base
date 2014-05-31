/*
 *  MedeaAltruismReplayWorldObserver.cpp
 *  roborobo-online
 *
 *  Created by Jean-Marc on 20/04/10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *  modified on 25/10/2010
 *
 */

#include "Observers/AgentObserver.h"
#include "Observers/WorldObserver.h"

#include "mEDEA-altruism/include/MedeaAltruismReplayWorldObserver.h"
#include "mEDEA-altruism/include/MedeaAltruismReplayAgentObserver.h"

#include "World/World.h"
#include <algorithm>

MedeaAltruismReplayWorldObserver::MedeaAltruismReplayWorldObserver( World *__world ) : WorldObserver( __world )
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
	
	gProperties.checkAndGetPropertyValue("gDeadTime",&MedeaAltruismSharedData::gDeadTime,true);
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
	
	gProperties.checkAndGetPropertyValue("fixedCost",&fixedCost,true);
	gProperties.checkAndGetPropertyValue("exponentialFactor",&exponentialFactor,true);

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

	_firstStep = true;
	loadGenome();
}

MedeaAltruismReplayWorldObserver::~MedeaAltruismReplayWorldObserver()
{
	// nothing to do.
}

void MedeaAltruismReplayWorldObserver::reset()
{
	// nothing to do.
}

void MedeaAltruismReplayWorldObserver::step()
{
	if (_firstStep)
	{
		MedeaAltruismReplayAgentObserver* agentObserver = dynamic_cast<MedeaAltruismReplayAgentObserver*>(gWorld->getAgent(0)->getObserver());
		if ( ! agentObserver)
		{
			std::cerr << " Error from MedeaAltruismReplayWorldObserver : the observer of robot 0 isn't a MedeaAltruismReplayAgentObserver " << std ::endl;
			exit(1);
		}
		agentObserver->loadGenome(_genomeToReplay);
		_firstStep = false ;
	}

	_lifeIterationCount++;

	if( _lifeIterationCount >= MedeaAltruismSharedData::gEvaluationTime ) // print mEDEA state
	{
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
}

void MedeaAltruismReplayWorldObserver::loadGenome()
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
			std::cout << "[error] MedeaAltruismReplayWorldObserver :: The gene " << i << " is missing from genomeToRead "<< std::endl;
			exit(1);
		}
		_genomeToReplay.push_back(gene);
	}
}


// * 
// * update energy level for each agents (ONLY active agents) (only in experimental setups featuring energy items)
// *
void MedeaAltruismReplayWorldObserver::updateAllAgentsEnergyLevel()
{	
	
	for ( int i = 0 ; i != gAgentCounter ; i++ ) // for each agent
	{
		MedeaAltruismAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaAltruismAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
		
		// * check energy level. Becomes inactive if zero.
	/*	
		if ( currentAgentWorldModel->getEnergyLevel() <= 0 )
		{
			currentAgentWorldModel->setDeltaEnergy(0);
			currentAgentWorldModel->setActiveStatus(false);
			currentAgentWorldModel->setWaitingAfterLifeSynchronization(true);
		}*/

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
						//float loadingEnergy = std::max( 0.0 , std::min( double(gEnergyPointValue), MedeaAltruismSharedData::gEnergyMax - currentAgentWorldModel->getEnergyLevel() ) - fixedCost);
						//float loadingEnergy = 5*(1.0/(2.0*sqrt(2.0*M_PI)))*gEnergyPointValue; // test?
						//float loadingEnergy = 5*(1.0/(2.0*sqrt(2.0*M_PI)))*exp(-(pow((_key - it->getKey()),2.0)/(pow(2.0,2.0))))*gEnergyPointValue;

						double energyMissing = MedeaAltruismSharedData::gEnergyMax-currentAgentWorldModel->getEnergyLevel();
						double costMeasure = 0.0;

						if ( currentAgentWorldModel->getEnergyLevel() + loadingEnergy < MedeaAltruismSharedData::gEnergyMax )
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

						// update energy level
						currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel() + loadingEnergy);
						currentAgentWorldModel->setDeltaEnergy(currentAgentWorldModel->getDeltaEnergy() + loadingEnergy);
	
						//saturate
						if ( currentAgentWorldModel->getEnergyLevel() > MedeaAltruismSharedData::gEnergyMax ) // assume: need MedeaAltruismSharedData::gEvaluationTime to live full life
							currentAgentWorldModel->setEnergyLevel(MedeaAltruismSharedData::gEnergyMax);
	
						double loadingRatio = loadingEnergy/gEnergyPointValue;
						double exponentialRespawn = exp(loadingRatio*exponentialFactor)*(MedeaAltruismSharedData::gHighestBoundRespawn/exp(exponentialFactor));
						it->setRespawnLag(exponentialRespawn);
						//it->setRespawnLag((loadingEnergy/gEnergyPointValue)*MedeaAltruismSharedData::gHighestBoundRespawn);
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
	

		if  ( currentAgentWorldModel->getEnergyLevel()  <= 0.0 )
		{
			//gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId << " die" << std::endl;
			
			currentAgentWorldModel->resetActiveGenome();
			currentAgentWorldModel->setMaturity(1);
		
			currentAgentWorldModel->setEnergyLevel(MedeaAltruismSharedData::gEnergyRevive); 
			currentAgentWorldModel->setDeltaEnergy(0.0); 
			currentAgentWorldModel->setLifeTime(0);

			currentAgentWorldModel->setActiveStatus(false);
			currentAgentWorldModel->setWaitForGenome(false);
		
			currentAgentWorldModel->_genomesList.empty();
		}
	}	
}


int MedeaAltruismReplayWorldObserver::getLifeIterationCount()
{
	return _lifeIterationCount;
}
