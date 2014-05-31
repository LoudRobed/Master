/*
 *  MedeaOptimSharedData.cpp
 *  Roborobo
 *
 *  Created by Nicolas on 19/1/2011
 *
 */


#include "mEDEA-optim/include/MedeaOptimSharedData.h"



// ----- ----- ----- ----- -----



bool MedeaOptimSharedData::gSwarmOnlineObsUsed = false; // define if the SwarmOnlineObserver is used. If it's the case, the following parameter have to be defined and gEnergyMode should be true
bool MedeaOptimSharedData::gDynamicSigma = false;
double MedeaOptimSharedData::gSigmaMin = 0.0;
double MedeaOptimSharedData::gProbSub = 0.0;
double MedeaOptimSharedData::gProbAdd = 0.0;
double MedeaOptimSharedData::gDynaStep = 0.0;
double MedeaOptimSharedData::gSigmaRef = 0.0; // reference value of sigma
double MedeaOptimSharedData::gSigmaMax = 0.0; // maximal value of sigma
double MedeaOptimSharedData::gProbRef = 0.0; // probability of transmitting the current genome mutated with sigma ref
double MedeaOptimSharedData::gProbMax = 0.0; // probability of transmitting the current genome mutatued withe sigma ref
int MedeaOptimSharedData::gEvaluationTime = 0; // how long a controller will be evaluated on a robot

//int MedeaOptimSharedData::gMaxEvaluation = 0; // Roughly how many controllers will be evaluated on a robot. Since there is some restart procedure because of the energy, it might happen that more evaluation take place.

double MedeaOptimSharedData::gDriftEvaluationRate = 0.0;
double MedeaOptimSharedData::gInitLock = 0.0;
double MedeaOptimSharedData::gDriftLock = 0.0;
double MedeaOptimSharedData::gMaxKeyRange = 0.0;
double MedeaOptimSharedData::gDeltaKey = 0.0;
bool MedeaOptimSharedData::gSynchronization = true;
// VALUE DEFINED IN CONSTRUCTOR (below)

int MedeaOptimSharedData::g_xStart_EnergyZone = 0;
int MedeaOptimSharedData::g_xEnd_EnergyZone = 0;
int MedeaOptimSharedData::g_yStart_EnergyZone = 0;
int MedeaOptimSharedData::g_yEnd_EnergyZone = 0;

double MedeaOptimSharedData::gZoneEnergy_harvestValue = 0; // set in the code, depends on the following params
double MedeaOptimSharedData::gZoneEnergy_maxHarvestValue;
double MedeaOptimSharedData::gZoneEnergy_minHarvestValue;
int MedeaOptimSharedData::gZoneEnergy_maxFullCapacity;
int MedeaOptimSharedData::gZoneEnergy_saturateCapacityLevel;

double MedeaOptimSharedData::gEnergyMax;
double MedeaOptimSharedData::gEnergyRevive;
double MedeaOptimSharedData::gEnergyInit;

bool MedeaOptimSharedData::gDynamicRespawn;

double MedeaOptimSharedData::gAlphaCorrelationValue;

double MedeaOptimSharedData::gMaxPenalizationRate;

// ----- ----- ----- ----- ----- 

bool MedeaOptimSharedData::gPropertiesLoaded = false; // global variable local to file -- TODO: move specific properties loader in dedicated WorldObserver

// ----- ----- ----- ----- ----- 
