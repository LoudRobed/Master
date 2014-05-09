/*
 *  SpikeAntsControlArchitecture.h
 *  roborobo-online
 *
 *  Created by Nicolas on 27/05/10.
 *
 */


#ifndef SPIKEANTSCONTROLARCHITECTURE_H
#define SPIKEANTSCONTROLARCHITECTURE_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "BehaviorControlArchitectures/BehaviorControlArchitecture.h"

// #include "WorldModels/RobotAgentWorldModel.h"

#include "SpikeAnts/include/SpikeAntsAgentWorldModel.h"

class SpikeAntsControlArchitecture : public BehaviorControlArchitecture
{
private:
  SpikeAntsAgentWorldModel *_wm;

public:
  //Initializes the variables
  SpikeAntsControlArchitecture( RobotAgentWorldModel *__wm );
  ~SpikeAntsControlArchitecture();
  
  void reset();
  void step();
};


#endif

