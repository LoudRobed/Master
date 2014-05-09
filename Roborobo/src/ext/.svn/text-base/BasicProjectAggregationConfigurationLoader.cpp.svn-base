#if defined PRJ_BASICPROJECT_AGGREGATION || !defined MODULAR

#include "Config/BasicProjectAggregationConfigurationLoader.h"

#include "BasicProject-aggregation/include/AggregationBasicWorldObserver.h"
#include "BasicProject-aggregation/include/AggregationBasicAgentWorldModel.h"
#include "BasicProject-aggregation/include/AggregationBasicAgentObserver.h"
#include "BasicProject-aggregation/include/AggregationBasicControlArchitecture.h"
#include "connectionMechanism/GripperWorldInterface.h"

#include "World/RobotAgentWorldInterface.h"

BasicProjectAggregationConfigurationLoader::BasicProjectAggregationConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
	_AgentWorldInterface = new RobotAgentWorldInterface();
}

BasicProjectAggregationConfigurationLoader::~BasicProjectAggregationConfigurationLoader()
{
	//nothing to do
}

WorldObserver* BasicProjectAggregationConfigurationLoader::make_WorldObserver(World* wm)
{
	return new AggregationBasicWorldObserver(wm);
}

RobotAgentWorldModel* BasicProjectAggregationConfigurationLoader::make_RobotAgentWorldModel()
{
	return new AggregationBasicAgentWorldModel();
}

AgentObserver* BasicProjectAggregationConfigurationLoader::make_AgentObserver(RobotAgentWorldModel* wm)
{
	return new AggregationBasicAgentObserver(wm);
}

BehaviorControlArchitecture* BasicProjectAggregationConfigurationLoader::make_BehaviorControlArchitecture(RobotAgentWorldModel* wm)
{
	return new AggregationBasicControlArchitecture(wm);
}

RobotAgentWorldInterface* BasicProjectAggregationConfigurationLoader::make_RobotAgentWorldInterface()
{
	//return _AgentWorldInterface;
	return new GripperWorldInterface();
}

#endif
