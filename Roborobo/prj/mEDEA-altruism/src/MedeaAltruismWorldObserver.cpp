/*:
 *  MedeaAltruismWorldObserver.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 24/05/10.
 *  Copyright 2010.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */

#include "Observers/AgentObserver.h"
#include "Observers/WorldObserver.h"
#include "mEDEA-altruism/include/MedeaAltruismAgentObserver.h"
#include "mEDEA-altruism/include/MedeaAltruismWorldObserver.h"

#include "World/World.h"
#include <algorithm>
//bool _firstStep = true;
//std::vector< std::vector<double> > _genomesToReplay;
MedeaAltruismWorldObserver::MedeaAltruismWorldObserver( World* __world ) : WorldObserver( __world )
{
	_world = __world;
	_firstStep = true;
	// ==== loading project-specific properties 
	std::cout << "Loading properties" << std::endl;
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

	gProperties.checkAndGetPropertyValue("selectionScheme",&MedeaAltruismSharedData::selectionScheme,true);
	gProperties.checkAndGetPropertyValue("harvestingScheme",&MedeaAltruismSharedData::harvestingScheme,true);
	//gDonationThreshold is the upper limit for the value of Donation before a donation is being made.
	gProperties.checkAndGetPropertyValue("gDonationThreshold",&MedeaAltruismSharedData::gDonationThreshold,true);


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
	std::cout << "Donation threshold: " << MedeaAltruismSharedData::gDonationThreshold << std::endl;
	// * iteration and generation counters
	loadGenomes();	
	_lifeIterationCount = -1;
	_agentPointCount = -0;
}
void MedeaAltruismWorldObserver::loadGenomes()
{
	std::cout << "Loading genomes from properties file" << std::endl;
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
            s += "listOfGenomes[";
            out<<agentId;
            s+=out.str();
            s +="][";
            std::stringstream out2;
            out2<<i ;
            s+=out2.str();
            s += "]";

	//	std::cout << "Checking if property exists: " << s << std::endl;
            if ( gProperties.hasProperty ( s ) ){
	//	std::cout << "gProperties has propertiy" << std::endl;
                convertFromString<double>(gene, gProperties.getProperty( s ), std::dec);
}
            else
            {
	//	std::cout << "Property not found" << std::endl;
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
MedeaAltruismWorldObserver::~MedeaAltruismWorldObserver()
{
	// nothing to do.
}

void MedeaAltruismWorldObserver::reset()
{
	// nothing to do.
}

void MedeaAltruismWorldObserver::step()
{

	// ***
	// * update iteration and generation counters + switch btw experimental setups if required
	// ***
if (_firstStep)
    {
        //give genomes to agents as long as there is genomes available
        for (unsigned int i = 0 ; i < _genomesToReplay.size() ; i++)
        {
            MedeaAltruismAgentObserver* agentObserver = dynamic_cast<MedeaAltruismAgentObserver*>(gWorld->getAgent(i)->getObserver());
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
	_lifeIterationCount++;

	if( _lifeIterationCount >= MedeaAltruismSharedData::gEvaluationTime ) // print mEDEA state
	{
		// * monitoring: count number of active agents.
		// * monitoring: sum the total amount of energy in the system.
		int totalEnergy = 0;
		double activeCount = 0;
		gLogFile << gWorld->getIterations() << " : active " ;
		for ( int i = 0 ; i != gAgentCounter ; i++ )
		{
			if ( (dynamic_cast<MedeaAltruismAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel()))->getActiveStatus() == true )
			{
				activeCount++;
				gLogFile << i << " ";
				totalEnergy += (dynamic_cast<MedeaAltruismAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel()))->getEnergyLevel(); 
			}
		}
		gLogFile << "\n" ;
		//gStatFile << activeCount << std::endl;
		if ( !gVerbose )
		{
//			std::cout << "[" << activeCount << "]";
		}
		gLogFile << gWorld->getIterations() << " : activeCount " << activeCount << std::endl;

		if(activeCount<=0)
		{
			gLogFile.close();
			exit(0);
		}
		//Sum active energy from EPs
		int energyPointActiveCount = 0;
		for(std::vector<EnergyPoint>::iterator it = gEnergyPoints.begin(); it != gEnergyPoints.end(); it++)
		{
			if (it->getActiveStatus() == true)
			{
				energyPointActiveCount ++;
				totalEnergy += it->getEnergyPointValue(); 
			}
		
	

			

		}
		gLogFile << gWorld->getIterations() << " : EP activeCount " << energyPointActiveCount << std::endl;
		gLogFile << gWorld->getIterations() << " : Entropy " << totalEnergy << std::endl;	
		gLogFile << gWorld->getIterations() << " : Agent Points " << _agentPointCount << std::endl;	
		std::cout << " Agent Points: " << _agentPointCount << std::endl;
		// * update iterations counter
		_lifeIterationCount = 0;
		_agentPointCount = 0;	
	}

	// * update energy level for each agents (ONLY active agents)
	
	updateAllAgentsEnergyLevel();
}


// * 
// * update energy level for each agents (ONLY active agents) (only in experimental setups featuring energy items)
// *
void MedeaAltruismWorldObserver::updateAllAgentsEnergyLevel()
{	
	int gAgentPoints = 0; //The number of agent created energy points.
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
					if( (getEuclidianDistance (posRobot,it->getPosition()) < gEnergyPointRadius) && (it->getActiveStatus())  && it->getId() != currentAgentWorldModel->_agentId+gMaxEnergyPoints)
					{
						float loadingEnergy = 0.0;
						if ( MedeaAltruismSharedData::harvestingScheme.compare("dynCost") == 0)
						{
							loadingEnergy = currentAgentWorldModel->getEnergyHarvestingRate() * gEnergyPointValue;
						}
						else if ( MedeaAltruismSharedData::harvestingScheme.compare("fixedCost") == 0)
						{
							loadingEnergy = std::max( 0.0 , std::min( double(gEnergyPointValue), MedeaAltruismSharedData::gEnergyMax - currentAgentWorldModel->getEnergyLevel() ) - fixedCost);
						}
						else
						{
							gLogFile << "harvesting scheme unknown" << std::endl;
							exit(1);
						}
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
	
						//double loadingRatio = loadingEnergy/gEnergyPointValue;
						//double exponentialRespawn = exp(loadingRatio*exponentialFactor)*(MedeaAltruismSharedData::gHighestBoundRespawn/exp(exponentialFactor));
						//it->setRespawnLag(exponentialRespawn);
						it->setRespawnLag((loadingEnergy/gEnergyPointValue)*MedeaAltruismSharedData::gHighestBoundRespawn);
						it->setActiveStatus(false);
						//std::cout << "Agent " << currentAgentWorldModel->_agentId << " ate an enrgypoint made by " << it->getId()-gMaxEnergyPoints << " In iteration " << gWorld->getIterations() << std::endl;
					}
				}
			}
			double thresh = MedeaAltruismSharedData::gDonationThreshold;
			//double thresh = 0.99;
			double donationRate = currentAgentWorldModel->getEnergyDonation();
			double donationPenalty = penalty();
			
			if(donationRate > thresh){
			
				EnergyPoint ep(currentAgentWorldModel->_agentId+gMaxEnergyPoints,currentAgentWorldModel->_xReal,currentAgentWorldModel->_yReal);
			//	ep.setEnergyPointValueIsLocal(true);
			//	ep.setRespawnLagMethodIsLocal(true);
			//	ep.setAgentGenerated(true);
			
				double donation = ((1.0-donationRate)/(1.0-thresh))*MedeaAltruismSharedData::gEnergyMax;
				
				if(currentAgentWorldModel->getEnergyLevel() < donation){
					ep.setEnergyPointValue( currentAgentWorldModel->getEnergyLevel());
					 }
				else{
					ep.setEnergyPointValue(donation);
					}	

				currentAgentWorldModel->setEnergyLevel(currentAgentWorldModel->getEnergyLevel()-ep.getEnergyPointValue()-donationPenalty);
				_world->addEnergyPoint(ep);
			//	currentAgentWorldModel->setEnergyDonation(-1.0); //Resets donation to 0;
				_agentPointCount ++;

		double activeCount = 0;
		for ( int i = 0 ; i != gAgentCounter ; i++ )
		{
			if ( (dynamic_cast<MedeaAltruismAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel()))->getActiveStatus() == true )
			{
				activeCount++;
			}
		}
				gStatFile << gWorld->getIterations()  << "," << currentAgentWorldModel->_agentId << "," << currentAgentWorldModel->getEnergyLevel()+donation << "," << donation << "," << activeCount << std::endl; 
//TODO: Log genetic relatedness to other agents close by.
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
			gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId << " die" << std::endl;
			gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId << " lf " << currentAgentWorldModel->getLifeTime() << std::endl;
			
			currentAgentWorldModel->resetActiveGenome();
			currentAgentWorldModel->setMaturity(1);
		
			currentAgentWorldModel->setEnergyLevel(MedeaAltruismSharedData::gEnergyRevive); 
			currentAgentWorldModel->setDeltaEnergy(0.0); 
			gLogFile << gWorld->getIterations() << " : " << currentAgentWorldModel->_agentId << " a " << (currentAgentWorldModel->_idlenessTracker.getAverageBoxesIdleness() / currentAgentWorldModel->getLifeTime()) * 100000 << std::endl;
			currentAgentWorldModel->setLifeTime(0);

			currentAgentWorldModel->setActiveStatus(false);
			currentAgentWorldModel->setWaitForGenome(false);
		
			currentAgentWorldModel->_genomesList.empty();
		}
	}	
			gLogFile << gWorld->getIterations() << " : " << "Agent Points Created " << gAgentPoints << std::endl;
			//std::cout << "Agent[" << activeCount << "]";
}

double MedeaAltruismWorldObserver::penalty(){

	return 0;
}

int MedeaAltruismWorldObserver::getLifeIterationCount()
{
	return _lifeIterationCount;
}
