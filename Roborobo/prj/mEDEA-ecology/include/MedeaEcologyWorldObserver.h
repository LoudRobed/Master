/**
 * @file
 * @author Nicolas Bredeche <nicolas.bredeche@gmail.com>
 * 
 * History :
 *  - imported from medea-basic project on 16/6/2012
 *
 */





#ifndef MEDEAECOLOGYWORLDOBSERVER_H
#define MEDEAECOLOGYWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Observers/Observer.h"
#include "mEDEA-ecology/include/MedeaEcologySharedData.h"
#include "mEDEA-ecology/include/MedeaEcologyAgentWorldModel.h"
#include "mEDEA-ecology/include/MedeaEcologySharedData.h"


//class World;

class MedeaEcologyWorldObserver : public WorldObserver
{
	private:
		void updateExperimentalSettings(); // check and update (only if required) experimental setting.
		void updateEnvironmentResources();
		void updateAllAgentsEnergyLevel();

	protected:
		int _generationCount;
		int _lifeIterationCount;

	public:
		MedeaEcologyWorldObserver(World *world);
		~MedeaEcologyWorldObserver();

		void reset();
		void step();

		int getLifeIterationCount();

};

#endif
