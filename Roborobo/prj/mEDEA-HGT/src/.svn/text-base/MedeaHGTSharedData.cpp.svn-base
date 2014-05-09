/**
 * @file
 * @author Leo Cazenille <leo.cazenille@gmail.com>
 * TODO : Add formal description
 * History :
 *
 *
 */


#include "mEDEA-HGT/include/MedeaHGTSharedData.h"



// ----- ----- ----- ----- -----

// Populations Stuffs
int MedeaHGTSharedData::gInitialNumberOfPopulations = 1;
int MedeaHGTSharedData::gMaxNumberOfPopulations = 1;
bool MedeaHGTSharedData::gAutoIncreaseNumberOfPopulation = false;
int MedeaHGTSharedData::gAutoIncreaseNumberOfPopulationPeriod = 30;

// HGT Stuffs
bool MedeaHGTSharedData::gActiveHGTBetweenAgentsOfSamePopulation = false;
bool MedeaHGTSharedData::gActiveHGTBetweenAgentsOfDifferentPopulations = true;
bool MedeaHGTSharedData::gDoHGTByBunch = true;
double MedeaHGTSharedData::gMinProportionOfGenesTransferedByCrossover = 0.1;
double MedeaHGTSharedData::gMaxProportionOfGenesTransferedByCrossover = 0.4;

// Expe
int MedeaHGTSharedData::gNumberOfGenomeExchangesToStayAlive = 2;
int MedeaHGTSharedData::gNumberOfEncounteredAgentsToStayAlive = 2;



bool MedeaHGTSharedData::gSwarmOnlineObsUsed = false; // define if the SwarmOnlineObserver is used. If it's the case, the following parameter have to be defined and gEnergyMode should be true
bool MedeaHGTSharedData::gDynamicSigma = false;
double MedeaHGTSharedData::gSigmaMin = 0.0;
double MedeaHGTSharedData::gProbSub = 0.0;
double MedeaHGTSharedData::gProbAdd = 0.0;
double MedeaHGTSharedData::gDynaStep = 0.0;
double MedeaHGTSharedData::gSigmaRef = 0.0; // reference value of sigma
double MedeaHGTSharedData::gSigmaMax = 0.0; // maximal value of sigma
double MedeaHGTSharedData::gProbRef = 0.0; // probability of transmitting the current genome mutated with sigma ref
double MedeaHGTSharedData::gProbMax = 0.0; // probability of transmitting the current genome mutatued withe sigma ref
int MedeaHGTSharedData::gEvaluationTime = 0; // how long a controller will be evaluated on a robot

//int MedeaHGTSharedData::gMaxEvaluation = 0; // Roughly how many controllers will be evaluated on a robot. Since there is some restart procedure because of the energy, it might happen that more evaluation take place.

double MedeaHGTSharedData::gDriftEvaluationRate = 0.0;
double MedeaHGTSharedData::gInitLock = 0.0;
double MedeaHGTSharedData::gDriftLock = 0.0;
double MedeaHGTSharedData::gMaxKeyRange = 0.0;
double MedeaHGTSharedData::gDeltaKey = 0.0;
bool MedeaHGTSharedData::gSynchronization = true;
// VALUE DEFINED IN CONSTRUCTOR (below)

int MedeaHGTSharedData::gExperimentNumber = 0;
int MedeaHGTSharedData::gExperiment1_genStart = 10;
int MedeaHGTSharedData::gExperiment2_genStart = 20;

int MedeaHGTSharedData::g_xStart_EnergyZone = 0;
int MedeaHGTSharedData::g_xEnd_EnergyZone = 0;
int MedeaHGTSharedData::g_yStart_EnergyZone = 0;
int MedeaHGTSharedData::g_yEnd_EnergyZone = 0;

double MedeaHGTSharedData::gZoneEnergy_harvestValue = 0; // set in the code, depends on the following params
double MedeaHGTSharedData::gZoneEnergy_maxHarvestValue;
double MedeaHGTSharedData::gZoneEnergy_minHarvestValue;
int MedeaHGTSharedData::gZoneEnergy_maxFullCapacity;
int MedeaHGTSharedData::gZoneEnergy_saturateCapacityLevel;

double MedeaHGTSharedData::gEnergyMax;
double MedeaHGTSharedData::gEnergyRevive;
double MedeaHGTSharedData::gEnergyInit;

bool MedeaHGTSharedData::gDynamicRespawn;


double MedeaHGTSharedData::gMaxPenalizationRate;

// ----- ----- ----- ----- -----

bool MedeaHGTSharedData::gPropertiesLoaded = false; // global variable local to file -- TODO: move specific properties loader in dedicated WorldObserver

// ----- ----- ----- ----- -----
