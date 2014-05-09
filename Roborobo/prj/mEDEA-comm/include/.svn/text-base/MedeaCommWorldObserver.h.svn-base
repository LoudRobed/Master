/*
 *  WorldObserver.h
 *  roborobo-online
 *
 *  Created by Nicolas on 25/05/10
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */



#ifndef MEDEACOMMWORLDOBSERVER_H
#define MEDEACOMMWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/Observer.h"

#include "mEDEA-comm/include/MedeaCommSharedData.h"
#include "mEDEA-comm/include/MedeaCommAgentWorldModel.h"
#include "mEDEA-comm/include/MedeaCommEnergyPoint.h"

class World;

class MedeaCommWorldObserver : public WorldObserver
{
	protected:
		void updateAllAgentsEnergyLevel();
		void updateAllAgentsDistanceToEnergyPoints();

		std::vector<MedeaCommEnergyPoint*> coopEnergyPoints;
		double fixedCost;
		int nbEnergyPoints;
		int _lifeIterationCount;
		bool firstIteration;

		double maxCostAction;
		double maxCostCommunication;

	public:
		MedeaCommWorldObserver( World *__world );
		~MedeaCommWorldObserver();
				
		void reset();
		void step();
		
		int getLifeIterationCount();

};

#endif
