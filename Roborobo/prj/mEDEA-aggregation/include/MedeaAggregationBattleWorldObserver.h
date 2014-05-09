/*
 *  MedeaAggregationBattleWorldObserver.h
 *  roborobo-online
 *
 *  Created by Nicolas on 25/05/10
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */



#ifndef MEDEAAGGREGATIONBATTLEWORLDOBSERVER_H
#define MEDEAAGGREGATIONBATTLEWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/Observer.h"

#include "mEDEA-aggregation/include/MedeaAggregationSharedData.h"
#include "mEDEA-aggregation/include/MedeaAggregationAgentWorldModel.h"

class World;

class MedeaAggregationBattleWorldObserver : public WorldObserver
{
	private:
		void updateAllAgentsEnergyLevel();
		double fixedCost;
		double exponentialFactor;

	protected:
		int _lifeIterationCount;
		std::string agentPositiveMaskImageFilename;
		std::string agentNegativeMaskImageFilename;
		SDL_Surface *agentPositiveMaskImage;	// mask used for showing that an agent wants to connect
		SDL_Surface *agentNegativeMaskImage;	// mask used for showing that an agent wants to connect

		bool _firstStep;
		std::vector< std::vector<double> > _genomesToLoad;
		int _nbGenomeToLoad;

	public:
		MedeaAggregationBattleWorldObserver( World *__world );
		~MedeaAggregationBattleWorldObserver();
				
		void reset();
		void step();
		
		int getLifeIterationCount();
		void loadGenomes();
};

#endif
