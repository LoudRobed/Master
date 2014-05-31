/*
 *  MedeaAltruismReplayWorldObserver.h
 *  roborobo-online
 *
 *  Created by Jean-Marc on 20/04/10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */



#ifndef MEDEAALTRUISMREPLAYWORLDOBSERVER_H
#define MEDEAALTRUISMREPLAYWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/Observer.h"

class World;

class MedeaAltruismReplayWorldObserver : public WorldObserver
{
	private:
//		World *_world;
		bool _firstStep;
		std::vector<double> _genomeToReplay;
		void updateEnvironmentResources();
		void updateAllAgentsEnergyLevel();
		double fixedCost;
		double exponentialFactor;

	protected:
		int _generationCount;
		int _lifeIterationCount;
		
	public:
		//Initializes the variables
		MedeaAltruismReplayWorldObserver( World *__world );
		~MedeaAltruismReplayWorldObserver();
				
		void reset();
		void step();
		void loadGenome();
		int getLifeIterationCount();

};

#endif

