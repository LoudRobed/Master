/*
 *  MedeaAltUtilityPerceptronControlArchitecture.h
 *  roborobo-online
 *
 *  Created by Nicolas on 20/03/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */


#ifndef MedeaAltUtilityENERGYPERCEPTRONCONTROLARCHITECTURE_H
#define MedeaAltUtilityENERGYPERCEPTRONCONTROLARCHITECTURE_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Utilities/SDL_gfxRoborobo.h"

#include "BehaviorControlArchitectures/BehaviorControlArchitecture.h"
#include "mEDEA-altruism-utility/include/MedeaAltUtilityAgentWorldModel.h"
#include "mEDEA-altruism-utility/include/MedeaAltUtilityAgentObserver.h"

class MedeaAltUtilityPerceptronControlArchitecture : public BehaviorControlArchitecture
{
	private:

		int _iteration;
		MedeaAltUtilityAgentWorldModel *_wm;

		std::vector<double> _parameters;
		int _nbHiddenNeurons;

		void searchClosestEnergyPoint(Point2d posRobot, std::vector<Point2d> energyPoints);

	public:
		//Initializes the variables
		MedeaAltUtilityPerceptronControlArchitecture( RobotAgentWorldModel *__wm );
		~MedeaAltUtilityPerceptronControlArchitecture();
		
		void reset();
		void step();		// if (_wm._age<0) then move randomly (useful to unstuck robot in evolution mode)

};


#endif

