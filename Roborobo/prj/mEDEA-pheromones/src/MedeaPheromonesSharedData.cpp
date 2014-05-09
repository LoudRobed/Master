/**
 * @file
 * @author Nicolas Bredeche <nicolas.bredeche@gmail.com>
 * 
 * History :
 *  - imported from medea-basic project on 16/6/2012
 *
 */


#include "mEDEA-pheromones/include/MedeaPheromonesSharedData.h"



// ----- ----- ----- ----- -----



bool MedeaPheromonesSharedData::gSwarmOnlineObsUsed = false; // define if the SwarmOnlineObserver is used. If it's the case, the following parameter have to be defined and gEnergyMode should be true
bool MedeaPheromonesSharedData::gDynamicSigma = false;
double MedeaPheromonesSharedData::gSigmaMin = 0.0;
double MedeaPheromonesSharedData::gProbSub = 0.0;
double MedeaPheromonesSharedData::gProbAdd = 0.0;
double MedeaPheromonesSharedData::gDynaStep = 0.0;
double MedeaPheromonesSharedData::gSigmaRef = 0.0; // reference value of sigma
double MedeaPheromonesSharedData::gSigmaMax = 0.0; // maximal value of sigma
double MedeaPheromonesSharedData::gProbRef = 0.0; // probability of transmitting the current genome mutated with sigma ref
double MedeaPheromonesSharedData::gProbMax = 0.0; // probability of transmitting the current genome mutatued withe sigma ref
int MedeaPheromonesSharedData::gEvaluationTime = 0; // how long a controller will be evaluated on a robot

//int MedeaPheromonesSharedData::gMaxEvaluation = 0; // Roughly how many controllers will be evaluated on a robot. Since there is some restart procedure because of the energy, it might happen that more evaluation take place.

double MedeaPheromonesSharedData::gDriftEvaluationRate = 0.0;
double MedeaPheromonesSharedData::gInitLock = 0.0;
double MedeaPheromonesSharedData::gDriftLock = 0.0;
double MedeaPheromonesSharedData::gMaxKeyRange = 0.0;
double MedeaPheromonesSharedData::gDeltaKey = 0.0;
bool MedeaPheromonesSharedData::gSynchronization = true;
// VALUE DEFINED IN CONSTRUCTOR (below)

int MedeaPheromonesSharedData::gExperimentNumber = 0;
int MedeaPheromonesSharedData::gExperiment1_genStart = 10;
int MedeaPheromonesSharedData::gExperiment2_genStart = 20;

int MedeaPheromonesSharedData::g_xStart_EnergyZone = 0;
int MedeaPheromonesSharedData::g_xEnd_EnergyZone = 0;
int MedeaPheromonesSharedData::g_yStart_EnergyZone = 0;
int MedeaPheromonesSharedData::g_yEnd_EnergyZone = 0;

double MedeaPheromonesSharedData::gZoneEnergy_harvestValue = 0; // set in the code, depends on the following params
double MedeaPheromonesSharedData::gZoneEnergy_maxHarvestValue;
double MedeaPheromonesSharedData::gZoneEnergy_minHarvestValue;
int MedeaPheromonesSharedData::gZoneEnergy_maxFullCapacity;
int MedeaPheromonesSharedData::gZoneEnergy_saturateCapacityLevel;

double MedeaPheromonesSharedData::gEnergyMax;
double MedeaPheromonesSharedData::gEnergyRevive;
double MedeaPheromonesSharedData::gEnergyInit;

bool MedeaPheromonesSharedData::gDynamicRespawn;


double MedeaPheromonesSharedData::gMaxPenalizationRate;

// ----- ----- ----- ----- ----- 

bool MedeaPheromonesSharedData::gPropertiesLoaded = false; // global variable local to file -- TODO: move specific properties loader in dedicated WorldObserver

// ----- ----- ----- ----- ----- 
