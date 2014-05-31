/**
 * @file
 * @author Nicolas Bredeche <nicolas.bredeche@gmail.com>
 * 
 * History :
 *  - imported from medea-basic project on 16/6/2012
 *
 */




#ifndef MEDEAECOLOGYCONTROLARCHITECTURE_H
#define MEDEAECOLOGYCONTROLARCHITECTURE_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Utilities/SDL_gfxRoborobo.h"
#include "BehaviorControlArchitectures/BehaviorControlArchitecture.h"
#include "mEDEA-ecology/include/MedeaEcologyAgentWorldModel.h"
#include "mEDEA-ecology/include/MedeaEcologyAgentObserver.h"
#include <neuralnetworks/NeuralNetwork.h>


using namespace Neural;


class MedeaEcologyControlArchitecture : public BehaviorControlArchitecture
{
	private:

		int _iteration;
		MedeaEcologyAgentWorldModel *_wm;

		std::vector<double> _parameters;
		std::string _nnType;
		int _nbHiddenLayers;
		std::vector<int> _nbHiddenNeuronsPerLayer;
		std::vector<int> _nbBiaisNeuronsPerLayer;
		NeuralNetwork* nn;

		void searchClosestEnergyPoint(Point2d posRobot, std::vector<Point2d> energyPoints);

		void createNN();


	public:
		//Initializes the variables
		MedeaEcologyControlArchitecture(RobotAgentWorldModel *wm);
		~MedeaEcologyControlArchitecture();

		void reset();
		void step();		// if (_wm._age<0) then move randomly (useful to unstuck robot in evolution mode)

		static unsigned int computeRequiredNumberOfWeights(MedeaEcologyAgentWorldModel *wm);
};


#endif

