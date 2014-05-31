/*
 *  MedeaAltruismSharedData.cpp
 *  Roborobo
 *
 *  Created by Nicolas on 3/6/2010.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */


#include "mEDEA-altruism/include/MedeaAltruismSharedData.h"



// ----- ----- ----- ----- -----



bool MedeaAltruismSharedData::gSwarmOnlineObsUsed = false; // define if the SwarmOnlineObserver is used. If it's the case, the following parameter have to be defined and gEnergyMode should be true
bool MedeaAltruismSharedData::gDynamicSigma = false;
double MedeaAltruismSharedData::gSigmaMin = 0.0;
double MedeaAltruismSharedData::gProbSub = 0.0;
double MedeaAltruismSharedData::gProbAdd = 0.0;
double MedeaAltruismSharedData::gDynaStep = 0.0;
double MedeaAltruismSharedData::gSigmaRef = 0.0; // reference value of sigma
double MedeaAltruismSharedData::gSigmaMax = 0.0; // maximal value of sigma
double MedeaAltruismSharedData::gProbRef = 0.0; // probability of transmitting the current genome mutated with sigma ref
double MedeaAltruismSharedData::gProbMax = 0.0; // probability of transmitting the current genome mutatued withe sigma ref
int MedeaAltruismSharedData::gEvaluationTime = 0; // how long a controller will be evaluated on a robot

//int MedeaAltruismSharedData::gMaxEvaluation = 0; // Roughly how many controllers will be evaluated on a robot. Since there is some restart procedure because of the energy, it might happen that more evaluation take place.

double MedeaAltruismSharedData::gDriftEvaluationRate = 0.0;
double MedeaAltruismSharedData::gInitLock = 0.0;
double MedeaAltruismSharedData::gDriftLock = 0.0;
double MedeaAltruismSharedData::gMaxKeyRange = 0.0;
double MedeaAltruismSharedData::gDeltaKey = 0.0;
bool MedeaAltruismSharedData::gSynchronization = true;
// VALUE DEFINED IN CONSTRUCTOR (below)

int MedeaAltruismSharedData::g_xStart_EnergyZone = 0;
int MedeaAltruismSharedData::g_xEnd_EnergyZone = 0;
int MedeaAltruismSharedData::g_yStart_EnergyZone = 0;
int MedeaAltruismSharedData::g_yEnd_EnergyZone = 0;

double MedeaAltruismSharedData::gZoneEnergy_harvestValue = 0; // set in the code, depends on the following params
double MedeaAltruismSharedData::gZoneEnergy_maxHarvestValue;
double MedeaAltruismSharedData::gZoneEnergy_minHarvestValue;
int MedeaAltruismSharedData::gZoneEnergy_maxFullCapacity;
int MedeaAltruismSharedData::gZoneEnergy_saturateCapacityLevel;

double MedeaAltruismSharedData::gDeadTime;
double MedeaAltruismSharedData::gEnergyMax;
double MedeaAltruismSharedData::gEnergyRevive;
double MedeaAltruismSharedData::gEnergyInit;

bool MedeaAltruismSharedData::gDynamicRespawn;
int MedeaAltruismSharedData::gThresholdIncreaseRespawn;
int MedeaAltruismSharedData::gLowestBoundRespawn;
int MedeaAltruismSharedData::gHighestBoundRespawn;


double MedeaAltruismSharedData::gMaxPenalizationRate;

std::string MedeaAltruismSharedData::selectionScheme;
std::string MedeaAltruismSharedData::harvestingScheme;

// ----- ----- ----- ----- ----- 

bool MedeaAltruismSharedData::gPropertiesLoaded = false; // global variable local to file -- TODO: move specific properties loader in dedicated WorldObserver

// ----- ----- ----- ----- ----- 
