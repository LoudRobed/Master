/*
 *  MedeaAltUtilityReplayAgentObserver.cpp
 *  Roborobo
 *
 *  Created by Jean-Marc on 15/12/09.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *  modification on 25/10/2010
 *
 */


#include "mEDEA-altruism-utility/include/MedeaAltUtilityReplayAgentObserver.h"

#include "World/World.h"
#include "Utilities/Misc.h"
#include "RoboroboMain/roborobo.h"
#include "mEDEA-altruism-utility/include/MedeaAltUtilityPerceptronControlArchitecture.h"
#include "mEDEA-altruism-utility/include/MedeaAltUtilityAgentWorldModel.h"


MedeaAltUtilityReplayAgentObserver::MedeaAltUtilityReplayAgentObserver( RobotAgentWorldModel *__wm )
{
	_wm = (MedeaAltUtilityAgentWorldModel*)__wm;

	_wm->_minValue = -1.0;
	_wm->_maxValue = 1.0;

	_wm->_currentSigma = MedeaAltUtilitySharedData::gSigmaRef;

	gProperties.checkAndGetPropertyValue("nbHiddenNeurons",&_wm->_nbHiddenNeurons,true);
	
	_wm->resetActiveGenome();
	
	if ( gVerbose )
	{
		std::cout << "robot #" << _wm->_agentId << "\n" ;	
	}
}

MedeaAltUtilityReplayAgentObserver::~MedeaAltUtilityReplayAgentObserver()
{
	// nothing to do.
}

void MedeaAltUtilityReplayAgentObserver::reset()
{
	// nothing to do 
}

void MedeaAltUtilityReplayAgentObserver::step()
{
					
	// debug verbose
	if ( gVerbose && gInspectAgent && gAgentIndexFocus == _wm->_agentId )
	{
		std::cout << "target: " << _wm->getEnergyPointDirectionAngleValue() << std::endl;
	}

	MedeaAltUtilityPerceptronControlArchitecture* currentBehavior = dynamic_cast<MedeaAltUtilityPerceptronControlArchitecture*>(gWorld->getAgent(_wm->_agentId)->getBehavior());

	if ( ! currentBehavior )
	{
		std::cerr << "Error from robot " << _wm->_agentId << " : the behavior architecture of this robot  isn't a MedeaAltUtilityPerceptronControlArchitecture" << std::endl;
		exit(1);
	}
	
}

void MedeaAltUtilityReplayAgentObserver::loadGenome(std::vector<double> inGenome)
{
	std::cout << std::flush ;
	_wm->_genome.clear();
	for ( unsigned int i = 0 ; i != inGenome.size() ; i++ )
	{
		_wm->_genome.push_back(inGenome[i]);
	}
	_currentGenome = _wm->_genome;
	_wm->setNewGenomeStatus(true);
//	MedeaAltUtilityPerceptronControlArchitecture* currentBehavior = dynamic_cast<MedeaAltUtilityPerceptronControlArchitecture*>(gWorld->getAgent(_wm->_agentId)->getBehavior());
	_wm->setDeltaEnergy(0.0);
}

