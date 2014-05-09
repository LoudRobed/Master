#if defined PRJ_BASICPROJECTKILOBOT || !defined MODULAR

#include "Config/BasicProjectKilobotConfigurationLoader.h"

#include "BasicProject-Kilobot/include/KilobotBasicProjectWorldObserver.h"
#include "BasicProject-Kilobot/include/KilobotBasicProjectAgentWorldModel.h"
#include "BasicProject-Kilobot/include/KilobotBasicProjectAgentObserver.h"
#include "BasicProject-Kilobot/include/KilobotBasicProjectControlArchitecture.h"

#include "World/RobotAgentWorldInterface.h"

BasicProjectKilobotConfigurationLoader::BasicProjectKilobotConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
	_AgentWorldInterface = new RobotAgentWorldInterface();
}

BasicProjectKilobotConfigurationLoader::~BasicProjectKilobotConfigurationLoader()
{
	//nothing to do
}

WorldObserver* BasicProjectKilobotConfigurationLoader::make_WorldObserver(World* wm)
{
	return new KilobotBasicWorldObserver(wm);
}

RobotAgentWorldModel* BasicProjectKilobotConfigurationLoader::make_RobotAgentWorldModel()
{
	return new KilobotBasicAgentWorldModel();
}

AgentObserver* BasicProjectKilobotConfigurationLoader::make_AgentObserver(RobotAgentWorldModel* wm)
{
	return new KilobotBasicAgentObserver(wm);
}

BehaviorControlArchitecture* BasicProjectKilobotConfigurationLoader::make_BehaviorControlArchitecture(RobotAgentWorldModel* wm)
{
	return new KilobotBasicControlArchitecture(wm);
}

RobotAgentWorldInterface* BasicProjectKilobotConfigurationLoader::make_RobotAgentWorldInterface()
{
	return _AgentWorldInterface;
}

#endif
