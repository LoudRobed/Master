/*
 *  WorldObserver.h
 *  roborobo-online
 *
 *  Created by Nicolas on 25/05/10
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */



#ifndef MEDEAALTRUISMWORLDOBSERVER_H
#define MEDEAALTRUISMWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/Observer.h"

#include "mEDEA-altruism/include/MedeaAltruismSharedData.h"
#include "mEDEA-altruism/include/MedeaAltruismAgentWorldModel.h"

class World;

class MedeaAltruismWorldObserver : public WorldObserver
{
	private:
		void updateAllAgentsEnergyLevel();
		double fixedCost;
		double exponentialFactor;

	protected:
		int _lifeIterationCount;

	public:
		MedeaAltruismWorldObserver( World *__world );
		~MedeaAltruismWorldObserver();
				
		void reset();
		void step();
		
		int getLifeIterationCount();

};

#endif
