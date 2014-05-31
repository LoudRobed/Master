/*
 *  World.h
 *  roborobo
 *
 *  Created by Nicolas on 16/01/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef WORLD_H
#define WORLD_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Agents/RobotAgent.h"

#include "Utilities/Misc.h"

#include "Observers/WorldObserver.h"

class RobotAgent;

class World
{
	protected:

		std::vector<RobotAgent*> agents;//[gNbOfAgents];

		//RobotAgent *agents[gNbOfAgents];
		//bool agentRegister[gNbOfAgents]; // track agents which are registered (ie. drawn) in the foreground image (for agent-agent collision)
		
		int _iterations;

		//True if there is a variation in the number of agent
		bool _agentsVariation;
    bool _initializeAgents;
    bool _setUpConnections;
    bool _initializeEnergyPoints;
		
		WorldObserver *_worldObserver;
		
	public:		

		World();
		~World();

		bool loadFiles();
		//bool loadProperties( std::string __propertiesFilename );

		void initWorld();
		void resetWorld();
		void updateWorld(Uint8 *__keyboardStates = NULL);
		
		RobotAgent* getAgent( int __agentIndex );

		//delete an agent from the simulator. No other functions to call
		void deleteAgent (int __agentIndex );
		//add an agent in the simulator. No other functions to call
		void addAgent(RobotAgent *agentToAdd);
		
		void deleteEnergyPoint(int __objectIndex );
		void addEnergyPoint(EnergyPoint objectToAdd);
	
		void deleteObject(int __objectIndex );
		void addObject(InanimateObject* objectToAdd);
	
		int getIterations();
		WorldObserver* getWorldObserver();
		int getNbOfAgent();

    void setInitializeAgents(bool initAgents);
    bool getInitiliazeAgents();
    
    void setSetUpConnections(bool setUpConnections);
    bool getSetUpConnections();
};



#endif // WORLD_H

