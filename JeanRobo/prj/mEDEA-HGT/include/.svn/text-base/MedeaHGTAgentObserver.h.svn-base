/**
 * @file
 * @author Leo Cazenille <leo.cazenille@gmail.com>
 * TODO : Add formal description
 * History : 
 *
 *
 */

#ifndef MEDEAHGTAGENTOBSERVER_H
#define MEDEAHGTAGENTOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Observers/AgentObserver.h"
#include "mEDEA-HGT/include/MedeaHGTAgentWorldModel.h"
#include "mEDEA-HGT/include/MedeaHGTSharedData.h"


class MedeaHGTAgentObserver : public AgentObserver
{
	protected:
		MedeaHGTAgentWorldModel *_wm;

		void SimpleGenomeSpreading(MedeaHGTAgentObserver* targetAgentObserver);
		void HGTGenomeSpreading(MedeaHGTAgentObserver* targetAgentObserver);

		void pickRandomGenome();
		void mutateWithBouncingBounds(float sigma);

	public:
		MedeaHGTAgentObserver(RobotAgentWorldModel *wm);
		~MedeaHGTAgentObserver();

		void reset();
		void step();

		void writeGenome(std::vector<double> genome, int senderId, float sigma);

};

#endif

