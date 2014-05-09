/*
 *  MedeaAltruismReplayAgentObserver.cpp
 *  Roborobo
 *
 *  Created by Jean-Marc on 15/12/09.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *  modification on 25/10/2010
 *
 */


#include "mEDEA-altruism/include/MedeaAltruismReplayAgentObserver.h"

#include "World/World.h"
#include "Utilities/Misc.h"
#include "RoboroboMain/roborobo.h"
#include "mEDEA-altruism/include/MedeaAltruismPerceptronControlArchitecture.h"
#include "mEDEA-altruism/include/MedeaAltruismAgentWorldModel.h"


MedeaAltruismReplayAgentObserver::MedeaAltruismReplayAgentObserver( RobotAgentWorldModel *__wm )
{
	_wm = (MedeaAltruismAgentWorldModel*)__wm;

	_wm->_minValue = -0.0;
	_wm->_maxValue = 0.0;

	_wm->_currentSigma = MedeaAltruismSharedData::gSigmaRef;
	_wm->setLifeTime(1);
	_wm->setWaitForGenome(true);
	_wm->setActiveStatus(true);
	_wm->_genomesList.clear();
	_wm->_sigmaList.clear();

	gProperties.checkAndGetPropertyValue("nbHiddenNeurons",&_wm->_nbHiddenNeurons,true);
	gProperties.checkAndGetPropertyValue("gNbMaxGenomeSelection",&nbMaxGenomeSelection,true);
	
	_wm->resetActiveGenome();
	_wm->setMaturity(0);
	
	if ( gVerbose )
	{
		std::cout << "robot #" << _wm->_agentId << "\n" ;	
	}
}

MedeaAltruismReplayAgentObserver::~MedeaAltruismReplayAgentObserver()
{
	// nothing to do.
}

void MedeaAltruismReplayAgentObserver::reset()
{
	// nothing to do 
}

void MedeaAltruismReplayAgentObserver::step()
{
	// debug verbose
	if ( gVerbose && gInspectAgent && gAgentIndexFocus == _wm->_agentId )
	{
		std::cout << "target: " << _wm->getEnergyPointDirectionAngleValue() << std::endl;
	}

	MedeaAltruismPerceptronControlArchitecture* currentBehavior = dynamic_cast<MedeaAltruismPerceptronControlArchitecture*>(gWorld->getAgent(_wm->_agentId)->getBehavior());

	if ( ! currentBehavior )
	{
		std::cerr << "Error from robot " << _wm->_agentId << " : the behavior architecture of this robot  isn't a MedeaAltruismPerceptronControlArchitecture" << std::endl;
		exit(1);
	}

	gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " " << _wm->_xReal << ":" << _wm->_yReal << std::endl;
	
}

void MedeaAltruismReplayAgentObserver::loadGenome(std::vector<double> inGenome)
{
	std::cout << std::flush ;
	_wm->_currentGenome.clear();
	for ( unsigned int i = 0 ; i != inGenome.size() ; i++ )
	{
		_wm->_currentGenome.push_back(inGenome[i]);
	}
	_wm->setNewGenomeStatus(true);
//	MedeaAltruismPerceptronControlArchitecture* currentBehavior = dynamic_cast<MedeaAltruismPerceptronControlArchitecture*>(gWorld->getAgent(_wm->_agentId)->getBehavior());
	_wm->setDeltaEnergy(0.0);
}

