/**
 * @file
 * @author Nicolas Bredeche <nicolas.bredeche@gmail.com>
 * 
 * History :
 *  - imported from medea-basic project on 16/6/2012
 *
 */




#ifndef MEDEAPHEROMONESWORLDOBSERVER_H
#define MEDEAPHEROMONESWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Observers/Observer.h"
#include "mEDEA-pheromones/include/MedeaPheromonesSharedData.h"
#include "mEDEA-pheromones/include/MedeaPheromonesAgentWorldModel.h"
#include "mEDEA-pheromones/include/MedeaPheromonesSharedData.h"


//class World;

class MedeaPheromonesWorldObserver : public WorldObserver
{
	private:
		void updateExperimentalSettings(); // check and update (only if required) experimental setting.
		void updateEnvironmentResources();
		void updateAllAgentsEnergyLevel();

	protected:
		int _generationCount;
		int _lifeIterationCount;

	public:
		MedeaPheromonesWorldObserver(World *world);
		~MedeaPheromonesWorldObserver();

		void reset();
		void step();

		int getLifeIterationCount();

};

#endif
