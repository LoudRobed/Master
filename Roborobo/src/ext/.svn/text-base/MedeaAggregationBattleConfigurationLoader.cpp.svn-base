#if defined PRJ_MEDEA_AGGREGATION || !defined MODULAR

#include "Config/MedeaAggregationBattleConfigurationLoader.h"

#include "mEDEA-aggregation/include/MedeaAggregationBattleWorldObserver.h"
#include "mEDEA-aggregation/include/MedeaAggregationAgentWorldModel.h"
#include "mEDEA-aggregation/include/MedeaAggregationBattleAgentObserver.h"
#include "mEDEA-aggregation/include/MedeaAggregationControlArchitecture.h"
#include "connectionMechanism/GripperWorldInterface.h"

MedeaAggregationBattleConfigurationLoader::MedeaAggregationBattleConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
	_AgentWorldInterface = new RobotAgentWorldInterface();
}

MedeaAggregationBattleConfigurationLoader::~MedeaAggregationBattleConfigurationLoader()
{
	//nothing to do
}

WorldObserver* MedeaAggregationBattleConfigurationLoader::make_WorldObserver(World* wm)
{
	return new MedeaAggregationBattleWorldObserver(wm);
}

RobotAgentWorldModel* MedeaAggregationBattleConfigurationLoader::make_RobotAgentWorldModel()
{
	return new MedeaAggregationAgentWorldModel();
}

AgentObserver* MedeaAggregationBattleConfigurationLoader::make_AgentObserver(RobotAgentWorldModel* wm)
{
	return new MedeaAggregationBattleAgentObserver(wm);
}

BehaviorControlArchitecture* MedeaAggregationBattleConfigurationLoader::make_BehaviorControlArchitecture(RobotAgentWorldModel* wm)
{
	return new MedeaAggregationControlArchitecture(wm);
}

RobotAgentWorldInterface* MedeaAggregationBattleConfigurationLoader::make_RobotAgentWorldInterface()
{
		return new GripperWorldInterface(); // pointer to single instance
}

#endif
