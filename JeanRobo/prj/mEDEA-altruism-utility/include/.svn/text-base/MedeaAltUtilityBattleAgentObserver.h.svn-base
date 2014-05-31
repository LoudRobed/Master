/*
 *  MedeaAltUtilityBattleAgentObserver.h
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

#include "mEDEA-altruism-utility/include/MedeaAltUtilityAgentWorldModel.h"

#include "mEDEA-altruism-utility/include/MedeaAltUtilitySharedData.h"

class MedeaAltUtilityBattleAgentObserver : public AgentObserver
{
	protected:
		MedeaAltUtilityAgentWorldModel	*_wm;

		std::map<int, std::vector<double> > _genomesList;
		std::map<int, float > _sigmaList;
		std::vector<double> _currentGenome;
		float _currentSigma;

		double _minValue;
		double _maxValue;
		int _nbGene;
		int _nbLayer;
		int _nbHiddenNeurons;

		int _evaluationCount;
		int _generationCount;
		int _iterationCount;
		bool _synchronization;

		void pickRandomGenome();
		void logStatus();

		int _side;
		float _key;

	public:
		MedeaAltUtilityBattleAgentObserver( RobotAgentWorldModel *__wm );
		~MedeaAltUtilityBattleAgentObserver();
				
		void reset();
		void step();

		void writeGenome(std::vector<double> genome, int senderId);
		void loadGenome ( std::vector<double> inGenome );

		int getSide();
};

#endif
