/*
 *  MedeaAltruismReplayPartialEvoAgentObserver.h
 *  Roborobo
 *
 *  Created by Jean-Marc on 20/04/10
 *  moved in altruism by Jean-Marc on 17/09/2010
 *  moved in partial evo by Jean-Marc on 08/12/2010
 *
 */

#ifndef MEDEA_ALTRUISM_REPLAY_PARTIAL_EVO_AGENT_OBSERVER_H
#define MEDEA_ALTRUISM_REPLAY_PARTIAL_EVO_AGENT_OBSERVER_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/AgentObserver.h"

#include "mEDEA-altruism/include/MedeaAltruismReplayPartialEvoAgentWorldModel.h"

#include "mEDEA-altruism/include/MedeaAltruismSharedData.h"
#include "Utilities/LogManager.h"

class MedeaAltruismReplayPartialEvoAgentObserver : public AgentObserver
{
	protected:
		MedeaAltruismReplayPartialEvoAgentWorldModel	*_wm;

		std::vector<double> _currentGenome;
		void pickRandomGenome();
		void mutateWithBouncingBounds(float sigma);

	public:
		MedeaAltruismReplayPartialEvoAgentObserver( RobotAgentWorldModel *__wm );
		~MedeaAltruismReplayPartialEvoAgentObserver();

		void loadGenome(std::vector<double> inGenome);
				
		void reset();
		void step();
		void writeGenome(std::vector<double> genome, int senderId, float sigma);
};

#endif
