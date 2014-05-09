/*
 *  MedeaAggregationWorldObserver.h
 *  roborobo-online
 *
 *  Created by Nicolas on 25/05/10
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */



#ifndef MEDEAAGGREGATIONWORLDOBSERVER_H
#define MEDEAAGGREGATIONWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/Observer.h"

#include "mEDEA-aggregation/include/MedeaAggregationSharedData.h"
#include "mEDEA-aggregation/include/MedeaAggregationAgentWorldModel.h"
#include "mEDEA-aggregation/include/MedeaAggregationEnergyPoint.h"

class World;

class MedeaAggregationWorldObserver : public WorldObserver
{
	private:
		void updateAllAgentsEnergyLevel();
		void updateAllAgentsDistanceToEnergyPoints();

		std::vector<MedeaAggregationEnergyPoint*> specificEnergyPoints;
		double fixedCost;
		int nbEnergyPoints;
		double temperature;
		double exponentialFactor;
		int margin;

		bool firstIteration;

	protected:
		int _lifeIterationCount;
		std::string agentPositiveMaskImageFilename;
		std::string agentNegativeMaskImageFilename;
		SDL_Surface *agentPositiveMaskImage;	// mask used for showing that an agent wants to connect
		SDL_Surface *agentNegativeMaskImage;	// mask used for showing that an agent wants to connect

	public:
		MedeaAggregationWorldObserver( World *__world );
		~MedeaAggregationWorldObserver();
				
		void reset();
		void step();
		
		int getLifeIterationCount();

};

#endif
