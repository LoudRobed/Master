/*
 *  MedeaAggregationAgentWorldModel.h
 *  roborobo-online
 *
 *  Created by Nicolas on 15/04/10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */


#ifndef MEDEAAGGREGATIONAGENTWORLDMODEL_H
#define MEDEAAGGREGATIONAGENTWORLDMODEL_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

//#include "WorldModels/EvolvingRobotAgentWorldModel.h"
#include "WorldModels/RobotAgentConnectableWorldModel.h"
#include "area/BoxIdleness.h"
#include "connectionMechanism/GripperConnectionMechanism.h"

//class World;

//class MedeaAggregationAgentWorldModel : public EvolvingRobotAgentWorldModel
class MedeaAggregationAgentWorldModel : public RobotAgentConnectableWorldModel
{
	protected:
		
		double _energyPointDirectionAngleValue; // angle to closest energy point -- normalized btw -1 and +1
		double _energyPointDistanceValue ; // distance to the closest energy point -- normalized btw 0  and 1
		double _energyPointType ; // type of the closest energy point -- either -1 or 1

		double _energyLevel;
		double _deltaEnergy;

		double _angleToClosestEnergyPoint;
		double _distanceToClosestEnergyPoint;

		double _energyHarvestingRate;

		int _fatherId;
		int _maturity;
		int _dateOfBirth;
		int _lifeTime;
		bool _isNewGenome;

		int _status;

		bool _firstStep;
		GripperConnectionMechanism* _connection;
		
	public:
		MedeaAggregationAgentWorldModel();
		~MedeaAggregationAgentWorldModel();

		//possible status
		static const int ACTIVE = 0;
		static const int LISTEN = 1;
		static const int DEAD = 2;
	
		//access method
		double getEnergyPointDirectionAngleValue();
		void setEnergyPointDistanceValue( double __value );

		double getEnergyPointDistanceValue();
		void setEnergyPointDirectionAngleValue( double __value );

		double getEnergyPointType();
		void setEnergyPointType( double __value );

		double getEnergyLevel();
		void setEnergyLevel(double inValue);
		
		double getDeltaEnergy();
		void setDeltaEnergy(double inValue);

		void setAngleToClosestEnergyPoint( double __value );
		double getAngleToClosestEnergyPoint();
		
		void setDistanceToClosestEnergyPoint( double __value );
		double getDistanceToClosestEnergyPoint();

		void setEnergyHarvestingRate(double __energyHarvestingRate);		
		double getEnergyHarvestingRate();

		void setUpGripper(GripperConnectionMechanism* gripper);
		void setGripperStatus(int status);
		int getGripperStatus();

		void setFirstStep (bool firstStep);
		bool getFirstStep();

		// evolutionary engine

		std::map<int, std::vector<double> > _genomesList;
		std::map<int, float > _sigmaList;
		std::vector<double> _currentGenome;
		std::vector<double> _genome; // todo: accessing
		float _currentSigma;

		void resetActiveGenome(int nbGene);

		bool getNewGenomeStatus();
		void setNewGenomeStatus( bool __status );

		void setFatherId(int fathId);
		int getFatherId();

		void setMaturity(int maturity);
		int getMaturity();

		void setDateOfBirth(int dateOfBirth);
		int getDateOfBirth();

		void setLifeTime(int lifeTime);
		int getLifeTime();

		int getStatus();
		void setStatus( int __status );

		bool getWaitingAfterLifeSynchronization();
		void setWaitingAfterLifeSynchronization( bool isSynchronized );

		// ANN

		double _minValue;
		double _maxValue;
		int _nbGenes;
		int _nbLayer;
		int _nbInputs;
		int _nbHiddenNeurons;
		std::string nnType;

		// idlenessTracker
		BoxIdleness _idlenessTracker;
		
};


#endif

