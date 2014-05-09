/*
 * BasicProjectAggregationConfigurationLoader.h
 *
 * Created by Jean-Marc 2012-04-06
 *
 */

#ifndef BASICPROJECTAGGREGATIONCONFIGURATIONLOADER_H
#define	BASICPROJECTAGGREGATIONCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class BasicProjectAggregationConfigurationLoader : public ConfigurationLoader
{
	public:
		BasicProjectAggregationConfigurationLoader();
		~BasicProjectAggregationConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotAgentWorldModel *make_RobotAgentWorldModel();
		AgentObserver *make_AgentObserver(RobotAgentWorldModel* wm) ;
		BehaviorControlArchitecture *make_BehaviorControlArchitecture(RobotAgentWorldModel* wm) ;
		RobotAgentWorldInterface *make_RobotAgentWorldInterface() ; // interface created once in constructor, returns a pointer
};

#endif
