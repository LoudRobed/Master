/*
 *  MedeaAltruismAgentWorldModel.h
 *  roborobo-online
 *
 *  Created by Nicolas on 15/04/10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */


#ifndef MedeaAltruismEVOLVINGROBOTAGENTWORLDMODEL_H
#define MedeaAltruismEVOLVINGROBOTAGENTWORLDMODEL_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "WorldModels/EvolvingRobotAgentWorldModel.h"
#include "area/BoxIdleness.h"

//class World;

class MedeaAltruismAgentWorldModel : public EvolvingRobotAgentWorldModel
{
	protected:
		
		double _energyPointDirectionAngleValue; // angle to closest energy point -- normalized btw -1 and +1
		double _energyPointDistanceValue ; // distance to the closest energy point -- normalized btw 0  and 1
		
		bool _isActive; // agent stand still if not.

		double _energyLevel;
		double _deltaEnergy;

		double _angleToClosestEnergyPoint;
		double _distanceToClosestEnergyPoint;

		double _energyHarvestingRate;

		int _fatherId;
		int _maturity;
		int _dateOfBirth;
		int _lifeTime;
		bool _waitForGenome;
		
	public:
		MedeaAltruismAgentWorldModel();
		~MedeaAltruismAgentWorldModel();
	
		//access method
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

		//compatibility issue with ReEvo
		bool getWaitingAfterLifeSynchronization();
		void setWaitingAfterLifeSynchronization( bool isSynchronized );

		void setAngleToClosestEnergyPoint( double __value );
		double getAngleToClosestEnergyPoint();
		
		void setDistanceToClosestEnergyPoint( double __value );
		double getDistanceToClosestEnergyPoint();

		void setEnergyHarvestingRate(double __energyHarvestingRate);		
		double getEnergyHarvestingRate();

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

		// idlenessTracker
		BoxIdleness _idlenessTracker;
		
};


#endif

