/*
 *  MedeaAltruismPerceptronControlArchitecture.h
 *  roborobo-online
 *
 *  Created by Nicolas on 20/03/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */


#ifndef MedeaAltruismENERGYPERCEPTRONCONTROLARCHITECTURE_H
#define MedeaAltruismENERGYPERCEPTRONCONTROLARCHITECTURE_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Utilities/SDL_gfxRoborobo.h"

#include "BehaviorControlArchitectures/BehaviorControlArchitecture.h"
#include "mEDEA-altruism/include/MedeaAltruismAgentWorldModel.h"
#include "mEDEA-altruism/include/MedeaAltruismAgentObserver.h"

class MedeaAltruismPerceptronControlArchitecture : public BehaviorControlArchitecture
{
	private:

		int _iteration;
		MedeaAltruismAgentWorldModel *_wm;

		std::vector<double> _parameters;
		int _nbHiddenNeurons;

		void searchClosestEnergyPoint(Point2d posRobot, std::vector<Point2d> energyPoints);

	public:
		//Initializes the variables
		MedeaAltruismPerceptronControlArchitecture( RobotAgentWorldModel *__wm );
		~MedeaAltruismPerceptronControlArchitecture();
		
		void reset();
		void step();		// if (_wm._age<0) then move randomly (useful to unstuck robot in evolution mode)

};


#endif

