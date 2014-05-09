/*
 *  GripperConnectionMechanism.h
 *  roborobo
 *
 *  Created by Jean-Marc on 09/04/13
 *
 */

#ifndef GRIPPERCONNECTIONMECHANISM_H
#define GRIPPERCONNECTIONMECHANISM_H

#include "Agents/ConnectionMechanism.h"

class GripperConnectionMechanism: public ConnectionMechanism
{
	public:
		GripperConnectionMechanism(RobotAgentConnectable* agent);
		~GripperConnectionMechanism();
		void setUpConnections();

		void setArmState (int state);
		int getArmState ();
		int getAttachedTo();

		static const int LOW = 0;
		static const int HIGH = 1;
	
	protected:
		int armState;
		int attachedTo;


};

#endif
