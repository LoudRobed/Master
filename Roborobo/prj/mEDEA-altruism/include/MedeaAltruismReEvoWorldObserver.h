/*
 *  MedeaAltruismReEvoWorldObserver.h
 *  roborobo-online
 *
 *  Created by Nicolas on 25/05/10
 *  moved in altruism by Jean-Marc on 17/09/2010
 *  modification for ReEvo : Jean-Marc 2/4/2011
 *
 */



#ifndef MEDEAALTRUISMREEVOWORLDOBSERVER_H
#define MEDEAALTRUISMREEVOWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/Observer.h"

#include "mEDEA-altruism/include/MedeaAltruismSharedData.h"
#include "mEDEA-altruism/include/MedeaAltruismAgentWorldModel.h"

class World;

class MedeaAltruismReEvoWorldObserver : public WorldObserver
{
	private:
		void updateAllAgentsEnergyLevel();
		double fixedCost;
		void loadGenomes();

		std::vector< std::vector<double> > _genomesToReplay;
		bool _firstStep;

	protected:
		int _lifeIterationCount;

	public:
		MedeaAltruismReEvoWorldObserver( World *__world );
		~MedeaAltruismReEvoWorldObserver();

				
		void reset();
		void step();
		
		int getLifeIterationCount();

};

#endif
