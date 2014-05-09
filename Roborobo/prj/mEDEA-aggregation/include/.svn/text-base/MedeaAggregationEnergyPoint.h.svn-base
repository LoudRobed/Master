/*
 *  MedeaAggregationEnergyPoint.h
 *  roborobo
 *
 *  Created by Jean-Marc on 25/05/11.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef MEDEAAGGREGATIONENERGYPOINT_H
#define MEDEAAGGREGATIONENERGYPOINT_H

#include "RoboroboMain/common.h"
#include "Utilities/Misc.h"
#include "World/InanimateObject.h"
#include "World/EnergyPoint.h"

#include "mEDEA-aggregation/include/MedeaAggregationSharedData.h"

class MedeaAggregationEnergyPoint : public EnergyPoint
{
	public :
	
		MedeaAggregationEnergyPoint(int uid, int harvestingOrganismSize, int margin);
		~MedeaAggregationEnergyPoint();

		void init();
		void display();
		void hide();
		void step();

		double getRadius();
		double getHarvestingOrganismSize();

		double getEnergy();
	
	protected :
		double harvestingOrganismSize;
		double energyPointRespawnLagMaxValue;
		int margin;
		int uid;

		void generatePosition(int inHarvestingOrganismSize, int margin, double &x, double &y);
	
};

#endif
