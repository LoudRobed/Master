/*
 *  ConnectionMechanism.h
 *  roborobo
 *
 *  Created by Jean-Marc on 09/04/13
 *
 */

#ifndef CONNECTIONMECHANISM_H
#define CONNECTIONMECHANISM_H

#include "Agents/RobotAgentConnectable.h"

class RobotAgentConnectable;

class ConnectionMechanism
{
	public:
		ConnectionMechanism(RobotAgentConnectable* agent);
		~ConnectionMechanism();

		virtual void setUpConnections()= 0;

	protected:
		RobotAgentConnectable* _agent;
};
#endif
