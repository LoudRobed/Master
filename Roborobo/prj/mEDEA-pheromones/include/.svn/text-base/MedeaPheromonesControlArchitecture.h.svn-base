/**
 * @file
 * @author Nicolas Bredeche <nicolas.bredeche@gmail.com>
 * 
 * History :
 *  - imported from medea-basic project on 16/6/2012
 *
 */



#ifndef MEDEAPHEROMONESCONTROLARCHITECTURE_H
#define MEDEAPHEROMONESCONTROLARCHITECTURE_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Utilities/SDL_gfxRoborobo.h"
#include "BehaviorControlArchitectures/BehaviorControlArchitecture.h"
#include "mEDEA-pheromones/include/MedeaPheromonesAgentWorldModel.h"
#include "mEDEA-pheromones/include/MedeaPheromonesAgentObserver.h"
#include <neuralnetworks/NeuralNetwork.h>


using namespace Neural;


class MedeaPheromonesControlArchitecture : public BehaviorControlArchitecture
{
	private:

		int _iteration;
		MedeaPheromonesAgentWorldModel *_wm;

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
		MedeaPheromonesControlArchitecture(RobotAgentWorldModel *wm);
		~MedeaPheromonesControlArchitecture();

		void reset();
		void step();		// if (_wm._age<0) then move randomly (useful to unstuck robot in evolution mode)

		static unsigned int computeRequiredNumberOfWeights(MedeaPheromonesAgentWorldModel *wm);
};


#endif

