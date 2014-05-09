/*
 *  MedeaAltUtilityReplayWorldObserver.h
 *  roborobo-online
 *
 *  Created by Jean-Marc on 20/04/10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */



#ifndef MEDEAALTUTILITYREPLAYWORLDOBSERVER_H
#define MEDEAALTUTILITYREPLAYWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/Observer.h"

class World;

class MedeaAltUtilityReplayWorldObserver : public WorldObserver
{
	private:
//		World *_world;
		bool _firstStep;
		std::vector<double> _genomeToReplay;
		void updateEnvironmentResources();
		void updateAllAgentsEnergyLevel();

	protected:
		int _generationCount;
		int _lifeIterationCount;
		
	public:
		//Initializes the variables
		MedeaAltUtilityReplayWorldObserver( World *__world );
		~MedeaAltUtilityReplayWorldObserver();
				
		void reset();
		void step();
		void loadGenome();

};

#endif

