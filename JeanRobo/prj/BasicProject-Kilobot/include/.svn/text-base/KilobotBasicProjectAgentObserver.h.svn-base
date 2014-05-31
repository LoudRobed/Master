/*
 *  KilobotBasicAgentObserver.h
 *  roborobo-online
 *
 *  Created by Nicolas on 27/05/10.
 *
 */

 
#ifndef KILOBOTBASICAGENTOBSERVER_H
#define KILOBOTBASICAGENTOBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "BasicProject-Kilobot/include/KilobotBasicProjectAgentWorldModel.h"

#include "Observers/AgentObserver.h"

class KilobotBasicAgentObserver : public AgentObserver
{
	protected:
		KilobotBasicAgentWorldModel	*_wm;

	public:
		//Initializes the variables
		KilobotBasicAgentObserver( );
		KilobotBasicAgentObserver( RobotAgentWorldModel *__wm );
		~KilobotBasicAgentObserver();
				
		void reset();
		void step();
		
};


#endif

