/*
 *  AggregationBasicWorldObserver.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 27/05/10.
 *
 */

#include "BasicProject-aggregation/include/AggregationBasicWorldObserver.h"
#include "Agents/RobotAgentConnectable.h"

#include "World/World.h"


AggregationBasicWorldObserver::AggregationBasicWorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
	agentPositiveMaskImageFilename = "data/agent-positive-mask.png";
	agentNegativeMaskImageFilename = "data/agent-negative-mask.png";

	if (gProperties.hasProperty("agentPositiveMaskImageFilename"))
	{
		agentPositiveMaskImageFilename = gProperties.getProperty("agentPositiveMaskImageFilename");
	}
		
	if (gProperties.hasProperty("agentNegativeMaskImageFilename"))
	{
		agentNegativeMaskImageFilename = gProperties.getProperty("agentNegativeMaskImageFilename");
	}

	agentPositiveMaskImage = load_image(agentPositiveMaskImageFilename);
	if (agentPositiveMaskImage == NULL) {
		std::cerr << "Could not load agent positive mask image\n";
	}

	agentNegativeMaskImage = load_image(agentNegativeMaskImageFilename);
	if (agentNegativeMaskImage == NULL) {
		std::cerr << "Could not load agent negative mask image\n";
	}

	SDL_SetColorKey(agentPositiveMaskImage, SDL_SRCCOLORKEY, SDL_MapRGB(agentPositiveMaskImage->format, 0xFF, 0xFF, 0xFF));
	SDL_SetColorKey(agentNegativeMaskImage, SDL_SRCCOLORKEY, SDL_MapRGB(agentNegativeMaskImage->format, 0xFF, 0xFF, 0xFF));
}

AggregationBasicWorldObserver::~AggregationBasicWorldObserver()
{
	// nothing to do.
	SDL_FreeSurface(agentPositiveMaskImage);
	SDL_FreeSurface(agentNegativeMaskImage);
}

void AggregationBasicWorldObserver::reset()
{
	// nothing to do.
}

void AggregationBasicWorldObserver::step()
{
	for ( int i = 0 ; i != gAgentCounter ; i++ )
	{
		RobotAgentConnectable* agent = dynamic_cast<RobotAgentConnectable*>(gWorld->getAgent(i));
		if (agent == 0)
		{
			std::cerr << "With Aggregation Basic project, RobotAgentConnectable should be used" << std::endl;
			exit(1);
		}
		if (agent->isPartOfOrganism() == true)
		{
			agent->setAgentMask(agentPositiveMaskImage);
		}
		else
		{
			agent->setAgentMask(agentNegativeMaskImage);
		}
	}
}


