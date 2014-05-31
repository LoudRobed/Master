/*
 *  MedeaAltruismReplayPartialEvoWorldObserver.h
 *  roborobo-online
 *
 *  Created by Jean-Marc on 20/04/10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *  moved in partial evo by Jean-Marc on 08/12/2010
 *
 */



#ifndef MEDEAALTRUISMREPLAYPARTIALEVOWORLDOBSERVER_H
#define MEDEAALTRUISMREPLAYPARTIALEVOWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/Observer.h"

class World;

class MedeaAltruismReplayPartialEvoWorldObserver : public WorldObserver
{
	private:
//		World *_world;
		bool _firstStep;
		std::vector<double> _genomeToReplay;
		void updateAllAgentsEnergyLevel();

	protected:
		int _generationCount;
		int _lifeIterationCount;
		float movementQuantity;
		
	public:
		//Initializes the variables
		MedeaAltruismReplayPartialEvoWorldObserver( World *__world );
		~MedeaAltruismReplayPartialEvoWorldObserver();
				
		void reset();
		void step();
		void loadGenome();

		int getLifeIterationCount();

};

#endif

