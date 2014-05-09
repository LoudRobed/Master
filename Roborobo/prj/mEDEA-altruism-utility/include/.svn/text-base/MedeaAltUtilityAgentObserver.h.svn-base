/*
 *  MedeaAltUtilityAgentObserver.h
 *  Roborobo
 *
 *  imported from Jean-Marc on 15/12/09
 *  current dev: Nicolas on 1/4/2009
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */

#ifndef MEDEAALTUTILITYAGENTOBSERVER_H
#define MEDEAALTUTILITYAGENTOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/AgentObserver.h"

#include "mEDEA-altruism-utility/include/MedeaAltUtilityAgentWorldModel.h"

#include "mEDEA-altruism-utility/include/MedeaAltUtilitySharedData.h"
 
class MedeaAltUtilityAgentObserver : public AgentObserver
{
	protected:
		MedeaAltUtilityAgentWorldModel	*_wm;

		void pickRandomGenome();
		void mutateWithBouncingBounds(float sigma);

	public:
		MedeaAltUtilityAgentObserver( RobotAgentWorldModel *__wm );
		~MedeaAltUtilityAgentObserver();
				
		void reset();
		void step();

		void writeGenome(std::vector<double> genome, int senderId, float sigma);

};

#endif
