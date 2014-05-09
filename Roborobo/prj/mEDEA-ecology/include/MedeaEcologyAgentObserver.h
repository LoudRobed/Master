/**
 * @file
 * @author Nicolas Bredeche <nicolas.bredeche@gmail.com>
 * 
 * History :
 *  - imported from medea-basic project on 16/6/2012
 *
 */


#ifndef MEDEAECOLOGYAGENTOBSERVER_H
#define MEDEAECOLOGYAGENTOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Observers/AgentObserver.h"
#include "mEDEA-ecology/include/MedeaEcologyAgentWorldModel.h"
#include "mEDEA-ecology/include/MedeaEcologySharedData.h"


class MedeaEcologyAgentObserver : public AgentObserver
{
	protected:
		MedeaEcologyAgentWorldModel *_wm;

		void pickRandomGenome();
		void mutateWithBouncingBounds(float sigma);

	public:
		MedeaEcologyAgentObserver(RobotAgentWorldModel *wm);
		~MedeaEcologyAgentObserver();

		void reset();
		void step();

		void writeGenome(std::vector<double> genome, int senderId, float sigma);

};

#endif

