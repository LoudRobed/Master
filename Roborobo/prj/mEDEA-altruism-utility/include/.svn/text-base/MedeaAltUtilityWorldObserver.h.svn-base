/*
 *  WorldObserver.h
 *  roborobo-online
 *
 *  Created by Nicolas on 25/05/10
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */



#ifndef MEDEAALTUTILITYWORLDOBSERVER_H
#define MEDEAALTUTILITYWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/Observer.h"

#include "mEDEA-altruism-utility/include/MedeaAltUtilitySharedData.h"
#include "mEDEA-altruism-utility/include/MedeaAltUtilityAgentWorldModel.h"

class World;

class MedeaAltUtilityWorldObserver : public WorldObserver
{
	private:
		void updateExperimentalSettings(); // check and update (only if required) experimental setting.
		void updateEnvironmentResources();
		void updateAllAgentsEnergyLevel();

	protected:
		int _generationCount;
		int _lifeIterationCount;

	public:
		MedeaAltUtilityWorldObserver( World *__world );
		~MedeaAltUtilityWorldObserver();
				
		void reset();
		void step();
		
		int getLifeIterationCount();

};

#endif
