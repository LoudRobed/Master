/*
 *  AggregationBasicWorldObserver.h
 *  roborobo-online
 *
 *  Created by Jean-Marc on 07/04/2013
 *
 */



#ifndef AGGREGATIONBASICWORLDOBSERVER_H
#define AGGREGATIONBASICWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/WorldObserver.h"

class World;

class AggregationBasicWorldObserver : public WorldObserver
{
	protected:
		std::string agentPositiveMaskImageFilename;
		std::string agentNegativeMaskImageFilename;
		SDL_Surface *agentPositiveMaskImage;	// mask used for showing that an agent wants to connect
		SDL_Surface *agentNegativeMaskImage;	// mask used for showing that an agent wants to connect
		
	public:
		AggregationBasicWorldObserver( World *__world );
		~AggregationBasicWorldObserver();
				
		void reset();
		void step();
		
};

#endif

