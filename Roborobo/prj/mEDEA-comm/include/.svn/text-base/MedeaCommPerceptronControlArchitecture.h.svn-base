/*
 *  MedeaCommPerceptronControlArchitecture.h
 *  roborobo-online
 *
 *  Created by Nicolas on 20/03/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */


#ifndef MedeaCommENERGYPERCEPTRONCONTROLARCHITECTURE_H
#define MedeaCommENERGYPERCEPTRONCONTROLARCHITECTURE_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Utilities/SDL_gfxRoborobo.h"

#include "BehaviorControlArchitectures/BehaviorControlArchitecture.h"
#include "mEDEA-comm/include/MedeaCommAgentWorldModel.h"
#include "mEDEA-comm/include/MedeaCommAgentObserver.h"
#include "mEDEA-comm/include/MedeaCommEnergyPoint.h"

class MedeaCommPerceptronControlArchitecture : public BehaviorControlArchitecture
{
	private:

		int _iteration;
		MedeaCommAgentWorldModel *_wm;

		std::vector<double> _parameters;
		int _nbHiddenNeurons;

		void searchClosestEnergyPoint(Point2d posRobot, std::vector<Point2d> energyPoints);

	public:
		//Initializes the variables
		MedeaCommPerceptronControlArchitecture( RobotAgentWorldModel *__wm );
		~MedeaCommPerceptronControlArchitecture();
		
		void reset();
		void step();		// if (_wm._age<0) then move randomly (useful to unstuck robot in evolution mode)

};


#endif

