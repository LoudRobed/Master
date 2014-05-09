/*
 *  RobotAgentConnectableWorldModel.h
 *
 *  Created by Jean-Marc on 22/03/13
 * 		Based on word done by berend in a separate branch
 *
 */


#ifndef ROBOTAGENTCONNECTABLEWORLDMODEL_H
#define ROBOTAGENTCONNECTABLEWORLDMODEL_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "WorldModels/RobotAgentWorldModel.h"

class RobotAgentConnectableWorldModel : public RobotAgentWorldModel
{	
	public:
		RobotAgentConnectableWorldModel();
		~RobotAgentConnectableWorldModel();

		bool joinedOrganism;
		
};


#endif


