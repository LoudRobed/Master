/*
 *  KilobotBasicControlArchitecture.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 27/05/10.
 *
 */

#include "BasicProject-Kilobot/include/KilobotBasicProjectControlArchitecture.h"

KilobotBasicControlArchitecture::KilobotBasicControlArchitecture( RobotAgentWorldModel *__wm ) : BehaviorControlArchitecture ( __wm )
{
	// nothing to do
}

KilobotBasicControlArchitecture::~KilobotBasicControlArchitecture()
{
	// nothing to do.
}

void KilobotBasicControlArchitecture::reset()
{
	// nothing to do.
}

void KilobotBasicControlArchitecture::step()
{
	// a basic obstacle avoidance behavior

    kilobot_set_motor(0,0);
    int message[3] = kilobot_get_message();
    
    
    //_wm->_desiredTranslationalValue = _wm->_desiredTranslationalValue * gMaxTranslationalSpeed;
    //_wm->_desiredRotationalVelocity = _wm->_desiredRotationalVelocity * gMaxRotationalSpeed;



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
