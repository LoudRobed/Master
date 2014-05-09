/*
 *  MedeaAggregationBattleAgentObserver.h
 *  Roborobo
 *
 *  imported from Jean-Marc on 15/12/09
 *  current dev: Nicolas on 1/4/2009
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */

#ifndef MEDEAAGGREGATIONBATTLEAGENTOBSERVER_H
#define MEDEAAGGREGATIONBATTLEAGENTOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/AgentObserver.h"

#include "mEDEA-aggregation/include/MedeaAggregationAgentWorldModel.h"
#include "mEDEA-aggregation/include/MedeaAggregationSharedData.h"
 
class MedeaAggregationBattleAgentObserver : public AgentObserver
{
	protected:
		MedeaAggregationAgentWorldModel	*_wm;

		void checkGenomeList();
		void pickRandomGenome();
		void randomElitismGenomeSelection();
		void tournamentGenomeSelection();
		void mutateWithBouncingBounds(float sigma);

		int nbMaxGenomeSelection ;

		int iterationUp;
		int iterationDown;

	public:
		MedeaAggregationBattleAgentObserver( RobotAgentWorldModel *__wm );
		~MedeaAggregationBattleAgentObserver();
				
		void reset();
		void step();

		void writeGenome(std::vector<double> genome, int senderId);
		void loadGenome ( std::vector<double> inGenome );

};

#endif
