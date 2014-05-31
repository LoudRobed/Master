/*
 *  AggregationBasicAgentObserver.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 27/05/10.
 *
 */

#include "BasicProject-aggregation/include/AggregationBasicAgentObserver.h"



AggregationBasicAgentObserver::AggregationBasicAgentObserver( )
{
}

AggregationBasicAgentObserver::AggregationBasicAgentObserver( RobotAgentWorldModel *__wm )
{
	_wm = (AggregationBasicAgentWorldModel*)__wm;
}

AggregationBasicAgentObserver::~AggregationBasicAgentObserver()
{
	// nothing to do.
}

void AggregationBasicAgentObserver::reset()
{
	// nothing to do.
}

void AggregationBasicAgentObserver::step()
{
	// nothing to do.
}

