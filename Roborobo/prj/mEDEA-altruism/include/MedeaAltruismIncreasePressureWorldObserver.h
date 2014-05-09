/*
 *  MedeaAltruismIncreasePressureWorldObserver.h
 *  roborobo-online
 *
 *  Created by Nicolas on 25/05/10
 *  moved in altruism by Jean-Marc on 17/09/2010
 * 	modification for IncreasePressure : Jean-marc 21/08/2012
 *
 */



#ifndef MEDEAALTRUISMINCREASEPRESSUREWORLDOBSERVER_H
#define MEDEAALTRUISMINCREASEPRESSUREWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/Observer.h"

#include "mEDEA-altruism/include/MedeaAltruismSharedData.h"
#include "mEDEA-altruism/include/MedeaAltruismAgentWorldModel.h"

class World;

class MedeaAltruismIncreasePressureWorldObserver : public WorldObserver
{
	private:
		void updateAllAgentsEnergyLevel();
		double fixedCost;
		double exponentialFactor;
		void loadGenomes();

		std::vector< std::vector<double> > _genomesToReplay;
		bool _firstStep;

		int amountIncreasePressure;
		int intervalIncreasePressure;
		int thresholdIncreasePressure;

	protected:
		int _lifeIterationCount;

	public:
		MedeaAltruismIncreasePressureWorldObserver( World *__world );
		~MedeaAltruismIncreasePressureWorldObserver();
				
		void reset();
		void step();
		
		int getLifeIterationCount();

};

#endif
