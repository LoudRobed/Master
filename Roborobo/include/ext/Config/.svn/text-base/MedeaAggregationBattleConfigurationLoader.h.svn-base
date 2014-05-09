/*
 * MedeaAltruismConfigurationLoader.h
 *
 *  created by Jean-Marc on 19/04/2013
 *
 */

#ifndef MEDEAAGGREGATIONBATTLECONFIGURATIONLOADER_H
#define MEDEAAGGREGATIONBATTLECONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"


class MedeaAggregationBattleConfigurationLoader : public ConfigurationLoader
{
	private:

	public:
		MedeaAggregationBattleConfigurationLoader();
		~MedeaAggregationBattleConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotAgentWorldModel *make_RobotAgentWorldModel();
		AgentObserver *make_AgentObserver(RobotAgentWorldModel* wm) ;
		BehaviorControlArchitecture *make_BehaviorControlArchitecture(RobotAgentWorldModel* wm) ;
		RobotAgentWorldInterface *make_RobotAgentWorldInterface() ; // interface created once in constructor, returns a pointer
};



#endif
