#include <iostream>

#include "SDL_collide.h"

#include "connectionMechanism/GripperConnectionMechanism.h"

GripperConnectionMechanism::GripperConnectionMechanism(RobotAgentConnectable* agent):
ConnectionMechanism(agent)
{
	armState = GripperConnectionMechanism::LOW;
	attachedTo = -1;
}

void GripperConnectionMechanism::setArmState (int state)
{
	if (state == GripperConnectionMechanism::LOW || state == GripperConnectionMechanism::HIGH )
	{
		armState = state;
	}
	else
	{
		std::cerr << "Try to set the state of the arm to something else than high or low" << std::endl;
		exit(1);
	}
}

int GripperConnectionMechanism::getArmState ()
{
	return armState;
}

int GripperConnectionMechanism::getAttachedTo ()
{
	return attachedTo;
}

void GripperConnectionMechanism::setUpConnections()
{
	//utiliser _agent à la place de _agent
	int nAgents = _agent->getWorldModel()->_world->getNbOfAgent();
	int id = _agent->getWorldModel()->_agentId;

	if (_agent->isPartOfOrganism()) 
	{
		if ((armState == GripperConnectionMechanism::HIGH) && (attachedTo != -1))
		{
			_agent->letGoOfOrganism();
			attachedTo = -1;
		}
		if (_agent->getConnected()->empty()) 
		{
			_agent->letGoOfOrganism();
			attachedTo = -1;
		}
	}

	for (int i = 0; i < nAgents; i++) 
	{
		RobotAgentConnectable* other = dynamic_cast<RobotAgentConnectable*>(_agent->getWorldModel()->_world->getAgent(i));
		if(other == 0)
		{
			std::cerr << "Agent" << i << "isn't of type RobotAgentConnectable" << std::endl;
			std::cerr << "Every  agents in the simulation should be of type RobotAgentConnectable" << std::endl;
			exit(1);
		}
		RobotAgentWorldModel *otherWM = (RobotAgentWorldModel*) other->getWorldModel();
		int otherId = otherWM->_agentId;

		if (otherId != id) 
		{
			// If they're out of bounds, ignore.
			// This happens at the start of the simulation sometimes and can lead
			// to false positives
			if (_agent->isOutOfBounds() || other->isOutOfBounds()) 
			{
				return;
			}

			double x1, y1, x2, y2, orientation;
			x1 = _agent->getWorldModel()->_xReal;
			y1 = _agent->getWorldModel()->_yReal;
			orientation = _agent->getWorldModel()->_agentAbsoluteOrientation;
			x2 = other->getWorldModel()->_xReal;
			y2 = other->getWorldModel()->_yReal;

			//compute the orientation of the closest energy point ( in degree between 0 and 360 )
			double angleToOther = (atan2(y2-y1,x2-x1)/M_PI)*180.0;
			angleToOther += 360.0 ;
			angleToOther = computeModulo(angleToOther,360.0);
			if ( angleToOther > 180 ) // force btw -180 and 180
				angleToOther -= 360.0;

			//compute the angle between the actual orientation of the robot and the orientation of the closest energy point ( in degree between -180 and 180 )
			double diffAngleToOther = angleToOther - orientation ;
			if ( diffAngleToOther < -180.0 )
			{
				diffAngleToOther += 360.0 ; 
			}
			if ( diffAngleToOther > 180.0 )
			{
				diffAngleToOther -= 360.0 ;
			}


			// Are they within range?
			if ((armState == GripperConnectionMechanism::LOW)  && (attachedTo == -1) && (abs(diffAngleToOther) < 10))
			{
				if (SDL_CollideBoundingCircle(_agent->getAgentMask(), x1, y1, other->getAgentMask(), x2, y2, gConnectionGap)) 
				{
					_agent->connectToRobot(other);
					attachedTo = otherId;
				}
			}
		}
	}
}
