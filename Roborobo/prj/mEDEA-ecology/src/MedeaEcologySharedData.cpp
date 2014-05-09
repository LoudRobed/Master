/**
 * @file
 * @author Nicolas Bredeche <nicolas.bredeche@gmail.com>
 * 
 * History :
 *  - imported from medea-basic project on 16/6/2012
 *
 */



#include "mEDEA-ecology/include/MedeaEcologySharedData.h"



// ----- ----- ----- ----- -----



bool MedeaEcologySharedData::gSwarmOnlineObsUsed = false; // define if the SwarmOnlineObserver is used. If it's the case, the following parameter have to be defined and gEnergyMode should be true
bool MedeaEcologySharedData::gDynamicSigma = false;
double MedeaEcologySharedData::gSigmaMin = 0.0;
double MedeaEcologySharedData::gProbSub = 0.0;
double MedeaEcologySharedData::gProbAdd = 0.0;
double MedeaEcologySharedData::gDynaStep = 0.0;
double MedeaEcologySharedData::gSigmaRef = 0.0; // reference value of sigma
double MedeaEcologySharedData::gSigmaMax = 0.0; // maximal value of sigma
double MedeaEcologySharedData::gProbRef = 0.0; // probability of transmitting the current genome mutated with sigma ref
double MedeaEcologySharedData::gProbMax = 0.0; // probability of transmitting the current genome mutatued withe sigma ref
int MedeaEcologySharedData::gEvaluationTime = 0; // how long a controller will be evaluated on a robot

//int MedeaEcologySharedData::gMaxEvaluation = 0; // Roughly how many controllers will be evaluated on a robot. Since there is some restart procedure because of the energy, it might happen that more evaluation take place.

double MedeaEcologySharedData::gDriftEvaluationRate = 0.0;
double MedeaEcologySharedData::gInitLock = 0.0;
double MedeaEcologySharedData::gDriftLock = 0.0;
double MedeaEcologySharedData::gMaxKeyRange = 0.0;
double MedeaEcologySharedData::gDeltaKey = 0.0;
bool MedeaEcologySharedData::gSynchronization = true;
// VALUE DEFINED IN CONSTRUCTOR (below)

int MedeaEcologySharedData::gExperimentNumber = 0;
int MedeaEcologySharedData::gExperiment1_genStart = 10;
int MedeaEcologySharedData::gExperiment2_genStart = 20;

int MedeaEcologySharedData::g_xStart_EnergyZone = 0;
int MedeaEcologySharedData::g_xEnd_EnergyZone = 0;
int MedeaEcologySharedData::g_yStart_EnergyZone = 0;
int MedeaEcologySharedData::g_yEnd_EnergyZone = 0;

double MedeaEcologySharedData::gZoneEnergy_harvestValue = 0; // set in the code, depends on the following params
double MedeaEcologySharedData::gZoneEnergy_maxHarvestValue;
double MedeaEcologySharedData::gZoneEnergy_minHarvestValue;
int MedeaEcologySharedData::gZoneEnergy_maxFullCapacity;
int MedeaEcologySharedData::gZoneEnergy_saturateCapacityLevel;

double MedeaEcologySharedData::gEnergyMax;
double MedeaEcologySharedData::gEnergyRevive;
double MedeaEcologySharedData::gEnergyInit;

bool MedeaEcologySharedData::gDynamicRespawn;


double MedeaEcologySharedData::gMaxPenalizationRate;

// ----- ----- ----- ----- ----- 

bool MedeaEcologySharedData::gPropertiesLoaded = false; // global variable local to file -- TODO: move specific properties loader in dedicated WorldObserver

// ----- ----- ----- ----- ----- 
