#include "connectionMechanism/GripperWorldInterface.h"
#include "connectionMechanism/GripperConnectionMechanism.h"


void GripperWorldInterface::prepareInternalDynamics()
{
}

void GripperWorldInterface::applyInternalDynamics( RobotAgentWorldModel *__wm )
{
	// * update internal data
	RobotAgentConnectable* agent= dynamic_cast<RobotAgentConnectable*>(gWorld->getAgent(__wm->_agentId));
	if (agent == 0)
	{
		std::cerr << "Should use RobotAgentConnectable with Gripper world interface" << std::endl;
		exit(1);
	}

	GripperConnectionMechanism* connection = dynamic_cast<GripperConnectionMechanism*>(agent->getConnectionMechanism());
	if (connection == 0)//if the connection isn't a gripper, do everything normal
	{
		__wm->_agentAbsoluteLinearSpeed = __wm->_actualTranslationalValue;
		__wm->_agentAbsoluteOrientation += __wm->_actualRotationalVelocity;


		if ( __wm->_agentAbsoluteOrientation <= -180.0 )
		{
			__wm->_agentAbsoluteOrientation = __wm->_agentAbsoluteOrientation + 360.0;
		}
		else
		{
			if ( __wm->_agentAbsoluteOrientation > 180.0 )
			{
				__wm->_agentAbsoluteOrientation = __wm->_agentAbsoluteOrientation - 360.0;
			}
		}
	}
	else//if the connection is a gripper, check if the gripper is used or not
	{
		if(connection->getAttachedTo() == -1) //if the gripper isn't attached, everything is normal
		{
			__wm->_agentAbsoluteLinearSpeed = __wm->_actualTranslationalValue;
			__wm->_agentAbsoluteOrientation += __wm->_actualRotationalVelocity;


			if ( __wm->_agentAbsoluteOrientation <= -180.0 )
			{
				__wm->_agentAbsoluteOrientation = __wm->_agentAbsoluteOrientation + 360.0;
			}
			else
			{
				if ( __wm->_agentAbsoluteOrientation > 180.0 )
				{
					__wm->_agentAbsoluteOrientation = __wm->_agentAbsoluteOrientation - 360.0;
				}
			}
		}
		else//if the gripper is attached to something, the robot doesn't turn
		{
			__wm->_agentAbsoluteLinearSpeed = __wm->_actualTranslationalValue;
		}
	}

}
