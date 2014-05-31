/*
 *  MedeaOptimAgentWorldModel.h
 *
 *  Created by Nicolas on 19/1/2011
 *
 */


#ifndef MedeaOptimAGENTWORLDMODEL_H
#define MedeaOptimAGENTWORLDMODEL_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "WorldModels/EvolvingRobotAgentWorldModel.h"

//class World;

class MedeaOptimAgentWorldModel : public EvolvingRobotAgentWorldModel
{
	protected:
		
		double _fitnessValue; // specific to MedeaOptim project
		
		double _energyPointDirectionAngleValue; // angle to closest energy point -- normalized btw -1 and +1
		double _energyPointDistanceValue ; // distance to the closest energy point -- normalized btw 0  and 1
		
		bool _isActive; // agent stand still if not.

		double _energyLevel;
		double _deltaEnergy;

		double _angleToClosestEnergyPoint;
		double _distanceToClosestEnergyPoint;


		
	public:
		//Initializes the variables
		MedeaOptimAgentWorldModel();
		~MedeaOptimAgentWorldModel();

		double getEnergyPointDirectionAngleValue();
		void setEnergyPointDistanceValue( double __value );

		double getEnergyPointDistanceValue();
		void setEnergyPointDirectionAngleValue( double __value );

		double getEnergyLevel();
		void setEnergyLevel(double inValue);
		
		double getDeltaEnergy();
		void setDeltaEnergy(double inValue);

		bool getActiveStatus();
		void setActiveStatus( bool __isActive );

		void setAngleToClosestEnergyPoint( double __value );
		double getAngleToClosestEnergyPoint();
		
		void setDistanceToClosestEnergyPoint( double __value );
		double getDistanceToClosestEnergyPoint();

		void setFitness ( double __value );
		double getFitness ();


		// evolutionary engine

		std::map<int, std::vector<double> > _genomesList;
		std::map<int, float > _sigmaList;
		std::map<int, double > _fitnessList;

		float _currentSigma;
		
		
		void resetActiveGenome();

		// ANN

		double _minValue;
		double _maxValue;
		int _nbLayer;
		int _nbHiddenNeurons;


};


#endif

