/*
 *  MedeaAggregationSharedData.cpp
 *  Roborobo
 *
 *  Created by Nicolas on 3/6/2010.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */


#include "mEDEA-aggregation/include/MedeaAggregationSharedData.h"



// ----- ----- ----- ----- -----



bool MedeaAggregationSharedData::gSwarmOnlineObsUsed = false; // define if the SwarmOnlineObserver is used. If it's the case, the following parameter have to be defined and gEnergyMode should be true
bool MedeaAggregationSharedData::gDynamicSigma = false;
double MedeaAggregationSharedData::gSigmaMin = 0.0;
double MedeaAggregationSharedData::gProbSub = 0.0;
double MedeaAggregationSharedData::gProbAdd = 0.0;
double MedeaAggregationSharedData::gDynaStep = 0.0;
double MedeaAggregationSharedData::gSigmaRef = 0.0; // reference value of sigma
double MedeaAggregationSharedData::gSigmaMax = 0.0; // maximal value of sigma
double MedeaAggregationSharedData::gProbRef = 0.0; // probability of transmitting the current genome mutated with sigma ref
double MedeaAggregationSharedData::gProbMax = 0.0; // probability of transmitting the current genome mutatued withe sigma ref
int MedeaAggregationSharedData::gEvaluationTime = 0; // how long a controller will be evaluated on a robot

double MedeaAggregationSharedData::energyPointValueMax = 0.0;

//int MedeaAggregationSharedData::gMaxEvaluation = 0; // Roughly how many controllers will be evaluated on a robot. Since there is some restart procedure because of the energy, it might happen that more evaluation take place.

double MedeaAggregationSharedData::gDriftEvaluationRate = 0.0;
double MedeaAggregationSharedData::gInitLock = 0.0;
double MedeaAggregationSharedData::gDriftLock = 0.0;
double MedeaAggregationSharedData::gMaxKeyRange = 0.0;
double MedeaAggregationSharedData::gDeltaKey = 0.0;
bool MedeaAggregationSharedData::gSynchronization = true;
// VALUE DEFINED IN CONSTRUCTOR (below)

int MedeaAggregationSharedData::g_xStart_EnergyZone = 0;
int MedeaAggregationSharedData::g_xEnd_EnergyZone = 0;
int MedeaAggregationSharedData::g_yStart_EnergyZone = 0;
int MedeaAggregationSharedData::g_yEnd_EnergyZone = 0;

double MedeaAggregationSharedData::gZoneEnergy_harvestValue = 0; // set in the code, depends on the following params
double MedeaAggregationSharedData::gZoneEnergy_maxHarvestValue;
double MedeaAggregationSharedData::gZoneEnergy_minHarvestValue;
int MedeaAggregationSharedData::gZoneEnergy_maxFullCapacity;
int MedeaAggregationSharedData::gZoneEnergy_saturateCapacityLevel;

double MedeaAggregationSharedData::gDeadTime;
double MedeaAggregationSharedData::gEnergyMax;
double MedeaAggregationSharedData::gEnergyRevive;
double MedeaAggregationSharedData::gEnergyInit;

bool MedeaAggregationSharedData::gDynamicRespawn;
int MedeaAggregationSharedData::gThresholdIncreaseRespawn;
int MedeaAggregationSharedData::gLowestBoundRespawn;
int MedeaAggregationSharedData::gHighestBoundRespawn;
int MedeaAggregationSharedData::energyPointRespawnLagMaxValue;


double MedeaAggregationSharedData::gMaxPenalizationRate;

std::string MedeaAggregationSharedData::selectionScheme;
std::string MedeaAggregationSharedData::harvestingScheme;

// ----- ----- ----- ----- ----- 

bool MedeaAggregationSharedData::gPropertiesLoaded = false; // global variable local to file -- TODO: move specific properties loader in dedicated WorldObserver

// ----- ----- ----- ----- ----- 
