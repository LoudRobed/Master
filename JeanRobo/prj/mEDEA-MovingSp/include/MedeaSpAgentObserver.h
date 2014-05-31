/*
 *  MedeaSpAgentObserver.h
 *  Roborobo
 *
 *  imported from Jean-Marc on 15/12/09
 *  current dev: Nicolas on 1/4/2009
 *
 */

#ifndef MEDEAAGENTOBSERVER_H
#define MEDEAAGENTOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/AgentObserver.h"

#include "mEDEA-MovingSp/include/MedeaSpAgentWorldModel.h"

#include "mEDEA-MovingSp/include/MedeaSpSharedData.h"
 
class MedeaSpAgentObserver : public AgentObserver
{
	protected:
		MedeaSpAgentWorldModel	*_wm;
		
// 		int _fatherId; 				//use to store the id of the robot there the current used genome comes from
		void pickRandomGenome();
		void mutateWithBouncingBounds(float sigma);
	public:
		MedeaSpAgentObserver( RobotAgentWorldModel *__wm );
		~MedeaSpAgentObserver();
				
		void reset();
		void step();

		void writeGenome(std::vector<double> genome, int senderId, float sigma);
		void checkGenomeList();

// 		void setFatherId(int fatherId);
// 		void getFatherId();
};

#endif
