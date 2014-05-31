/*
 *  AggregationBasicControlArchitecture.h
 *  roborobo-online
 *
 *  Created by Jean-Marc on 07/04/13
 *
 */


#ifndef AGGREGATIONBASICCONTROLARCHITECTURE_H
#define AGGREGATIONBASICCONTROLARCHITECTURE_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "BehaviorControlArchitectures/BehaviorControlArchitecture.h"

#include "WorldModels/RobotAgentWorldModel.h"

#include "connectionMechanism/GripperConnectionMechanism.h"

class AggregationBasicControlArchitecture : public BehaviorControlArchitecture
{
	public:
		//Initializes the variables
		AggregationBasicControlArchitecture( RobotAgentWorldModel *__wm );
		~AggregationBasicControlArchitecture();
		
		void reset();
		void step();
	
	protected:
		bool _firstStep;
		GripperConnectionMechanism* connection;

};


#endif

