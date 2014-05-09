/*
 *  SpikeAntsAgentObserver.h
 *  roborobo-online
 *
 *  Created by Nicolas on 27/05/10.
 *
 */

 
#ifndef SPIKEANTSAGENTOBSERVER_H
#define SPIKEANTSAGENTOBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "SpikeAnts/include/SpikeAntsAgentWorldModel.h"

#include "Observers/AgentObserver.h"

class SpikeAntsAgentObserver : public AgentObserver
{
protected:
  SpikeAntsAgentWorldModel	*_wm;

public:
  //Initializes the variables
  SpikeAntsAgentObserver( );
  SpikeAntsAgentObserver( RobotAgentWorldModel *__wm );
  ~SpikeAntsAgentObserver();
				
  void reset();
  void step();
		
};


#endif

