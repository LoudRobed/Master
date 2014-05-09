/*
 *  MedeaCommEnergyPoint.h
 *  roborobo
 *
 *  Created by Jean-Marc on 25/05/11.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef MEDEACOMMENERGYPOINT_H
#define MEDEACOMMENERGYPOINT_H

#include "RoboroboMain/common.h"
#include "Utilities/Misc.h"
#include "World/InanimateObject.h"
#include "World/EnergyPoint.h"

#include "mEDEA-comm/include/MedeaCommSharedData.h"

class MedeaCommEnergyPoint : public EnergyPoint
{
	public :
	
		MedeaCommEnergyPoint();
		~MedeaCommEnergyPoint();

		void display();
		void hide();
		void step();

		double getRadius();
		double getHarvestingThreshold();

		double getEnergy();
	
	protected :
		double harvestingThreshold;
		double energyPointRespawnLagMaxValue;

		double harvestingRate;
		double regrowRate;
	
};

#endif
