/*
 *  AggregationBasicAgentWorldModel.h
 *  roborobo-online
 *
 *  Created by Jean-Marc on 07/04/13
 *
 */


#ifndef AGGREGATIONBASICAGENTWORLDMODEL_H
#define AGGREGATIONBASICAGENTWORLDMODEL_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "WorldModels/RobotAgentConnectableWorldModel.h"

class World;

class AggregationBasicAgentWorldModel : public RobotAgentConnectableWorldModel
{	
	private: 
		int _robotNeighborhoodCounter; // count the number of other robots within a given radius.
	
	public:

		// refer to super class to check what data / methods are available.		
		
		AggregationBasicAgentWorldModel();
		virtual ~AggregationBasicAgentWorldModel();
};


#endif


