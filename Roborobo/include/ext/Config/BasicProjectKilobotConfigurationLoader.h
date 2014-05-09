/*
 * BasicProjectKilobotConfigurationLoader.h
 *
 * Created by nicolas 2012-08-01
 *
 */

#ifndef BASICPROJECTKILOBOTCONFIGURATIONLOADER_H
#define	BASICPROJECTKILOBOTCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class BasicProjectKilobotConfigurationLoader : public ConfigurationLoader
{
	public:
		BasicProjectKilobotConfigurationLoader();
		~BasicProjectKilobotConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotAgentWorldModel *make_RobotAgentWorldModel();
		AgentObserver *make_AgentObserver(RobotAgentWorldModel* wm) ;
		BehaviorControlArchitecture *make_BehaviorControlArchitecture(RobotAgentWorldModel* wm) ;
		RobotAgentWorldInterface *make_RobotAgentWorldInterface() ; // interface created once in constructor, returns a pointer
};

#endif
