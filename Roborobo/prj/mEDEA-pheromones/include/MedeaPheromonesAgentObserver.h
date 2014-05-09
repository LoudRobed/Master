/**
 * @file
 * @author Nicolas Bredeche <nicolas.bredeche@gmail.com>
 * 
 * History :
 *  - imported from medea-basic project on 16/6/2012
 *
 */

#ifndef MEDEAPHEROMONESAGENTOBSERVER_H
#define MEDEAPHEROMONESAGENTOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Observers/AgentObserver.h"
#include "mEDEA-pheromones/include/MedeaPheromonesAgentWorldModel.h"
#include "mEDEA-pheromones/include/MedeaPheromonesSharedData.h"


class MedeaPheromonesAgentObserver : public AgentObserver
{
	protected:
		MedeaPheromonesAgentWorldModel *_wm;

		void pickRandomGenome();
		void mutateWithBouncingBounds(float sigma);

	public:
		MedeaPheromonesAgentObserver(RobotAgentWorldModel *wm);
		~MedeaPheromonesAgentObserver();

		void reset();
		void step();

		void writeGenome(std::vector<double> genome, int senderId, float sigma);

};

#endif

