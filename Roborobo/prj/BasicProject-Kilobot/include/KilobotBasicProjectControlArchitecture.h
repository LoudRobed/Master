/*
 *  KilobotBasicControlArchitecture.h
 *  roborobo-online
 *
 *  Created by Nicolas on 27/05/10.
 *
 */


#ifndef KILOBOTBASICCONTROLARCHITECTURE_H
#define KILOBOTBASICCONTROLARCHITECTURE_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "BehaviorControlArchitectures/BehaviorControlArchitecture.h"

#include "WorldModels/RobotAgentWorldModel.h"

class KilobotBasicControlArchitecture : public BehaviorControlArchitecture
{
	public:
		//Initializes the variables
		KilobotBasicControlArchitecture( RobotAgentWorldModel *__wm );
		~KilobotBasicControlArchitecture();
		
		void reset();
		void step();
};


#endif

