/*
 *  MedeaAltruismReEvoWorldObserver.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 24/05/10.
 *  Copyright 2010.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *  modification for ReEvo : Jean-Marc 2/4/2011
 *
 */

#include "Observers/AgentObserver.h"
#include "Observers/WorldObserver.h"

#include "mEDEA-altruism/include/MedeaAltruismReEvoWorldObserver.h"
#include "mEDEA-altruism/include/MedeaAltruismReEvoAgentObserver.h"

#include "World/World.h"
#include <algorithm>

MedeaAltruismReEvoWorldObserver::MedeaAltruismReEvoWorldObserver( World* __world ) : WorldObserver( __world )
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
	
	gProperties.checkAndGetPropertyValue("fixedCost",&fixedCost,true);

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
	
	_firstStep = true;
	loadGenomes();
}

MedeaAltruismReEvoWorldObserver::~MedeaAltruismReEvoWorldObserver()
{
	// nothing to do.
}

void MedeaAltruismReEvoWorldObserver::reset()
{
	// nothing to do.
}

void MedeaAltruismReEvoWorldObserver::step()
{

	if (_firstStep)
	{
		//give genomes to agents as long as there is genomes available
		for (unsigned int i = 0 ; i < _genomesToReplay.size() ; i++)
		{
			MedeaAltruismReEvoAgentObserver* agentObserver = dynamic_cast<MedeaAltruismReEvoAgentObserver*>(gWorld->getAgent(i)->getObserver());
			if ( ! agentObserver)
			{
				std::cerr << " Error from MedeaAltruismReEvoWorldObserver : the observer of robot " << i << " isn't a MedeaAltruismReEvoAgentObserver " << std ::endl;
				exit(1);
			}
			agentObserver->loadGenome(_genomesToReplay[i]);
		}

		//The remaining agents aren't active, and are listening for new genomes
		for (int i =_genomesToReplay.size() ; i < gNbOfAgents ; i++ )
		{
			MedeaAltruismAgentWorldModel* agentWorldModel = dynamic_cast<MedeaAltruismAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
			if ( ! agentWorldModel)
			{
				std::cerr << " Error from MedeaAltruismReEvoWorldObserver : the worldModel of robot " << i << " isn't a MedeaAltruismAgentWorldModel " << std ::endl;
				exit(1);
			}
			agentWorldModel->setActiveStatus(false);
			agentWorldModel->resetActiveGenome();
			agentWorldModel->setWaitingAfterLifeSynchronization(false);
		}
		_firstStep = false ;
	}

	// ***
	// * update iteration and generation counters 
	// ***
	
	_lifeIterationCount++;

	if( _lifeIterationCount >= MedeaAltruismSharedData::gEvaluationTime ) // go to next generation.
	{
		// * monitoring: count number of active agents.

		int activeCount = 0;
		for ( int i = 0 ; i != gAgentCounter ; i++ )
		{
			if ( (dynamic_cast<MedeaAltruismAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel()))->getActiveStatus() == true )
				activeCount++;
		}
		if ( !gVerbose )
		{
			std::cout << "[" << activeCount << "]";
		}
		gLogFile << gWorld->getIterations() << " : activeCount " << activeCount << std::endl;

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

void MedeaAltruismReEvoWorldObserver::loadGenomes()
{
	int nbHiddenNeurons;
	gProperties.checkAndGetPropertyValue("nbHiddenNeurons",&nbHiddenNeurons,true);
	int nbInput = 8 + 5 ; //sensors + floorSensor + energyDirection + energyLevel + energyDirection + bias
	int nbOutput = 3 ; // rotation + velocity + energyHarvestingRate
	int nbGene = ( nbInput * nbHiddenNeurons ) + ( nbHiddenNeurons * nbOutput) + nbOutput ; // from input to hidden layer + from hiddenLayer to output + from bias to output
	for (int agentId = 0 ; agentId < gNbOfAgents ; agentId ++ )
	{
		std::vector<double> tmpGenome;
		for (int i=0 ; i< nbGene ; i++)
		{
			double gene = 0;
			std::stringstream out;
			std::string s = "";
			s += "genomeToReplay[";
			out<<agentId;
			s+=out.str();
			s +="][";
			std::stringstream out2;
			out2<<i ;
			s+=out2.str();
			s += "]";


			if ( gProperties.hasProperty ( s ) )
				convertFromString<double>(gene, gProperties.getProperty( s ), std::dec);
			else
			{
				//std::cout << "[error] MedeaAltruismReEvoWorldObserver :: " << s << " is missing"<< std::endl;
				//exit(1);
				break;
			}
			tmpGenome.push_back(gene);
		}
		if (tmpGenome.size() == 0)
		{
			break; //if there is no gene in the genome that means the last genome has already been described
		}
		_genomesToReplay.push_back(tmpGenome);
	}
}


// * 
// * update energy level for each agents (ONLY active agents) (only in experimental setups featuring energy items)
// *
void MedeaAltruismReEvoWorldObserver::updateAllAgentsEnergyLevel()
{	
	
	for ( int i = 0 ; i != gAgentCounter ; i++ ) // for each agent
	{
		MedeaAltruismAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaAltruismAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
		
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
						//float loadingEnergy = std::max( 0.0 , std::min( double(gEnergyPointValue), MedeaAltruismSharedData::gEnergyMax - currentAgentWorldModel->getEnergyLevel() ) - fixedCost);
						//float loadingEnergy = 5*(1.0/(2.0*sqrt(2.0*M_PI)))*gEnergyPointValue; // test?
						//float loadingEnergy = 5*(1.0/(2.0*sqrt(2.0*M_PI)))*exp(-(pow((_key - it->getKey()),2.0)/(pow(2.0,2.0))))*gEnergyPointValue;
	
						gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId
							<< " get " << loadingEnergy  << " Before " << currentAgentWorldModel->getEnergyLevel() <<std::endl;

						// update energy level
						currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel() + loadingEnergy);
						currentAgentWorldModel->setDeltaEnergy(currentAgentWorldModel->getDeltaEnergy() + loadingEnergy);
	
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

			if (currentAgentWorldModel->_agentId == gAgentIndexFocus && gVerbose) // debug
			{
				std::cout << "agent #" << gAgentIndexFocus << " is revived (energy was 0)." << std::endl;
			}

			
			currentAgentWorldModel->resetActiveGenome();
		
			currentAgentWorldModel->setEnergyLevel(MedeaAltruismSharedData::gEnergyRevive); 
			currentAgentWorldModel->setDeltaEnergy(0.0); 

			currentAgentWorldModel->setActiveStatus(false); // true: restart, false: no-restart
			currentAgentWorldModel->setWaitingAfterLifeSynchronization(true);
		
			currentAgentWorldModel->_genomesList.empty();
		}
	}	
}


int MedeaAltruismReEvoWorldObserver::getLifeIterationCount()
{
	return _lifeIterationCount;
}
