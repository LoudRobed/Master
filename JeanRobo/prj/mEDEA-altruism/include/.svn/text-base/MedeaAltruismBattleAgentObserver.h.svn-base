/*
 *  MedeaAltruismBattleAgentObserver.h
 *  Roborobo
 *
 *  Created by Jean-Marc on 15/12/09
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */

#ifndef MEDEA_ALTRUISM_BATTLE_AGENT_OBSERVER_H
#define MEDEA_ALTRUISM_BATTLE_AGENT_OBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/AgentObserver.h"

#include "mEDEA-altruism/include/MedeaAltruismAgentWorldModel.h"

#include "mEDEA-altruism/include/MedeaAltruismSharedData.h"

class MedeaAltruismBattleAgentObserver : public AgentObserver
{
	protected:
		MedeaAltruismAgentWorldModel	*_wm;

		void checkGenomeList();
		void pickRandomGenome();
		void randomElitismGenomeSelection();
		void tournamentGenomeSelection();

		int _side;
		int nbMaxGenomeSelection ;

	public:
		MedeaAltruismBattleAgentObserver( RobotAgentWorldModel *__wm );
		~MedeaAltruismBattleAgentObserver();
				
		void reset();
		void step();

		void writeGenome(std::vector<double> genome, int senderId);
		void loadGenome ( std::vector<double> inGenome );

		int getSide();
};

#endif
