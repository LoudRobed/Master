/*
 *  SpikeAntsAgentWorldModel.h
 *  roborobo-online
 *
 *  Created by Nicolas on 27/05/10.
 *
 */


#ifndef SPIKEANTSAGENTWORLDMODEL_H
#define SPIKEANTSAGENTWORLDMODEL_H 

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "WorldModels/RobotAgentWorldModel.h"

#include "SpikeAnts/include/lif.h"
#include "SpikeAnts/include/qif.h"

class World;

class SpikeAntsAgentWorldModel : public RobotAgentWorldModel
{	
private: 
  int _robotNeighborhoodCounter; // count the number of other robots within a given radius.

  int _incomingSpikes;
  qif* _activeNeuron;
  lif* _passiveNeuron;
	
public:
  enum saStatus {WORK, SLEEP, SIESTA, OBSERVE};
  saStatus _currentStatus;
  int _saForageSuccess;
  int _saAvoidCounter;
  int _isFiring;
  bool _saUnboundObs;
  bool _saUnboundFor;

  int _saObs, _saForage, _saSleep, _saGroom;
  int _saObsTimer, _saForageTimer, _saSleepTimer;
  double _saLifRest, _saLifTau, _saLifThres, _saLifReset;
  double _saQifTau, _saQifRest, _saQifThres, _saQifVth, _saQifReset, _saQifWin;
  double _spikeIntegrationStep;
  double _saWeight;

  // refer to super class to check what data / methods are available.		
  SpikeAntsAgentWorldModel();
  virtual ~SpikeAntsAgentWorldModel();

  int getCurrentStatus ();

  // int isSpiking ();
  void addSpikeEvent ();
  int getSpikeEvent ();

  double getActivePotential ();
  int updateActiveNeuron ();
  void addPspActiveNeuron (int nbSpike);
  void resetActiveNeuronPotential ();
  void addWinActiveNeuron ();
  double getPassivePotential ();
  int updatePassiveNeuron ();
  void addPspPassiveNeuron (int nbSpike);
  
};


#endif


