/*
 *  MedeaAltUtilityBattleAgentObserver.cpp
 *  Roborobo
 *
 *  Created by Jean-Marc on 15/12/09.
 *
 */


#include "mEDEA-altruism-utility/include/MedeaAltUtilityBattleAgentObserver.h"

#include "World/World.h"
#include "Utilities/Misc.h"
#include "RoboroboMain/roborobo.h"
#include "BehaviorControlArchitectures/EnergyPerceptronControlArchitecture.h"
#include "mEDEA-altruism-utility/include/MedeaAltUtilityPerceptronControlArchitecture.h"
#include "mEDEA-altruism-utility/include/MedeaAltUtilityAgentWorldModel.h"


MedeaAltUtilityBattleAgentObserver::MedeaAltUtilityBattleAgentObserver( RobotAgentWorldModel *__wm )
{
	_wm = (MedeaAltUtilityAgentWorldModel*)__wm;
/*
		gProperties.checkAndGetPropertyValue("g_xStart_EnergyZone",&MedeaAltUtilitySharedData::g_xStart_EnergyZone,true);
		gProperties.checkAndGetPropertyValue("g_yStart_EnergyZone",&MedeaAltUtilitySharedData::g_yStart_EnergyZone,true);
		gProperties.checkAndGetPropertyValue("g_xEnd_EnergyZone",&MedeaAltUtilitySharedData::g_xEnd_EnergyZone,true);
		gProperties.checkAndGetPropertyValue("g_yEnd_EnergyZone",&MedeaAltUtilitySharedData::g_yEnd_EnergyZone,true);
	
		gProperties.checkAndGetPropertyValue("gZoneEnergy_maxHarvestValue",&MedeaAltUtilitySharedData::gZoneEnergy_maxHarvestValue,true);
		gProperties.checkAndGetPropertyValue("gZoneEnergy_minHarvestValue",&MedeaAltUtilitySharedData::gZoneEnergy_minHarvestValue,true);
		gProperties.checkAndGetPropertyValue("gZoneEnergy_maxFullCapacity",&MedeaAltUtilitySharedData::gZoneEnergy_maxFullCapacity,true);
		gProperties.checkAndGetPropertyValue("gZoneEnergy_saturateCapacityLevel",&MedeaAltUtilitySharedData::gZoneEnergy_saturateCapacityLevel,true);
		
		gProperties.checkAndGetPropertyValue("gMaxPenalizationRate",&MedeaAltUtilitySharedData::gMaxPenalizationRate,true);
		if ( MedeaAltUtilitySharedData::gMaxPenalizationRate < 0 || MedeaAltUtilitySharedData::gMaxPenalizationRate > 1 )
		{
			std::cerr << "gMaxPenalizationRate should be defined btw O and 1" << std::endl;
			exit(-1);
		}*/

	if ( !gRadioNetwork)
	{
		std::cout << "Error : gRadioNetwork == false. The swarm online observer need the radio network" << std::endl;
		exit(1);
	}

	gProperties.checkAndGetPropertyValue("synchronization",&_synchronization,true);
		gProperties.checkAndGetPropertyValue("gEnergyMax",&MedeaAltUtilitySharedData::gEnergyMax,true);
		gProperties.checkAndGetPropertyValue("gEnergyInit",&MedeaAltUtilitySharedData::gEnergyInit,true);
		gProperties.checkAndGetPropertyValue("gEnergyRevive",&MedeaAltUtilitySharedData::gEnergyRevive,true);

	if ( gProperties.checkAndGetPropertyValue("gExperimentNumber",&MedeaAltUtilitySharedData::gExperimentNumber,false) == false )
	{
		if ( gVerbose )
			std::cout << "Medea property missing: MedeaAltUtilitySharedData::gExperimentNumber (default value assumed)." << std::endl;
		MedeaAltUtilitySharedData::gExperimentNumber = 0;
	}
		gProperties.checkAndGetPropertyValue("gEvaluationTime",&MedeaAltUtilitySharedData::gEvaluationTime,true);
	_minValue = -1.0;
	_maxValue = 1.0;

	_iterationCount = 0;
	_evaluationCount = 0;
	_side = -1;

	//resetActiveGenome();
}

MedeaAltUtilityBattleAgentObserver::~MedeaAltUtilityBattleAgentObserver()
{
	// nothing to do.
}

void MedeaAltUtilityBattleAgentObserver::reset()
{
	// nothing to do 
}

void MedeaAltUtilityBattleAgentObserver::step()
{
	_iterationCount++;
	if ( _wm->_agentId == 0 )
	{
			if ( MedeaAltUtilitySharedData::gExperimentNumber == 2 )
			{
					if (_wm->_agentId ==  gAgentIndexFocus ) // && gVerbose ) // debug
					{
						std::cout << std::endl << "#### Experiment no.2 starts now. ####" << std::endl;
					}
				
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
					
//	std::cout << "robot #" << _wm->_agentId << "\n" ;

	MedeaAltUtilityPerceptronControlArchitecture* currentBehavior = dynamic_cast<MedeaAltUtilityPerceptronControlArchitecture*>(gWorld->getAgent(_wm->_agentId)->getBehavior());

	if ( ! currentBehavior )
	{
		std::cerr << "Error from robot " << _wm->_agentId << " : the behavior architecture of this robot  isn't a MedeaAltUtilityPerceptronControlArchitecture" << std::endl;
		exit(1);
	}

	/*if (_wm->_agentId == 1)
	{
		std::cout << _key <<std::endl;
	}*/
	if ( gVerbose && gInspectAgent && gAgentIndexFocus == _wm->_agentId )
	{
		//std::cout << "target: " << _wm->getEnergyPointDirectionAngleValue() << std::endl;// " (" << _wm->_agentAbsoluteOrientation << "," << angleToClosestEnergyPoint << ")" << std::endl;
	}

	if ( MedeaAltUtilitySharedData::gExperimentNumber == 1 )
	{
		// * update the energy of the robot (if needed)
	
		Point2d posRobot(_wm->_xReal,_wm->_yReal);
		if ( gEnergyMode )
		{
			for(std::vector<EnergyPoint>::iterator it = gEnergyPoints.begin(); it != gEnergyPoints.end(); it++)
			{

				if( (getEuclidianDistance (posRobot,it->getPosition()) < gEnergyPointRadius) && (it->getActiveStatus()))
				{
					float loadingEnergy = gEnergyPointValue; // test?
					//float loadingEnergy = 5*(1.0/(2.0*sqrt(2.0*M_PI)))*gEnergyPointValue; // test?
					//float loadingEnergy = 5*(1.0/(2.0*sqrt(2.0*M_PI)))*exp(-(pow((_key - it->getKey()),2.0)/(pow(2.0,2.0))))*gEnergyPointValue;

					// update energy level
					_wm->setEnergyLevel(_wm->getEnergyLevel() + loadingEnergy);
					_wm->setDeltaEnergy(_wm->getDeltaEnergy() + loadingEnergy);

					//saturate
					if ( _wm->getEnergyLevel() > MedeaAltUtilitySharedData::gEnergyMax ) // should be at least one lifetime
						_wm->setEnergyLevel(MedeaAltUtilitySharedData::gEnergyMax);
					if ( _wm->getDeltaEnergy() > MedeaAltUtilitySharedData::gEnergyMax )
						_wm->setDeltaEnergy(MedeaAltUtilitySharedData::gEnergyMax);

					gLogFile << "Info(" << gWorld->getIterations() << ") : " << _wm->_agentId
						<< "(" << posRobot.x << "," << posRobot.y << ")" 
						<< " get an energy point at " << it->getPosition().x << "," << it->getPosition().y << " :: Value : " << loadingEnergy  << std::endl;

					it->setActiveStatus(false);
				}
			}
		}
	}
	else 
	{
		if ( MedeaAltUtilitySharedData::gExperimentNumber == 2 )
		{
			// * once per world update (TODO: move to worldobserver)
			
			if (_wm->_agentId ==  0 ) // debug
			{
				int agentsOnZone = 0;
				for ( int i = 0 ; i != gAgentCounter ; i++ )
				{
					int x = (int)(gWorld->getAgent(i)->getWorldModel()->getXReal());
					int y = (int)(gWorld->getAgent(i)->getWorldModel()->getYReal());
					// std::cout << "x =" << x << " , y = " << y << std::endl;

					if ( x >= MedeaAltUtilitySharedData::g_xStart_EnergyZone && y >= MedeaAltUtilitySharedData::g_yStart_EnergyZone && x <= MedeaAltUtilitySharedData::g_xEnd_EnergyZone && y <= MedeaAltUtilitySharedData::g_yEnd_EnergyZone )
						agentsOnZone++;
				}
				// update MedeaAltUtilitySharedData::gZoneEnergy_harvestValue
				//MedeaAltUtilitySharedData::gZoneEnergy_harvestValue = 10; // TODO :: TEMPORARY !!!!!!!!!!TEMPORARY !!!!!!!!!!TEMPORARY !!!!!!!!!!TEMPORARY !!!!!!!!!!TEMPORARY !!!!!!!!!!
			
				if ( gVerbose )
					std::cout << "There are " << agentsOnZone << " agents on the energy zone" <<  std::endl;
			
				/**/
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
				/**/
				
				// debug : MedeaAltUtilitySharedData::gZoneEnergy_harvestValue = MedeaAltUtilitySharedData::gZoneEnergy_maxHarvestValue;
			
			}

		
			// * for each agent -- TODO: could be optimized by merging with previous block in the worldobserve

			if ( _wm->_xReal >= MedeaAltUtilitySharedData::g_xStart_EnergyZone && _wm->_xReal <= MedeaAltUtilitySharedData::g_xEnd_EnergyZone && _wm->_yReal >= MedeaAltUtilitySharedData::g_yStart_EnergyZone && _wm->_yReal <= MedeaAltUtilitySharedData::g_yEnd_EnergyZone )
			{
				float loadingEnergy = MedeaAltUtilitySharedData::gZoneEnergy_harvestValue;
				
				// update energy level
				_wm->setEnergyLevel(_wm->getEnergyLevel() + loadingEnergy);
				_wm->setDeltaEnergy(_wm->getDeltaEnergy() + loadingEnergy);

				// saturate
				if ( _wm->getEnergyLevel() > MedeaAltUtilitySharedData::gEnergyMax ) // assume: need MedeaAltUtilitySharedData::gEvaluationTime to live full life
					_wm->setEnergyLevel(MedeaAltUtilitySharedData::gEnergyMax);
				if ( _wm->getDeltaEnergy() > MedeaAltUtilitySharedData::gEnergyMax ) // assume: need MedeaAltUtilitySharedData::gEvaluationTime to live full life 
					_wm->setDeltaEnergy(MedeaAltUtilitySharedData::gEnergyMax);

				Point2d posRobot(_wm->_xReal,_wm->_yReal);				
				gLogFile << "Info(" << gWorld->getIterations() << ") : " << _wm->_agentId
						<< "(" << posRobot.x << "," << posRobot.y << ")" 
						<< " get an energy point at 0,0 :: Value : " << loadingEnergy  << std::endl; // hack to comply with python log analyser
			}
		}
	}

	// * check energy level

	if ( MedeaAltUtilitySharedData::gExperimentNumber == 1 || MedeaAltUtilitySharedData::gExperimentNumber == 2 )
	{
		if ( _wm->getEnergyLevel() <= 0 )
		{
			_wm->setDeltaEnergy(0); // must be set to zero to avoid broadcasting.
			_wm->setActiveStatus(false);
		}
	}

	// * broadcast the genome (current agent writes its genome to all neighbors
		
	// broadcast only if agent is active (ie. not just revived) and deltaE>0.
	if ( 
			/*( _wm->getDeltaEnergy()>0.0 && _wm->getActiveStatus() == true )
			||
			( MedeaAltUtilitySharedData::gExperimentNumber == 0 && _wm->getActiveStatus() == true )*/
			_wm->getActiveStatus() == true
		)  
	{
		for (int i = 0 ; i < gAgentCounter ; i++)
		{
			if ( ( i != _wm->_agentId ) && ( gRadioNetworkArray[_wm->_agentId][i] ) ) //&& (_wm->getEnergyLevel() > 0.0) ) --> always true as status is active
			{
				MedeaAltUtilityBattleAgentObserver* agentObserver = dynamic_cast<MedeaAltUtilityBattleAgentObserver*>(gWorld->getAgent(i)->getObserver());
				if ( ! agentObserver )
				{
					std::cerr << "Error from robot " << _wm->_agentId << " : the observer of robot " << i << " isn't a MedeaAltUtilityBattleAgentObserver" << std::endl;
					exit(1);
				}
				agentObserver->writeGenome(_currentGenome, _wm->_agentId);
			}
		}
	}

	// * handle genome renewal

	//"restart" the robot in case it runs out of energy -- case: no synchronisation
	/*
	if ( ( _wm->getEnergyLevel()  <= 0.0 ) &&  ( MedeaAltUtilitySharedData::gSynchronization == false ) ){
		logStatus();
		//resetActiveGenome();
		_wm->setEnergyLevel( currentBehavior->getInitialEnergy());
		_wm->setDeltaEnergy(0.0);

		gLogFile << "Info(" << gWorld->getIterations() << ") : Human intervention on robot " << _wm->_agentId << " (Energy)" << std::endl;
		_iterationCount = 0;
		_wm->setActiveStatus(false); // !N.20100407 : inactive robot should get a new genome and move until it imports one from neighbors.
	}
	*/
	
	// case: default for Medea, synchronised
	if( _iterationCount >= MedeaAltUtilitySharedData::gEvaluationTime )
	{
		/**/
		if (_wm->_agentId ==  gAgentIndexFocus && gVerbose) // debug
		{
			std::cout << "agent #" << gAgentIndexFocus << " is renewed" << std::endl;
			std::cout << "agent #" << gAgentIndexFocus << " imported " << _genomesList.size() << " genomes. Energy is " << _wm->getEnergyLevel() << ". Status is "  << _wm->getActiveStatus() << "." <<std::endl;
		}
		/**/

	
		logStatus();
		
		//"revive" the robot in case it runs out of energy
		if ( MedeaAltUtilitySharedData::gExperimentNumber == 1 || MedeaAltUtilitySharedData::gExperimentNumber == 2 )
		{
			if  ( _wm->getEnergyLevel()  <= 0.0 )
			{
				gLogFile << "Info(" << gWorld->getIterations() << ") : Human intervention on robot " << _wm->_agentId << " (Energy)" << std::endl;
				// reformulate (check python script compatibility before): gLogFile << "Info(" << gWorld->getIterations() << ") : robot " << _wm->_agentId << " was revived (human intervention)" << std::endl;

				if (_wm->_agentId == gAgentIndexFocus && gVerbose) // debug
				{
					std::cout << "agent #" << gAgentIndexFocus << " is revived (energy was 0)." << std::endl;
				}

				logStatus();
				//resetActiveGenome();
			
				_wm->setEnergyLevel(MedeaAltUtilitySharedData::gEnergyRevive); // !n : too few?

				_wm->setActiveStatus(false); // true: restart, false: no-restart
			
				_genomesList.empty();
			}
		}
		
		//else // uncomment if restart
		// note: at this point, agent got energy, wether because it was revived or because of remaining energy.
		// case: genome(s) imported, random pick.
		if (_genomesList.size() > 0)
		{
			pickRandomGenome();
			_wm->setActiveStatus(true); // !N.20100407 : revive takes imported genome if any
		}
		// case: no imported genome - wait for new genome.
		else
		{
			gLogFile << "Info(" << gWorld->getIterations() << ") : robot nb." << _wm->_agentId
			//					<< " is trying a whole new genome" << std::endl;
								<< " is waiting for a new genome" << std::endl;

			//resetActiveGenome(); // optional -- could be set to zeroes.
			_wm->setActiveStatus(false); // !N.20100407 : inactive robot must import a genome from others.
		}
		
		//log the genome
		gLogFile << "get active status" << std::endl ;
		if ( _wm->getActiveStatus() == true )
		{
			gLogFile << "Info("<< gWorld->getIterations() <<") : robot nb."<< _wm->_agentId << " use genome :";
			for(unsigned int i=0; i<_wm->_genome.size(); i++)
			{
				gLogFile << std::fixed << std::showpoint<< _wm->_genome[i] << " ";
			}
			gLogFile << std::endl;
		}

		//Re-initialize the main parameters

		if ( MedeaAltUtilitySharedData::gExperimentNumber == 1 || MedeaAltUtilitySharedData::gExperimentNumber == 2 )
		{
			_wm->setDeltaEnergy(0.0); // !n : avant: 10.0
		}
		
		_iterationCount = 0;
		_generationCount ++;
		
		
		if ( _wm->_agentId == 0 )
		{
			if ( !gVerbose )
			{
				//std::cout << ".";
				int activeCount = 0;
				for ( int i = 0 ; i != gAgentCounter ; i++ )
				{
					if ( _wm->getActiveStatus() == true )  
						activeCount++;
				}
				std::cout << "[" << activeCount << "]";
			}
				
			
		}
	}


	
}


void MedeaAltUtilityBattleAgentObserver::pickRandomGenome()
{
		if(_genomesList.size() != 0)
		{
			int randomIndex = rand()%_genomesList.size();
			std::map<int, std::vector<double> >::iterator it = _genomesList.begin();
			while (randomIndex !=0 )
			{
				it ++;
				randomIndex --;
			}
			_currentGenome = (*it).second;
			_wm->_genome = _currentGenome;
			_wm->setNewGenomeStatus(true);
			gLogFile << "Info(" << gWorld->getIterations() << ") : robot nb." << _wm->_agentId << " take the genome from the robot nb." << (*it).first << std::endl;
			_genomesList.clear();
		}
}

void MedeaAltUtilityBattleAgentObserver::writeGenome(std::vector<double> genome, int senderId)
{
	_genomesList[senderId] = genome;
}




void MedeaAltUtilityBattleAgentObserver::loadGenome(std::vector<double> inGenome)
{
	std::cout << std::flush ;
	_wm->_genome.clear();
	for ( unsigned int i = 0 ; i != inGenome.size() ; i++ )
	{
		_wm->_genome.push_back(inGenome[i]);
	}
	_currentGenome = _wm->_genome;
	_wm->setNewGenomeStatus(true);
	_genomesList.clear();
//	MedeaAltUtilityPerceptronControlArchitecture* currentBehavior = dynamic_cast<MedeaAltUtilityPerceptronControlArchitecture*>(gWorld->getAgent(_wm->_agentId)->getBehavior());
	_wm->setDeltaEnergy(10.0);
	_wm->setActiveStatus(true); // true: restart, false: no-restart
}

int MedeaAltUtilityBattleAgentObserver::getSide()
{
	return _side;
}

void MedeaAltUtilityBattleAgentObserver::logStatus()
{
	MedeaAltUtilityPerceptronControlArchitecture* currentBehavior = dynamic_cast<MedeaAltUtilityPerceptronControlArchitecture*>(gWorld->getAgent(_wm->_agentId)->getBehavior());
	if ( ! currentBehavior )
	{
		std::cerr << "Error from robot " << _wm->_agentId << " : the behavior architecture of this robot  isn't a EnergyPerceptronControlArchitecture" << std::endl;
		exit(1);
	}

	//Display the current state of the controller
	gLogFile  << "#GIteration: " << gWorld->getIterations() << " #Robot: " << _wm->_agentId
		<< " #Energy: " <<  _wm->getEnergyLevel()
		<< " #DeltaEnergy: " << _wm->getDeltaEnergy()
		<< " #GenomeListSize: " << _genomesList.size() <<std::endl;
}
