/*
 *  MedeaOptimWorldObserver.h
 *
 *  Created by Nicolas on 19/1/2011
 *
 */



#ifndef MedeaOptimWORLDOBSERVER_H
#define MedeaOptimWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/Observer.h"

#include "mEDEA-optim/include/MedeaOptimSharedData.h"
#include "mEDEA-optim/include/MedeaOptimAgentWorldModel.h"

class World;

class MedeaOptimWorldObserver : public WorldObserver
{
	private:
		void updateExperimentalSettings(); // check and update (only if required) experimental setting.
		void updateEnvironmentResources();
		void updateAllAgentsEnergyLevel();
		
		int _activeAgents_genStart; // log
		int _activeAgents_genEnd;   // log

	protected:
		int _generationCount;
		int _lifeIterationCount;

	public:
		MedeaOptimWorldObserver( World *__world );
		~MedeaOptimWorldObserver();
				
		void reset();
		void step();
		
		int getLifeIterationCount();

};

#endif