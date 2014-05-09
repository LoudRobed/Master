#if defined PRJ_MEDEA_AGGREGATION || !defined MODULAR

#include "Config/MedeaAggregationConfigurationLoader.h"

#include "mEDEA-aggregation/include/MedeaAggregationWorldObserver.h"
#include "mEDEA-aggregation/include/MedeaAggregationAgentWorldModel.h"
#include "mEDEA-aggregation/include/MedeaAggregationAgentObserver.h"
#include "mEDEA-aggregation/include/MedeaAggregationControlArchitecture.h"
#include "connectionMechanism/GripperWorldInterface.h"

MedeaAggregationConfigurationLoader::MedeaAggregationConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
	_AgentWorldInterface = new RobotAgentWorldInterface();
}

MedeaAggregationConfigurationLoader::~MedeaAggregationConfigurationLoader()
{
	//nothing to do
}

WorldObserver* MedeaAggregationConfigurationLoader::make_WorldObserver(World* wm)
{
	return new MedeaAggregationWorldObserver(wm);
}

RobotAgentWorldModel* MedeaAggregationConfigurationLoader::make_RobotAgentWorldModel()
{
	return new MedeaAggregationAgentWorldModel();
}

AgentObserver* MedeaAggregationConfigurationLoader::make_AgentObserver(RobotAgentWorldModel* wm)
{
	return new MedeaAggregationAgentObserver(wm);
}

BehaviorControlArchitecture* MedeaAggregationConfigurationLoader::make_BehaviorControlArchitecture(RobotAgentWorldModel* wm)
{
	return new MedeaAggregationControlArchitecture(wm);
}

RobotAgentWorldInterface* MedeaAggregationConfigurationLoader::make_RobotAgentWorldInterface()
{
		return new GripperWorldInterface(); // pointer to single instance
}

#endif
