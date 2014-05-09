/*
 *  MedeaAggregationControlArchitecture.h
 *  roborobo-online
 *
 *  Created by Nicolas on 20/03/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *  modification by Jean-Marc on 24/22/2013 : 
 *    - add the possibity to use also CTRNN from neuralnetworks contrib
 *
 */


#ifndef MEDEAAGGREGATIONCONTROLARCHITECTURE_H
#define MEDEAAGGREGATIONCONTROLARCHITECTURE_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Utilities/SDL_gfxRoborobo.h"

#include "BehaviorControlArchitectures/BehaviorControlArchitecture.h"
#include "mEDEA-aggregation/include/MedeaAggregationAgentWorldModel.h"
#include "mEDEA-aggregation/include/MedeaAggregationAgentObserver.h"
#include "mEDEA-aggregation/include/MedeaAggregationEnergyPoint.h"
#include "connectionMechanism/GripperConnectionMechanism.h"
#include <neuralnetworks/NeuralNetwork.h>

class MedeaAggregationControlArchitecture : public BehaviorControlArchitecture
{
	private:

		int _iteration;
		MedeaAggregationAgentWorldModel *_wm;

		std::vector<double> _parameters;
		std::string _nnType;
		bool _typeEP;

		Neural::NeuralNetwork* nn;

		void searchClosestEnergyPoint(Point2d posRobot, std::vector<Point2d> energyPoints);

		void createNN();
		void perceptronStep();

	public:
		//Initializes the variables
		MedeaAggregationControlArchitecture( RobotAgentWorldModel *__wm );
		~MedeaAggregationControlArchitecture();
		
		void reset();
		void step();		// if (_wm._age<0) then move randomly (useful to unstuck robot in evolution mode)
};


#endif

