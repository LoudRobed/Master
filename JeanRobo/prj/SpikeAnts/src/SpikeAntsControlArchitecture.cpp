/*
 *  SpikeAntsControlArchitecture.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 19/11/10 for Sylvain.
 *
 */

#include "SpikeAnts/include/SpikeAntsControlArchitecture.h"
// #include "RoboroboMain/roborobo.h"
#include "World/World.h"
#include "Utilities/Misc.h"
// #include "SpikeAnts/include/lif.h"

SpikeAntsControlArchitecture::SpikeAntsControlArchitecture( RobotAgentWorldModel *__wm ) //  : BehaviorControlArchitecture ( __wm )
{
	_wm = (SpikeAntsAgentWorldModel*)__wm;

	// nothing to do
	_wm->setRobotLED_status(true);
	_wm->setRobotLED_colorValues(0,0,0);
}

SpikeAntsControlArchitecture::~SpikeAntsControlArchitecture()
{
	// nothing to do.
}

void SpikeAntsControlArchitecture::reset()
{
	// nothing to do.
}

void SpikeAntsControlArchitecture::step()
{

	// * perform a basic obstacle avoidance behavior

	_wm->_desiredTranslationalValue =  + 1 - ( (double)gSensorRange - ((_wm->_sensors[2][5]+_wm->_sensors[3][5])/2) )  / (double)gSensorRange; 
	if (_wm->_desiredTranslationalValue > 0.9999)
	  _wm->_saAvoidCounter++;
	if ( _wm->_sensors[0][5] + _wm->_sensors[1][5] + _wm->_sensors[2][5] < _wm->_sensors[3][5] + _wm->_sensors[4][5] + _wm->_sensors[5][5] )
	  _wm->_desiredRotationalVelocity = +5;
	else if ( _wm->_sensors[3][5] + _wm->_sensors[4][5] + _wm->_sensors[5][5] < 3*gSensorRange ) 
	  _wm->_desiredRotationalVelocity = -5;
	else if ( _wm->_desiredRotationalVelocity > 0 ) 
	  _wm->_desiredRotationalVelocity--;
	else if ( _wm->_desiredRotationalVelocity < 0) 
	  _wm->_desiredRotationalVelocity++;
	else
	  _wm->_desiredRotationalVelocity = 0.01 - (double)(rand()%10)/10.*0.02;


	// * go to nest if observing
	if (_wm->_currentStatus == SpikeAntsAgentWorldModel::OBSERVE) {
	  Point2d posRobot(_wm->_xReal,_wm->_yReal);
	  Point2d posEnergyPoint = gEnergyPoints[0].getPosition();
	  // double distance = getEuclidianDistance(posRobot,posEnergyPoint);
	  double orientation = getAngleToTarget(posRobot, _wm->_agentAbsoluteOrientation, posEnergyPoint);
	  
	  if ((( _wm->_desiredRotationalVelocity < 0 ) && ( _wm->_desiredRotationalVelocity > -2.0)) || (( _wm->_desiredRotationalVelocity > 0 ) && ( _wm->_desiredRotationalVelocity < 2.0)))
		 _wm->_desiredRotationalVelocity = (orientation / 180.0)* 5.0;
	}
	// go to energy point if foraging
	else if (_wm->getCurrentStatus () == SpikeAntsAgentWorldModel::WORK) {
	  Point2d posRobot(_wm->_xReal,_wm->_yReal);
	  Point2d posEnergyPoint = gEnergyPoints[1].getPosition();
	  double distance = getEuclidianDistance(posRobot, posEnergyPoint);
	  double orientation = getAngleToTarget(posRobot, _wm->_agentAbsoluteOrientation, posEnergyPoint);

	  // If the robot is close to the energy point then its a forage success.
	  if ((distance < 10.*(double)gSensorRange) && (_wm->_saForageSuccess == 0)) {
		 _wm->_saForageSuccess = _wm->_saForageTimer;
	  }
	  if ((( _wm->_desiredRotationalVelocity < 0 ) && ( _wm->_desiredRotationalVelocity > -4.0)) || (( _wm->_desiredRotationalVelocity > 0 ) && ( _wm->_desiredRotationalVelocity < 4.0)))
		 _wm->_desiredRotationalVelocity = (orientation / 180.0)* 18.0; // *5.0
	}
	// go to nest and stop if sleeping/grooming
	else {
	  Point2d posRobot(_wm->_xReal,_wm->_yReal);
	  Point2d posEnergyPoint = gEnergyPoints[0].getPosition();
	  double distance = getEuclidianDistance(posRobot, posEnergyPoint);
	  double orientation = getAngleToTarget(posRobot, _wm->_agentAbsoluteOrientation, posEnergyPoint);
	  
	  if ((( _wm->_desiredRotationalVelocity < 0 ) && ( _wm->_desiredRotationalVelocity > -2.0)) || (( _wm->_desiredRotationalVelocity > 0 ) && ( _wm->_desiredRotationalVelocity < 2.0))) {
		 _wm->_desiredRotationalVelocity = (orientation / 180.0)* 5.0;
		 if (distance < (double)gSensorRange) 
			_wm->_desiredTranslationalValue = 0.;
	  }
	}


	// * track harvest zones and nest distance and orientation wrt. current agent.
	if ( gVerbose ) // only in verbose mode (press hotkey "v" during simulation)
	{
		if ( _wm->_agentId == gAgentIndexFocus ) // only focused agent (press hotkey "f" to spot it)
		{
			Point2d posRobot(_wm->_xReal,_wm->_yReal);
			Point2d posEnergyPoint = gEnergyPoints[0].getPosition();
			double distance = getEuclidianDistance(posRobot,posEnergyPoint);
			double orientation = getAngleToTarget(posRobot, _wm->_agentAbsoluteOrientation, posEnergyPoint);
			std::cout << "Agent("<< _wm->_agentId <<") to targets (target index, distance, orientation): (0 , " << distance << " , " << orientation << ")  ";

			posEnergyPoint = gEnergyPoints[1].getPosition();
			distance = getEuclidianDistance(posRobot,posEnergyPoint);
			orientation = getAngleToTarget(posRobot, _wm->_agentAbsoluteOrientation, posEnergyPoint);
			std::cout << "(1 , " << distance << " , " << orientation << ")  ";

			posEnergyPoint = gEnergyPoints[2].getPosition();
			distance = getEuclidianDistance(posRobot,posEnergyPoint);
			orientation = getAngleToTarget(posRobot, _wm->_agentAbsoluteOrientation, posEnergyPoint);
			std::cout << "(2 , " << distance << " , " << orientation << ")." << std::endl;
		}
	}
}
