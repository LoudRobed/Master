/**
 * @file
 * @author Leo Cazenille <leo.cazenille@gmail.com>
 * TODO : Add formal description
 * History :
 *
 *
 */


#include "Observers/AgentObserver.h"
#include "Observers/WorldObserver.h"
#include "mEDEA-HGT/include/MedeaHGTWorldObserver.h"
#include "World/World.h"


MedeaHGTWorldObserver::MedeaHGTWorldObserver( World* world ) : WorldObserver( world )
{

	_world = world;


	// ==== loading project-specific properties

	// Populations Stuffs
	gProperties.checkAndGetPropertyValue("gInitialNumberOfPopulations", &MedeaHGTSharedData::gInitialNumberOfPopulations, true);
	gProperties.checkAndGetPropertyValue("gMaxNumberOfPopulations", &MedeaHGTSharedData::gMaxNumberOfPopulations, true);
	gProperties.checkAndGetPropertyValue("gAutoIncreaseNumberOfPopulation", &MedeaHGTSharedData::gAutoIncreaseNumberOfPopulation, true);
	gProperties.checkAndGetPropertyValue("gAutoIncreaseNumberOfPopulationPeriod", &MedeaHGTSharedData::gAutoIncreaseNumberOfPopulationPeriod, true);

	// HGT Stuffs
	gProperties.checkAndGetPropertyValue("gActiveHGTBetweenAgentsOfSamePopulation", &MedeaHGTSharedData::gActiveHGTBetweenAgentsOfSamePopulation, true);
	gProperties.checkAndGetPropertyValue("gActiveHGTBetweenAgentsOfDifferentPopulations", &MedeaHGTSharedData::gActiveHGTBetweenAgentsOfDifferentPopulations, true);
	gProperties.checkAndGetPropertyValue("gDoHGTByBunch", &MedeaHGTSharedData::gDoHGTByBunch, true);
	gProperties.checkAndGetPropertyValue("gMinProportionOfGenesTransferedByCrossover", &MedeaHGTSharedData::gMinProportionOfGenesTransferedByCrossover, true);
	gProperties.checkAndGetPropertyValue("gMaxProportionOfGenesTransferedByCrossover", &MedeaHGTSharedData::gMaxProportionOfGenesTransferedByCrossover, true);

	// Expe Stuffs
	gProperties.checkAndGetPropertyValue("gNumberOfGenomeExchangesToStayAlive", &MedeaHGTSharedData::gNumberOfGenomeExchangesToStayAlive, true);
	gProperties.checkAndGetPropertyValue("gNumberOfEncounteredAgentsToStayAlive", &MedeaHGTSharedData::gNumberOfEncounteredAgentsToStayAlive, true);

	gProperties.checkAndGetPropertyValue("gSwarmOnlineObsUsed",&MedeaHGTSharedData::gSwarmOnlineObsUsed,true);
	gProperties.checkAndGetPropertyValue("gDynamicSigma",&MedeaHGTSharedData::gDynamicSigma,true);
	gProperties.checkAndGetPropertyValue("gSigmaMin",&MedeaHGTSharedData::gSigmaMin,true);
	gProperties.checkAndGetPropertyValue("gProbAdd",&MedeaHGTSharedData::gProbAdd,true);
	gProperties.checkAndGetPropertyValue("gProbSub",&MedeaHGTSharedData::gProbSub,true);
	gProperties.checkAndGetPropertyValue("gDynaStep",&MedeaHGTSharedData::gDynaStep,true);
	gProperties.checkAndGetPropertyValue("gSigmaRef",&MedeaHGTSharedData::gSigmaRef,true);
	gProperties.checkAndGetPropertyValue("gSigmaMax",&MedeaHGTSharedData::gSigmaMax,true);
	gProperties.checkAndGetPropertyValue("gProbRef",&MedeaHGTSharedData::gProbRef,true);
	gProperties.checkAndGetPropertyValue("gProbMax",&MedeaHGTSharedData::gProbMax,true);
	gProperties.checkAndGetPropertyValue("gEvaluationTime",&MedeaHGTSharedData::gEvaluationTime,true);
	gProperties.checkAndGetPropertyValue("gDriftEvaluationRate",&MedeaHGTSharedData::gDriftEvaluationRate,true);
	gProperties.checkAndGetPropertyValue("gInitLock",&MedeaHGTSharedData::gInitLock,true);
	gProperties.checkAndGetPropertyValue("gDriftLock",&MedeaHGTSharedData::gDriftLock,true);
	gProperties.checkAndGetPropertyValue("gMaxKeyRange",&MedeaHGTSharedData::gMaxKeyRange,true);
	gProperties.checkAndGetPropertyValue("gDeltaKey",&MedeaHGTSharedData::gDeltaKey,true);
	gProperties.checkAndGetPropertyValue("gSynchronization",&MedeaHGTSharedData::gSynchronization,true);

	gProperties.checkAndGetPropertyValue("gExperimentNumber",&MedeaHGTSharedData::gExperimentNumber,true);
	gProperties.checkAndGetPropertyValue("gExperiment1_genStart",&MedeaHGTSharedData::gExperiment1_genStart,true);
	gProperties.checkAndGetPropertyValue("gExperiment2_genStart",&MedeaHGTSharedData::gExperiment2_genStart,true);

	gProperties.checkAndGetPropertyValue("g_xStart_EnergyZone",&MedeaHGTSharedData::g_xStart_EnergyZone,true);
	gProperties.checkAndGetPropertyValue("g_yStart_EnergyZone",&MedeaHGTSharedData::g_yStart_EnergyZone,true);
	gProperties.checkAndGetPropertyValue("g_xEnd_EnergyZone",&MedeaHGTSharedData::g_xEnd_EnergyZone,true);
	gProperties.checkAndGetPropertyValue("g_yEnd_EnergyZone",&MedeaHGTSharedData::g_yEnd_EnergyZone,true);

	gProperties.checkAndGetPropertyValue("gZoneEnergy_maxHarvestValue",&MedeaHGTSharedData::gZoneEnergy_maxHarvestValue,true);
	gProperties.checkAndGetPropertyValue("gZoneEnergy_minHarvestValue",&MedeaHGTSharedData::gZoneEnergy_minHarvestValue,true);
	gProperties.checkAndGetPropertyValue("gZoneEnergy_maxFullCapacity",&MedeaHGTSharedData::gZoneEnergy_maxFullCapacity,true);
	gProperties.checkAndGetPropertyValue("gZoneEnergy_saturateCapacityLevel",&MedeaHGTSharedData::gZoneEnergy_saturateCapacityLevel,true);

	gProperties.checkAndGetPropertyValue("gEnergyMax",&MedeaHGTSharedData::gEnergyMax,true);
	gProperties.checkAndGetPropertyValue("gEnergyInit",&MedeaHGTSharedData::gEnergyInit,true);
	gProperties.checkAndGetPropertyValue("gEnergyRevive",&MedeaHGTSharedData::gEnergyRevive,true);

	gProperties.checkAndGetPropertyValue("gMaxPenalizationRate",&MedeaHGTSharedData::gMaxPenalizationRate,true);
	if ( MedeaHGTSharedData::gMaxPenalizationRate < 0 || MedeaHGTSharedData::gMaxPenalizationRate > 1 )
	{
		std::cerr << "gMaxPenalizationRate should be defined btw O and 1" << std::endl;
		exit(-1);
	}

	gProperties.checkAndGetPropertyValue("gDynamicRespawn",&MedeaHGTSharedData::gDynamicRespawn,true); // forced, in this setup.


	// ====

	if ( !gRadioNetwork)
	{
		std::cout << "Error : gRadioNetwork == false. The swarm online observer need the radio network" << std::endl;
		exit(1);
	}

	if ( !MedeaHGTSharedData::gSwarmOnlineObsUsed)
	{
		std::cout << "Error : gSwarmOnlineObsUsed == false. The swarm online observer need some variables. Define this option to true or use another observer" << std::endl;
		exit(1);
	}

	if ( !gEnergyMode )
	{
		std::cout << "Error : gEnergyMode should be true to use SwarmOnlineObserver" << std::endl;
		exit(1);
	}

	// Populations Counter
	_populationsSize = std::vector<unsigned int>(MedeaHGTSharedData::gMaxNumberOfPopulations, 0);
	_numberOfPopulations = MedeaHGTSharedData::gInitialNumberOfPopulations,

	// * iteration and generation counters
	_lifeIterationCount = -1;
	_generationCount = -1;

	std::cout << std::endl << "#### Experiment no.0 starts now. ####" << std::endl;
}

MedeaHGTWorldObserver::~MedeaHGTWorldObserver()
{
	// nothing to do.
}

void MedeaHGTWorldObserver::reset()
{

	// ...
}

void MedeaHGTWorldObserver::step()
{
	// Update populations
	updatePopulations();

	// ***
	// * update iteration and generation counters + switch btw experimental setups if required
	// ***

	_lifeIterationCount++;

	if( _lifeIterationCount >= MedeaHGTSharedData::gEvaluationTime ) // go to next generation.
	{
		// * monitoring: count number of active agents.

		int activeCount = 0;
		std::vector<unsigned int> activeCountPerPop(_numberOfPopulations, 0);
		for ( int i = 0 ; i != gAgentCounter ; i++ ) {
			MedeaHGTAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaHGTAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
			if(currentAgentWorldModel->getActiveStatus()) {
				++activeCount;
				++activeCountPerPop[currentAgentWorldModel->getPopulationID()];
			}
		}

		if ( !gVerbose ) {
			//std::cout << "[" << activeCount << "]";
			std::cout << "[" << activeCount << ":";
			for(int i = 0; i < _numberOfPopulations; i++) {
				std::cout << activeCountPerPop[i];
				if(i < _numberOfPopulations - 1)
					std::cout << ",";
			}
			std::cout << "]";
		}
		gLogFile << "Info(" << gWorld->getIterations() << ") : active count is " << activeCount << std::endl;


		// * monitor and log orientation and distance to center for all agents

		// build heatmap

		int heatmapSize = 100; // arbitrary, but should be enough to get precise view
		int maxDistance = sqrt ( gAreaWidth*gAreaWidth + gAreaHeight*gAreaHeight ) / 2.0 ; // distance max to center.

		int *distanceHeatmap;
		distanceHeatmap = new int[heatmapSize];
		int *orientationHeatmap;
		orientationHeatmap = new int[heatmapSize];

		for (int i = 0 ; i != heatmapSize ; i++ )
		{
			distanceHeatmap[i] = 0;
			orientationHeatmap[i] = 0;
		}

		double xRef = gAreaWidth / 2.0 ;
		double yRef = gAreaHeight / 2.0 ;

		for ( int i = 0 ; i != gAgentCounter ; i++ )
		{
			MedeaHGTAgentWorldModel *wm = (dynamic_cast<MedeaHGTAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel()));
			if ( wm->getActiveStatus() == true ) // only active agents
			{
				// monitor distance

				double dist = getEuclidianDistance( xRef, yRef, wm->_xReal, wm->_yReal );
				int indexDist = (int)dist * heatmapSize / maxDistance; // normalize within heatmap bounds
				distanceHeatmap[indexDist]++;

				// monitor orientationHeatmap

				double orient = acos ( ( wm->_xReal - xRef ) / (double)dist );
				if ( wm->_yReal - yRef > 0 ) // [trick] why ">0" ?  : it should be <0, but as the 2D-display norm for the coordinate system origin is upper-left (and not bottom-left), the sign is inversed.
				{
					orient = -orient;
				}

				int indexOrient = ( orient + M_PI ) * heatmapSize / (2.0 * M_PI);
				orientationHeatmap[heatmapSize-1-((indexOrient+((heatmapSize*3)/4))%heatmapSize)]++; // index is such that list ordering is as follow: [South-West-North-East-South]

				//std::cout << "\n agent[" << wm->_xReal << "," << wm->_yReal << "](" << dist << "," << orient << ") -- " << wm->_xReal << ";" << xRef << ";" << ( ( wm->_xReal - xRef ) / (double)dist ) << ";" << acos ( ( wm->_xReal - xRef ) / (double)dist ); //debug
			}
		}
		//std::cout << "\n"; //debug


		// update log file

		std::string str_agentDistancesToRef ="";
		std::string str_agentOrientationsToRef = "";

		for (int i = 0 ; i != heatmapSize ; i++ )
		{
			str_agentDistancesToRef += convertToString(distanceHeatmap[i]);
			str_agentDistancesToRef += ",";
			str_agentOrientationsToRef += convertToString(orientationHeatmap[i]);
			str_agentOrientationsToRef += ",";
		}

		//gLogFile
		//std::cout << std::endl << std::endl;//debug
		//gLogFile << "Info(" << gWorld->getIterations() << ") : monitor distance to ref - " << (_generationCount+1) << "," << gAgentCounter << "," << str_agentDistancesToRef << std::endl;
		//gLogFile << "Info(" << gWorld->getIterations() << ") : monitor orientation to ref - " << (_generationCount+1) << "," << gAgentCounter << "," << str_agentOrientationsToRef << std::endl;

		for ( int i = 0 ; i != heatmapSize ; i++ )
		{
			gLogFile << "monitorDistance: " << gAgentCounter << "," << (int)sqrt(gMaxRadioDistanceToSquare) << "," << (_generationCount+1) << "," << i << "," << distanceHeatmap[i] << std::endl;
			gLogFile << "monitorOrientation: " << gAgentCounter << "," << (int)sqrt(gMaxRadioDistanceToSquare) << "," << (_generationCount+1) << "," << i << "," << orientationHeatmap[i] << std::endl;
		}
		//gLogFile << "Info(" << gWorld->getIterations() << ") : monitor distance to ref - " << (_generationCount+1) << "," << gAgentCounter << "," << str_agentDistancesToRef << std::endl;
		//gLogFile << "Info(" << gWorld->getIterations() << ") : monitor orientation to ref - " << (_generationCount+1) << "," << gAgentCounter << "," << str_agentOrientationsToRef << std::endl;

		delete [] distanceHeatmap;
		delete [] orientationHeatmap;

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

	// prepape and take screenshot of ultimate iteration

	if ( gWorld->getIterations() == gMaxIt-2 )
	{
		gDisplayMode = 0;
		gDisplaySensors = true; // prepape for next it.
	}
	else
	{
		if ( gWorld->getIterations() == gMaxIt-1 )
			saveScreenshot("lastIteration");
	}

}


/*
 * Update populations
 */
void MedeaHGTWorldObserver::updatePopulations() {

	// Initialize population, if required
	if(_populationsSize[0] == 0)
		initPopulations();

	// See if the number of population must be increased
	if(		_generationCount != 0 &&
			MedeaHGTSharedData::gAutoIncreaseNumberOfPopulation &&
			_generationCount % MedeaHGTSharedData::gAutoIncreaseNumberOfPopulationPeriod == 0 &&
			_numberOfPopulations < MedeaHGTSharedData::gMaxNumberOfPopulations &&
			_numberOfPopulations < gAgentCounter) {
		// Randomly select a population and fork it
		for(int tries = 0; tries < 42; tries++) {
			int const popIDToFork = rand() % _numberOfPopulations;
			if(_populationsSize[popIDToFork] > 1) {
				++_numberOfPopulations;
				int const newPopID = _numberOfPopulations - 1;
				bool isGood = false;
				do {
					_populationsSize[popIDToFork] = 0;
					_populationsSize[newPopID] = 0;

					for ( int i = 0 ; i != gAgentCounter ; i++ ) {
						MedeaHGTAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaHGTAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
						if(currentAgentWorldModel->getPopulationID() == popIDToFork || currentAgentWorldModel->getPopulationID() == newPopID) {
							unsigned int const coin = rand() % 2;
							if(coin) {
								currentAgentWorldModel->setPopulationID(popIDToFork);
								++_populationsSize[popIDToFork];
							} else {
								currentAgentWorldModel->setPopulationID(newPopID);
								++_populationsSize[newPopID];
							}
						}
					}

					isGood = true;
					for(int i = 0; i < _numberOfPopulations; i++) {
						isGood &= (_populationsSize[i] != 0);
					}
				} while(!isGood);
				break;
			}
		}

		std::cout << std::endl << "# Increased Number of populations: ";
		for(int i = 0; i < _numberOfPopulations; i++) {
			std::cout << "pop" << i << "size=" << _populationsSize[i] << " ";
		}
		std::cout << std::endl;

	}
}


// ***
// * Check and update (ONLY IF REQUIRED) experimental setup.
// ***
void MedeaHGTWorldObserver::updateExperimentalSettings()
{
	// ...
}

// ***
// * Update environment status wrt. nature and availability of energy resources (update at each iteration)
// ***
void MedeaHGTWorldObserver::updateEnvironmentResources()
{
	// ...
}


// *
// * update energy level for each agents (ONLY active agents) (only in experimental setups featuring energy items)
// *
void MedeaHGTWorldObserver::updateAllAgentsEnergyLevel()
{
	// ...
}

void MedeaHGTWorldObserver::initPopulations() {
	bool isGood = false;
	do {
		_populationsSize = std::vector<unsigned int>(MedeaHGTSharedData::gMaxNumberOfPopulations, 0);

		for ( int i = 0 ; i != gAgentCounter ; i++ ) {
			MedeaHGTAgentWorldModel *currentAgentWorldModel = dynamic_cast<MedeaHGTAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
			unsigned int const populationID = rand() % _numberOfPopulations;
			currentAgentWorldModel->setPopulationID(populationID);
			++_populationsSize[populationID];
		}

		isGood = true;
		for(int i = 0; i < _numberOfPopulations; i++) {
			isGood &= (_populationsSize[i] != 0);
		}
	} while(!isGood);
}


int MedeaHGTWorldObserver::getLifeIterationCount()
{
	return _lifeIterationCount;
}

std::vector<unsigned int> MedeaHGTWorldObserver::getPopulationsSize() {
	return _populationsSize;
}

int MedeaHGTWorldObserver::getNumberOfPopulations() {
	return _numberOfPopulations;
}

