/*
 *  MedeaOptimPerceptronControlArchitecture.h
 *
 *  Created by Nicolas on 19/1/2011
 *
 */


#ifndef MedeaOptimPERCEPTRONCONTROLARCHITECTURE_H
#define MedeaOptimPERCEPTRONCONTROLARCHITECTURE_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Utilities/SDL_gfxRoborobo.h"

#include "BehaviorControlArchitectures/BehaviorControlArchitecture.h"
#include "mEDEA-optim/include/MedeaOptimAgentWorldModel.h"
#include "mEDEA-optim/include/MedeaOptimAgentObserver.h"

class MedeaOptimPerceptronControlArchitecture : public BehaviorControlArchitecture
{
	private:

		int _iteration;
		MedeaOptimAgentWorldModel *_wm;

		std::vector<double> _parameters;
		int _nbHiddenNeurons;

		void searchClosestEnergyPoint(Point2d posRobot, std::vector<Point2d> energyPoints);

	public:
		//Initializes the variables
		MedeaOptimPerceptronControlArchitecture( RobotAgentWorldModel *__wm );
		~MedeaOptimPerceptronControlArchitecture();
		
		void reset();
		void step();		// if (_wm._age<0) then move randomly (useful to unstuck robot in evolution mode)

};


#endif

