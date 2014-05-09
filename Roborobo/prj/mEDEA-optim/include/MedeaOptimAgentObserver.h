/*
 *  MedeaOptimAgentObserver.h
 *
 *  current dev: Nicolas on 19/1/2011
 *
 */

#ifndef MedeaOptimAGENTOBSERVER_H
#define MedeaOptimAGENTOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/AgentObserver.h"

#include "mEDEA-optim/include/MedeaOptimAgentWorldModel.h"

#include "mEDEA-optim/include/MedeaOptimSharedData.h"
 
class MedeaOptimAgentObserver : public AgentObserver
{
	protected:
		MedeaOptimAgentWorldModel	*_wm;

		void pickRandomGenome();
		
		void performGenomeSelectionWithTournament( int tournamentSize );
		void performGenomeSelectionWithPGTA_geneBased();
		void performGenomeSelectionWithPGTA_genomeBased();

		void mutateWithBouncingBounds(float sigma);

	public:
		MedeaOptimAgentObserver( RobotAgentWorldModel *__wm );
		~MedeaOptimAgentObserver();
				
		void reset();
		void step();

		void writeGenome(std::vector<double> genome, int senderId, float sigma, double fitness);

};

#endif
