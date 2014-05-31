/*
 * MedeaAltruismBattleConfigurationLoader.h
 *
 * 	Jean-Marc on 27/02/2013
 *
 */

#ifndef MEDEAALTRUISMBATTLECONFIGURATIONLOADER_H
#define MEDEAALTRUISMBATTLECONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"


class MedeaAltruismBattleConfigurationLoader : public ConfigurationLoader
{
	private :

	public:
		MedeaAltruismBattleConfigurationLoader();
		~MedeaAltruismBattleConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotAgentWorldModel *make_RobotAgentWorldModel();
		AgentObserver *make_AgentObserver(RobotAgentWorldModel* wm) ;
		BehaviorControlArchitecture *make_BehaviorControlArchitecture(RobotAgentWorldModel* wm) ;
		RobotAgentWorldInterface *make_RobotAgentWorldInterface() ; // interface created once in constructor, returns a pointer
};



#endif
