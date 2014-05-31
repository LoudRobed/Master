/*
 *  MedeaAltruismReplayAgentObserver.h
 *  Roborobo
 *
 *  Created by Jean-Marc on 20/04/10
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */

#ifndef MEDEA_ALTRUISM_REPLAY_AGENT_OBSERVER_H
#define MEDEA_ALTRUISM_REPLAY_AGENT_OBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/AgentObserver.h"

#include "mEDEA-altruism/include/MedeaAltruismAgentWorldModel.h"

#include "mEDEA-altruism/include/MedeaAltruismSharedData.h"
#include "Utilities/LogManager.h"

class MedeaAltruismReplayAgentObserver : public AgentObserver
{
	protected:
		MedeaAltruismAgentWorldModel	*_wm;

		std::vector<double> _currentGenome;

		int nbMaxGenomeSelection ;

	public:
		MedeaAltruismReplayAgentObserver( RobotAgentWorldModel *__wm );
		~MedeaAltruismReplayAgentObserver();

		void loadGenome(std::vector<double> inGenome);
				
		void reset();
		void step();
};

#endif
