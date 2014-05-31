#if defined PRJ_MEDEA_ALTRUISM || !defined MODULAR

#include "Config/MedeaAltruismIncreasePressureConfigurationLoader.h"

#include "mEDEA-altruism/include/MedeaAltruismIncreasePressureWorldObserver.h"
#include "mEDEA-altruism/include/MedeaAltruismAgentWorldModel.h"
#include "mEDEA-altruism/include/MedeaAltruismIncreasePressureAgentObserver.h"
#include "mEDEA-altruism/include/MedeaAltruismPerceptronControlArchitecture.h"
#include "World/RobotAgentWorldInterfaceDangerWorld.h"

MedeaAltruismIncreasePressureConfigurationLoader::MedeaAltruismIncreasePressureConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
	_AgentWorldInterface = new RobotAgentWorldInterfaceDangerWorld();
}

MedeaAltruismIncreasePressureConfigurationLoader::~MedeaAltruismIncreasePressureConfigurationLoader()
{
	//nothing to do
}

WorldObserver* MedeaAltruismIncreasePressureConfigurationLoader::make_WorldObserver(World* wm)
{
	return new MedeaAltruismIncreasePressureWorldObserver(wm);
}

RobotAgentWorldModel* MedeaAltruismIncreasePressureConfigurationLoader::make_RobotAgentWorldModel()
{
	return new MedeaAltruismAgentWorldModel();
}

AgentObserver* MedeaAltruismIncreasePressureConfigurationLoader::make_AgentObserver(RobotAgentWorldModel* wm)
{
	return new MedeaAltruismIncreasePressureAgentObserver(wm);
}

BehaviorControlArchitecture* MedeaAltruismIncreasePressureConfigurationLoader::make_BehaviorControlArchitecture(RobotAgentWorldModel* wm)
{
	return new MedeaAltruismPerceptronControlArchitecture(wm);
}

RobotAgentWorldInterface* MedeaAltruismIncreasePressureConfigurationLoader::make_RobotAgentWorldInterface()
{
		return _AgentWorldInterface; // pointer to single instance
}

#endif
