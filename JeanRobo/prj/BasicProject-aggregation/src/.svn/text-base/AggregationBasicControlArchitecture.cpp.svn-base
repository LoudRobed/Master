/*
 *  AggregationBasicControlArchitecture.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 27/05/10.
 *
 */

#include "BasicProject-aggregation/include/AggregationBasicControlArchitecture.h"
#include "Agents/RobotAgentConnectable.h"

AggregationBasicControlArchitecture::AggregationBasicControlArchitecture( RobotAgentWorldModel *__wm ) : BehaviorControlArchitecture ( __wm )
{
	//nothing to do
	_firstStep = true;
}

AggregationBasicControlArchitecture::~AggregationBasicControlArchitecture()
{
	// nothing to do.
}

void AggregationBasicControlArchitecture::reset()
{
	// nothing to do.
}

void AggregationBasicControlArchitecture::step()
{
	// always go for connection with other robots
	if (_firstStep == true)
	{
		RobotAgentConnectable* agent = dynamic_cast<RobotAgentConnectable*>(gWorld->getAgent(_wm->_agentId));
		if (agent == 0)
		{
			std::cerr << "With Aggregation Basic project, RobotAgentConnectable should be used" << std::endl;
			exit(1);
		}
		connection = new GripperConnectionMechanism(agent);

		/*
		if (_wm->_agentId == 0)
		{
			connection->setArmState(GripperConnectionMechanism::LOW);
		}
		else
		{
			connection->setArmState(GripperConnectionMechanism::HIGH);
		}
		*/

		/*
		if ((float)rand()/(float)RAND_MAX > 0.8)
		{
			connection->setArmState(GripperConnectionMechanism::LOW);
		}
		else
		{
			connection->setArmState(GripperConnectionMechanism::HIGH);
		}
		*/
		//agent->setConnectToOthers(RobotAgentConnectable::POSITIVE);
		_firstStep = false;
		connection->setArmState(GripperConnectionMechanism::LOW);
	}
	
	/*
	if (gWorld->getIterations() % 400 == 0)
	{
		if ((float)rand()/(float)RAND_MAX > 0.8)
		{
			connection->setArmState(GripperConnectionMechanism::HIGH);
		}
		if (_wm->_agentId == 1)
		{
			connection->setArmState(GripperConnectionMechanism::HIGH);
		}
	}
	*/

	/*
	if ((_wm->_agentId == 1) && (gWorld->getIterations() == 400))
	{
		//RobotAgentConnectable* agent = dynamic_cast<RobotAgentConnectable*>(gWorld->getAgent(_wm->_agentId));
		//agent->setConnectToOthers(RobotAgentConnectable::NEGATIVE);
		std::cout << "switch" << std::endl;
		connection->setArmState(GripperConnectionMechanism::LOW);
	}
	*/

	/*
	if (_wm->_agentId == 0)
	{
		_wm->_desiredTranslationalValue = 1.0 ; 
		if (abs(_wm->_agentAbsoluteOrientation-180) < 1) 
		{
			_wm->_desiredRotationalVelocity = -0.0;
		}
		else
		{
			_wm->_desiredRotationalVelocity = -0.5;
		}
	}
	
	if (_wm->_agentId == 1)
	{
		_wm->_desiredTranslationalValue = 1.0 ; 
		if (abs(_wm->_agentAbsoluteOrientation) < 1)
		{
			_wm->_desiredRotationalVelocity = -0.0;
		}
		else
		{
			_wm->_desiredRotationalVelocity = 0.5;
		}
	}
	*/

	/*
	if ((_wm->_agentId == 1) || (_wm->_agentId == 0))
	{
		_wm->_desiredTranslationalValue = 1.0; 
		_wm->_desiredRotationalVelocity = 0.0;
	}
	
	if (_wm->_agentId == 2)
	{
		_wm->_desiredTranslationalValue = 0.0; 
		_wm->_desiredRotationalVelocity = 0.0;
	}
	*/

	// a basic obstacle avoidance behavior
	_wm->_desiredTranslationalValue =  + 1 - ( (double)gSensorRange - ((_wm->_sensors[2][5]+_wm->_sensors[3][5])/2) )  / (double)gSensorRange; 
	if ( _wm->_sensors[0][5] + _wm->_sensors[1][5] + _wm->_sensors[2][5] < _wm->_sensors[3][5] + _wm->_sensors[4][5] + _wm->_sensors[5][5] ) 
		_wm->_desiredRotationalVelocity = +5;
	else
		if ( _wm->_sensors[3][5] + _wm->_sensors[4][5] + _wm->_sensors[5][5] < 3*gSensorRange ) 
			_wm->_desiredRotationalVelocity = -5;
		else
			if ( _wm->_desiredRotationalVelocity > 0 ) 
				_wm->_desiredRotationalVelocity--;
			else
				if ( _wm->_desiredRotationalVelocity < 0) 
					_wm->_desiredRotationalVelocity++;
				else
					_wm->_desiredRotationalVelocity = 0.01 - (double)(rand()%10)/10.*0.02;


}

