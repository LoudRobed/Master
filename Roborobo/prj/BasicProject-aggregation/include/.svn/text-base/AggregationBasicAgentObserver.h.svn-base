/*
 *  AggregationBasicAgentObserver.h
 *  roborobo-online
 *
 *  Created by Jean-Marc on 07/04/13
 *
 */

 
#ifndef AGGREGATIONBASICAGENTOBSERVER_H
#define AGGREGATIONBASICAGENTOBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "BasicProject-aggregation/include/AggregationBasicAgentWorldModel.h"

#include "Observers/AgentObserver.h"

class AggregationBasicAgentObserver : public AgentObserver
{
	protected:
		AggregationBasicAgentWorldModel	*_wm;

	public:
		//Initializes the variables
		AggregationBasicAgentObserver( );
		AggregationBasicAgentObserver( RobotAgentWorldModel *__wm );
		~AggregationBasicAgentObserver();
				
		void reset();
		void step();
		
};


#endif

