/*
 *  MedeaAltruismBattleWorldObserver.h
 *  roborobo-online
 *
 *  Created by Jean-Marc on 01/02/10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */



#ifndef MEDEAALTRUISMBATTLEWORLDOBSERVER_H
#define MEDEAALTRUISMBATTLEWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/Observer.h"

#include "mEDEA-altruism/include/MedeaAltruismSharedData.h"

class World;

class MedeaAltruismBattleWorldObserver : public WorldObserver
{
	private:
		void updateAllAgentsEnergyLevel();
		double fixedCost;
		double exponentialFactor;

	protected:
		int _lifeIterationCount;
		bool _firstStep;
		std::vector< std::vector<double> > _genomesToLoad;
		int _nbGenomeToLoad;

	public:
		//Initializes the variables
		MedeaAltruismBattleWorldObserver( World *__world );
		~MedeaAltruismBattleWorldObserver();
				
		void reset();
		void step();

		void loadGenomes();

};

#endif

