/**
 * @file
 * @author Leo Cazenille <leo.cazenille@gmail.com>
 * TODO : Add formal description
 * History :
 *
 *
 */



#ifndef MEDEAHGTENERGYNNCONTROLARCHITECTURE_H
#define MEDEAHGTENERGYNNCONTROLARCHITECTURE_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Utilities/SDL_gfxRoborobo.h"
#include "BehaviorControlArchitectures/BehaviorControlArchitecture.h"
#include "mEDEA-HGT/include/MedeaHGTAgentWorldModel.h"
#include "mEDEA-HGT/include/MedeaHGTAgentObserver.h"
#include <neuralnetworks/NeuralNetwork.h>


using namespace Neural;


class MedeaHGTNNControlArchitecture : public BehaviorControlArchitecture
{
	private:

		int _iteration;
		MedeaHGTAgentWorldModel *_wm;

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
		MedeaHGTNNControlArchitecture(RobotAgentWorldModel *wm);
		~MedeaHGTNNControlArchitecture();

		void reset();
		void step();		// if (_wm._age<0) then move randomly (useful to unstuck robot in evolution mode)

		static unsigned int computeRequiredNumberOfWeights(MedeaHGTAgentWorldModel *wm);
};


#endif

