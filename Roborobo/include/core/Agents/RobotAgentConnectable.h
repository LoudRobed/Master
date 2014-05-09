/*
 *  RobotAgentConnectable.h
 *  roborobo
 *
 *  Created by Jean-Marc on 22/03/13.
 *		From work done by Berend Weel in a separate branch
 *
 */

#ifndef ROBOTAGENTCONNECTABLE_H
#define ROBOTAGENTCONNECTABLE_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Agents/RobotAgent.h"

#include "Utilities/SDL_gfxPrimitives.h"
#include "Utilities/SDL_gfxPrimitivesExtra.h"

#include "BehaviorControlArchitectures/BehaviorControlArchitecture.h"
#include "Observers/Observer.h"
#include "Observers/WorldObserver.h"
#include "WorldModels/RobotAgentWorldModel.h"

#include "WorldModels/RobotAgentWorldModel.h"
#include "World/World.h"
#include "World/RobotAgentWorldInterface.h"

// *** begin: add new includes here ***

#include "WorldModels/EvolvingRobotAgentWorldModel.h"
#include "WorldModels/EvolvingRobotAgentWorldModelDangerWorld.h"

#include "BehaviorControlArchitectures/PerceptronBehaviorControlArchitecture.h"

#include "Observers/Observer.h"
#include "Observers/AgentObserver.h"
#include "Agents/ConnectionMechanism.h"

#include "World/RobotAgentWorldInterfaceDangerWorld.h"


// *** end ***

class Organism;

class World;

class ConnectionMechanism;

class RobotAgentConnectable : public RobotAgent
{
	
	protected:
    SDL_Surface* _agentMask;
    Organism* _organism; // organism robot is part of
		int _connectToOthers;
		bool _connectionMechanismCustomized;
		ConnectionMechanism* _customConnectionMechanism;
	
		std::vector<RobotAgentConnectable*> *connected; // the neighbours the robot is connected to if in an organism
					
	public:
		//Initializes the variables
		RobotAgentConnectable( World *__world );
		~RobotAgentConnectable();

		void setConnectToOthers(int __connectToOthers);
		int getConnectToOthers();

		// Organism related functions
		void customizeConnectionMechanism(ConnectionMechanism* customConnectionMechanism);
		ConnectionMechanism* getConnectionMechanism();
		void setUpConnections();

		bool isOutOfBounds();
		void connectToRobot(RobotAgentConnectable* other);
		void letGoOfOrganism();
		void addNeighbour(RobotAgentConnectable* neighbour);
		void removeNeighbour(RobotAgentConnectable* neighbour);
		std::vector<RobotAgentConnectable*> *getConnected();

		void setOrganism(Organism* __organism);
		Organism *getOrganism();
		bool isPartOfOrganism();
		bool isPartOfSameOrganism(RobotAgentConnectable* other);

		double xReal_old;
		double yReal_old;
		Point2d oldPosition;
		double _lastAgentAbsoluteOrientation;

		static const int POSITIVE = 1;
		static const int NEUTRAL = 0;
		static const int NEGATIVE = -1;
};



#endif /* ROBOTAGENT_H */


