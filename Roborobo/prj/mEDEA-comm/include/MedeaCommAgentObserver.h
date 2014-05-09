/*
 *  MedeaCommAgentObserver.h
 *  Roborobo
 *
 *  imported from Jean-Marc on 15/12/09
 *  current dev: Nicolas on 1/4/2009
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */

#ifndef MEDEACOMMAGENTOBSERVER_H
#define MEDEACOMMAGENTOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/AgentObserver.h"

#include "mEDEA-comm/include/MedeaCommAgentWorldModel.h"

#include "mEDEA-comm/include/MedeaCommSharedData.h"
 
class MedeaCommAgentObserver : public AgentObserver
{
	protected:
		MedeaCommAgentWorldModel	*_wm;

		void checkGenomeList();
		void pickRandomGenome();
		void randomElitismGenomeSelection();
		void tournamentGenomeSelection();
		void mutateWithBouncingBounds(float sigma);

		int nbMaxGenomeSelection ;

	public:
		MedeaCommAgentObserver( RobotAgentWorldModel *__wm );
		~MedeaCommAgentObserver();
				
		void reset();
		void step();

		void writeGenome(std::vector<double> genome, int senderId, float sigma);

		double getCommunication();

};

#endif
