/*
 * MedeaAltruismConfigurationLoader.h
 *
 *  created by Jean-Marc on 19/04/2013
 *
 */

#ifndef MEDEAAGGREGATIONCONFIGURATIONLOADER_H
#define MEDEAAGGREGATIONCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"


class MedeaAggregationConfigurationLoader : public ConfigurationLoader
{
	private:

	public:
		MedeaAggregationConfigurationLoader();
		~MedeaAggregationConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotAgentWorldModel *make_RobotAgentWorldModel();
		AgentObserver *make_AgentObserver(RobotAgentWorldModel* wm) ;
		BehaviorControlArchitecture *make_BehaviorControlArchitecture(RobotAgentWorldModel* wm) ;
		RobotAgentWorldInterface *make_RobotAgentWorldInterface() ; // interface created once in constructor, returns a pointer
};



#endif
