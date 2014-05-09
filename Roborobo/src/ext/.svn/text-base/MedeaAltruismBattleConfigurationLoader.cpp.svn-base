#if defined PRJ_MEDEA_ALTRUISM || !defined MODULAR

#include "Config/MedeaAltruismBattleConfigurationLoader.h"

#include "mEDEA-altruism/include/MedeaAltruismBattleWorldObserver.h"
#include "mEDEA-altruism/include/MedeaAltruismAgentWorldModel.h"
#include "mEDEA-altruism/include/MedeaAltruismBattleAgentObserver.h"
#include "mEDEA-altruism/include/MedeaAltruismPerceptronControlArchitecture.h"
#include "World/RobotAgentWorldInterfaceDangerWorld.h"

MedeaAltruismBattleConfigurationLoader::MedeaAltruismBattleConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
	_AgentWorldInterface = new RobotAgentWorldInterfaceDangerWorld();
}

MedeaAltruismBattleConfigurationLoader::~MedeaAltruismBattleConfigurationLoader()
{
	//nothing to do
}


WorldObserver* MedeaAltruismBattleConfigurationLoader::make_WorldObserver(World* wm)
{
	return new MedeaAltruismBattleWorldObserver(wm);
}

RobotAgentWorldModel* MedeaAltruismBattleConfigurationLoader::make_RobotAgentWorldModel()
{
	return new MedeaAltruismAgentWorldModel();
}

AgentObserver* MedeaAltruismBattleConfigurationLoader::make_AgentObserver(RobotAgentWorldModel* wm)
{
	return new MedeaAltruismBattleAgentObserver(wm);
}

BehaviorControlArchitecture* MedeaAltruismBattleConfigurationLoader::make_BehaviorControlArchitecture(RobotAgentWorldModel* wm)
{
	return new MedeaAltruismPerceptronControlArchitecture(wm);
}

RobotAgentWorldInterface* MedeaAltruismBattleConfigurationLoader::make_RobotAgentWorldInterface()
{
	return _AgentWorldInterface;
}

#endif
