/*
 *  MedeaCommAgentWorldModel.h
 *  roborobo-online
 *
 *  Created by Nicolas on 15/04/10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */


#ifndef MedeaCommEVOLVINGROBOTAGENTWORLDMODEL_H
#define MedeaCommEVOLVINGROBOTAGENTWORLDMODEL_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "WorldModels/EvolvingRobotAgentWorldModel.h"

#include "mEDEA-comm/include/MedeaCommSharedData.h"

//class World;

class MedeaCommAgentWorldModel : public EvolvingRobotAgentWorldModel
{
	protected:
		
		bool _isActive; // agent stand still if not.

		double _energyLevel;
		double _deltaEnergy;

		double _angleToClosestEnergyPoint;
		double _distanceToClosestEnergyPoint;
		double _action;
		double _communication;
		std::vector<double> _receivedCommunication;
		bool _isInContest;

		int _fatherId;
		int _maturity;
		int _dateOfBirth;
		int _lifeTime;
		bool _waitForGenome;
		
	public:
		MedeaCommAgentWorldModel();
		~MedeaCommAgentWorldModel();
	
		//access method

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

		void setAction ( double __value );
		double getAction ();

		void setCommunication ( double __value );
		double getCommunication ();

		void setReceivedCommunication ( std::vector<double> __value );
		std::vector<double> getReceivedCommunication ();

		void setIsInContest ( bool __value );
		bool getIsInContest ();

		void setFatherId(int fathId);
		int getFatherId();

		void setMaturity(int maturity);
		int getMaturity();

		void setDateOfBirth(int dateOfBirth);
		int getDateOfBirth();

		void setLifeTime(int lifeTime);
		int getLifeTime();

		void setWaitForGenome(bool wait);
		bool getWaitForGenome();

		// evolutionary engine

		std::map<int, std::vector<double> > _genomesList;
		std::map<int, float > _sigmaList;
		std::vector<double> _currentGenome;
		float _currentSigma;

		void resetActiveGenome();

		// ANN

		double _minValue;
		double _maxValue;
		int _nbLayer;
		int _nbHiddenNeurons;


};


#endif

