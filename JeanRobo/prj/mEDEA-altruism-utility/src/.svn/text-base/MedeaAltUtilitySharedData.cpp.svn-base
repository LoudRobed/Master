/*
 *  MedeaAltUtilitySharedData.cpp
 *  Roborobo
 *
 *  Created by Nicolas on 3/6/2010.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */


#include "mEDEA-altruism-utility/include/MedeaAltUtilitySharedData.h"



// ----- ----- ----- ----- -----



bool MedeaAltUtilitySharedData::gSwarmOnlineObsUsed = false; // define if the SwarmOnlineObserver is used. If it's the case, the following parameter have to be defined and gEnergyMode should be true
bool MedeaAltUtilitySharedData::gDynamicSigma = false;
double MedeaAltUtilitySharedData::gSigmaMin = 0.0;
double MedeaAltUtilitySharedData::gProbSub = 0.0;
double MedeaAltUtilitySharedData::gProbAdd = 0.0;
double MedeaAltUtilitySharedData::gDynaStep = 0.0;
double MedeaAltUtilitySharedData::gSigmaRef = 0.0; // reference value of sigma
double MedeaAltUtilitySharedData::gSigmaMax = 0.0; // maximal value of sigma
double MedeaAltUtilitySharedData::gProbRef = 0.0; // probability of transmitting the current genome mutated with sigma ref
double MedeaAltUtilitySharedData::gProbMax = 0.0; // probability of transmitting the current genome mutatued withe sigma ref
int MedeaAltUtilitySharedData::gEvaluationTime = 0; // how long a controller will be evaluated on a robot

//int MedeaAltUtilitySharedData::gMaxEvaluation = 0; // Roughly how many controllers will be evaluated on a robot. Since there is some restart procedure because of the energy, it might happen that more evaluation take place.

double MedeaAltUtilitySharedData::gDriftEvaluationRate = 0.0;
double MedeaAltUtilitySharedData::gInitLock = 0.0;
double MedeaAltUtilitySharedData::gDriftLock = 0.0;
double MedeaAltUtilitySharedData::gMaxKeyRange = 0.0;
double MedeaAltUtilitySharedData::gDeltaKey = 0.0;
bool MedeaAltUtilitySharedData::gSynchronization = true;
// VALUE DEFINED IN CONSTRUCTOR (below)

int MedeaAltUtilitySharedData::gExperimentNumber = 0;
int MedeaAltUtilitySharedData::gExperiment1_genStart = 10;
int MedeaAltUtilitySharedData::gExperiment2_genStart = 20;

int MedeaAltUtilitySharedData::g_xStart_EnergyZone = 0;
int MedeaAltUtilitySharedData::g_xEnd_EnergyZone = 0;
int MedeaAltUtilitySharedData::g_yStart_EnergyZone = 0;
int MedeaAltUtilitySharedData::g_yEnd_EnergyZone = 0;

double MedeaAltUtilitySharedData::gZoneEnergy_harvestValue = 0; // set in the code, depends on the following params
double MedeaAltUtilitySharedData::gZoneEnergy_maxHarvestValue;
double MedeaAltUtilitySharedData::gZoneEnergy_minHarvestValue;
int MedeaAltUtilitySharedData::gZoneEnergy_maxFullCapacity;
int MedeaAltUtilitySharedData::gZoneEnergy_saturateCapacityLevel;

double MedeaAltUtilitySharedData::gEnergyMax;
double MedeaAltUtilitySharedData::gEnergyRevive;
double MedeaAltUtilitySharedData::gEnergyInit;

bool MedeaAltUtilitySharedData::gDynamicRespawn;
int MedeaAltUtilitySharedData::gThresholdIncreaseRespawn;
int MedeaAltUtilitySharedData::gLowestBoundRespawn;
int MedeaAltUtilitySharedData::gHighestBoundRespawn;


double MedeaAltUtilitySharedData::gMaxPenalizationRate;

// ----- ----- ----- ----- ----- 

bool MedeaAltUtilitySharedData::gPropertiesLoaded = false; // global variable local to file -- TODO: move specific properties loader in dedicated WorldObserver

// ----- ----- ----- ----- ----- 
