/*
 *  SpikeAntsWorldObserver.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 27/05/10.
 *
 */

#include "SpikeAnts/include/SpikeAntsWorldObserver.h"
#include "SpikeAnts/include/SpikeAntsAgentWorldModel.h"

#include "World/World.h"


SpikeAntsWorldObserver::SpikeAntsWorldObserver( World *__world ) : WorldObserver( __world )
{
  _world = __world;
  gProperties.checkAndGetPropertyValue("RecordPotentialFocus",&_saRecFocPot,true);
  gProperties.checkAndGetPropertyValue("RecordAgentsPosition",&_saRecAgPos,true);
}

SpikeAntsWorldObserver::~SpikeAntsWorldObserver()
{
  int nbAvoidCounter = 0;
  for (int i = 0 ; i < gAgentCounter ; i++) {
	 SpikeAntsAgentWorldModel *wm = (SpikeAntsAgentWorldModel*)gWorld->getAgent(i)->getWorldModel();
	 if (wm->_saAvoidCounter != 0) nbAvoidCounter += wm->_saAvoidCounter;
  }
  gLogFile << "STATUSAVOID " << gWorld->getIterations() << " " << nbAvoidCounter << std::endl;
}

void SpikeAntsWorldObserver::reset()
{
  Point2d positionNest(150,390);
  Point2d positionHarvestZone1(650,413);
  // Point2d positionHarvestZone2(400,600);

  gEnergyPoints[0].hide();
  gEnergyPoints[0].setFixedLocationStatus(true);
  gEnergyPoints[0].setPosition(positionNest);
  gEnergyPoints[0].display();

  gEnergyPoints[1].hide();
  gEnergyPoints[1].setFixedLocationStatus(true);
  gEnergyPoints[1].setPosition(positionHarvestZone1);
  gEnergyPoints[1].display();
}

void SpikeAntsWorldObserver::step()
{
  int nbObs = 0, nbFor = 0, nbSleep = 0, nbGroom = 0, nbForSuc = 0, nbAvoidCounter = 0;

  // Update light according to agent status :
  //  - black when sleeping
  //  - white when grooming
  //  - green when observing
  //  - red when foraging or blue if spiking during foraging
  // If spiking when foraging, send spike to observing agents in radio network
  for (int i = 0 ; i < gAgentCounter ; i++) {
	 SpikeAntsAgentWorldModel *wm = (SpikeAntsAgentWorldModel*)gWorld->getAgent(i)->getWorldModel();
	 if (wm->_currentStatus == SpikeAntsAgentWorldModel::OBSERVE) {
		wm->setRobotLED_colorValues(0,255,0);
	 }
	 else if (wm->_currentStatus == SpikeAntsAgentWorldModel::SLEEP) {
		wm->setRobotLED_colorValues(0,0,0);
	 }
	 else if (wm->_currentStatus == SpikeAntsAgentWorldModel::SIESTA) {
		wm->setRobotLED_colorValues(0,0,0); //(255,255,255);
	 }
	 else if (wm->_isFiring == 1) {
		wm->setRobotLED_colorValues(255,0,0); //(0,0,255);
		for (int j = 0 ; j < gAgentCounter ; j++) {
		  if (( i != j ) && ( gRadioNetworkArray[i][j])) {
			 SpikeAntsAgentWorldModel *wmTarget = (SpikeAntsAgentWorldModel*)gWorld->getAgent(j)->getWorldModel();
			 if (wmTarget->_currentStatus == SpikeAntsAgentWorldModel::OBSERVE)
				wmTarget->addSpikeEvent ();
		  }
		}
	 }
	 else {
		if (wm->_saForageSuccess != 0) wm->setRobotLED_colorValues(255,0,0); //(0,255,255);
		else wm->setRobotLED_colorValues(255,0,0);
	 }
  }  

  for (int i = 0 ; i < gAgentCounter ; i++) {
	 SpikeAntsAgentWorldModel *wm = (SpikeAntsAgentWorldModel*)gWorld->getAgent(i)->getWorldModel();
	 if (wm->_currentStatus == SpikeAntsAgentWorldModel::OBSERVE) nbObs++;
	 else if (wm->_currentStatus == SpikeAntsAgentWorldModel::SLEEP) nbSleep++;
	 else if (wm->_currentStatus == SpikeAntsAgentWorldModel::SIESTA) nbGroom++;
	 else if (wm->_currentStatus == SpikeAntsAgentWorldModel::WORK) nbFor++;
	 if (wm->_saForageSuccess != 0) nbForSuc++;
	 if (wm->_saAvoidCounter != 0) nbAvoidCounter += wm->_saAvoidCounter;
  }
  gLogFile << "STATUSGLOBAL " << gWorld->getIterations() << " " << nbObs << " " << nbFor << " " << nbSleep << " " << nbGroom << std::endl;
  gLogFile << "STATUSFORAGE " << gWorld->getIterations() << " " << nbForSuc << std::endl;
  gLogFile << "STATUSAVOID " << gWorld->getIterations() << " " << nbAvoidCounter << std::endl;

  for (int i = 0 ; i < gAgentCounter ; i++) {
	 SpikeAntsAgentWorldModel *wm = (SpikeAntsAgentWorldModel*)gWorld->getAgent(i)->getWorldModel();
	 if (_saRecAgPos) //record all agent positions for creating activity images
		gLogFile << "STATUSALLAGENT " << wm->_agentId << " " << gWorld->getIterations() << " " << wm->_currentStatus << " " << wm->getXReal() << " " << wm->getYReal() << std::endl;

	 if (wm->_agentId == gAgentIndexFocus) { // only focused agent (press hotk
		gLogFile << "STATUSAGENT " << wm->_agentId << " " << gWorld->getIterations() << " " << wm->_currentStatus << std::endl;
		if (_saRecFocPot) {//log neurons' potential of focused agent
		  gLogFile << "QIFAGENT " << wm->_agentId << " " << gWorld->getIterations() << " " << wm->getActivePotential () << std::endl;
		  gLogFile << "LIFAGENT " << wm->_agentId << " " << gWorld->getIterations() << " " << wm->getPassivePotential () << std::endl;
		}
	 }
  }  
}
