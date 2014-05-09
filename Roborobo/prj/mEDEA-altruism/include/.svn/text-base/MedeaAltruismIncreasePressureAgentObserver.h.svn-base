/*
 *  MedeaAltruismIncreasePressureAgentObserver.h
 *  Roborobo
 *
 *  imported from Jean-Marc on 15/12/09
 *  current dev: Nicolas on 1/4/2009
 *  moved in altruism by Jean-Marc on 17/09/2010
 *  modification for increase pressure : jean-marc 21/08/2012
 *
 */

#ifndef MEDEAALTRUISMINCREASEPRESSUREAGENTOBSERVER_H
#define MEDEAALTRUISMINCREASEPRESSUREAGENTOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/AgentObserver.h"

#include "mEDEA-altruism/include/MedeaAltruismAgentWorldModel.h"

#include "mEDEA-altruism/include/MedeaAltruismSharedData.h"
 
class MedeaAltruismIncreasePressureAgentObserver : public AgentObserver
{
	protected:
		MedeaAltruismAgentWorldModel	*_wm;

		void checkGenomeList();
		void pickRandomGenome();
		void randomElitismGenomeSelection();
		void tournamentGenomeSelection();
		void mutateWithBouncingBounds(float sigma);

		int nbMaxGenomeSelection ;

	public:
		MedeaAltruismIncreasePressureAgentObserver( RobotAgentWorldModel *__wm );
		~MedeaAltruismIncreasePressureAgentObserver();

		void loadGenome(std::vector<double> inGenome);
				
		void reset();
		void step();

		void writeGenome(std::vector<double> genome, int senderId, float sigma);

};

#endif
