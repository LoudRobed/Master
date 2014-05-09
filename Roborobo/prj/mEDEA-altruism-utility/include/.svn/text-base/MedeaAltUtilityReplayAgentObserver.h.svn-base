/*
 *  MedeaAltUtilityReplayAgentObserver.h
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

#include "mEDEA-altruism-utility/include/MedeaAltUtilityAgentWorldModel.h"

#include "mEDEA-altruism-utility/include/MedeaAltUtilitySharedData.h"
#include "Utilities/LogManager.h"

class MedeaAltUtilityReplayAgentObserver : public AgentObserver
{
	protected:
		MedeaAltUtilityAgentWorldModel	*_wm;

		std::vector<double> _currentGenome;

	public:
		MedeaAltUtilityReplayAgentObserver( RobotAgentWorldModel *__wm );
		~MedeaAltUtilityReplayAgentObserver();

		void loadGenome(std::vector<double> inGenome);
				
		void reset();
		void step();
};

#endif
