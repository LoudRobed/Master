/**
 * @file
 * @author Leo Cazenille <leo.cazenille@gmail.com>
 * TODO : Add formal description
 * History :
 *
 *
 */




#ifndef MEDEAHGTWORLDOBSERVER_H
#define MEDEAHGTWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Observers/Observer.h"
#include "mEDEA-HGT/include/MedeaHGTSharedData.h"
#include "mEDEA-HGT/include/MedeaHGTAgentWorldModel.h"
#include "mEDEA-HGT/include/MedeaHGTSharedData.h"


//class World;

class MedeaHGTWorldObserver : public WorldObserver
{
	private:
		void updateExperimentalSettings(); // check and update (only if required) experimental setting.
		void updateEnvironmentResources();
		void updateAllAgentsEnergyLevel();
		void updatePopulations();
		void initPopulations();

	protected:
		int _generationCount;
		int _lifeIterationCount;

		int _numberOfPopulations;
		std::vector<unsigned int> _populationsSize;

	public:
		MedeaHGTWorldObserver(World *world);
		~MedeaHGTWorldObserver();

		void reset();
		void step();

		int getLifeIterationCount();
		int getNumberOfPopulations();
		std::vector<unsigned int> getPopulationsSize();

};

#endif
