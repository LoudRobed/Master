/*
 *  SpikeAntsWorldModel.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 27/05/10.
 *
 */

#include "SpikeAnts/include/SpikeAntsAgentWorldModel.h"

#include "World/World.h"

SpikeAntsAgentWorldModel::SpikeAntsAgentWorldModel()
{
  double mu;
  gsl_rng *r;
  r = gsl_rng_alloc (gsl_rng_taus);
  gsl_rng_set (r, rand());

  _sensors = NULL;
  /******************    Reading properties   ***********************/
  gProperties.checkAndGetPropertyValue("globalWeight",&_saWeight,true);
  gProperties.checkAndGetPropertyValue("SpikeIntegrationStep",&_spikeIntegrationStep,true);
  gProperties.checkAndGetPropertyValue("ObserveTime",&_saObs,true);
  gProperties.checkAndGetPropertyValue("ForageTime",&_saForage,true);
  gProperties.checkAndGetPropertyValue("SleepTime",&_saSleep,true);
  gProperties.checkAndGetPropertyValue("GroomTime",&_saGroom,true);
  gProperties.checkAndGetPropertyValue("LifRest",&_saLifRest,true);
  gProperties.checkAndGetPropertyValue("LifTau",&_saLifTau,true);
  gProperties.checkAndGetPropertyValue("LifThres",&_saLifThres,true);
  gProperties.checkAndGetPropertyValue("LifReset",&_saLifReset,true);
  gProperties.checkAndGetPropertyValue("QifTau",&_saQifTau,true);
  gProperties.checkAndGetPropertyValue("QifRest",&_saQifRest,true);
  gProperties.checkAndGetPropertyValue("QifThres",&_saQifThres,true);
  gProperties.checkAndGetPropertyValue("QifVth",&_saQifVth,true);
  gProperties.checkAndGetPropertyValue("QifReset",&_saQifReset,true);
  gProperties.checkAndGetPropertyValue("QifWin",&_saQifWin,true);
  gProperties.checkAndGetPropertyValue("UnboundedObservation",&_saUnboundObs,true);
  gProperties.checkAndGetPropertyValue("UnboundedForaging",&_saUnboundFor,true);
  gProperties.checkAndGetPropertyValue("MuInit",&mu,true);

  /********************     Initialization     *************************/
  _isFiring = 0;
  _incomingSpikes = 0;
  _saForageSuccess = 0;
  _saAvoidCounter = 0;
  _currentStatus = SLEEP;
  _saObsTimer = 0;
  _saForageTimer = 0;
  _saSleepTimer = (int) (rand() % (2*_saSleep)) + 1;
  // _saSleepTimer = (int) gsl_ran_poisson (r, mu) * 100;
  // printf ("_saSleepTimer = %d\n", _saSleepTimer);

  if (((_activeNeuron = (qif*) malloc (sizeof (qif))) == NULL) ||
		((_passiveNeuron = (lif*) malloc (sizeof(lif))) == NULL)){
  	 printf ("[FATAL] Malloc error: cannot allocation new neurons\n");
  	 exit (1);
  }
  init_lif (_passiveNeuron, _saLifRest, _saLifTau, _saLifRest, _saLifThres, _saLifReset, _spikeIntegrationStep, 100000);
  init_qif (_activeNeuron, _saQifRest, _saQifTau, _saQifRest, _spikeIntegrationStep, 
				_saQifThres, _saQifVth, _saQifReset, 100000);
  gsl_rng_free (r);
}

SpikeAntsAgentWorldModel::~SpikeAntsAgentWorldModel()
{
	if ( _sensors != NULL )
		delete[] _sensors;
	// zz: change total_runtime & filename
#ifdef PTRACE
	if (_activeNeuron != NULL)
	  destroy_qif (_activeNeuron, "./aSuppr-qif.txt", 1000000);
#endif
	free (_activeNeuron);
#ifdef PTRACE
	if (_passiveNeuron != NULL)
	  destroy_lif (_passiveNeuron, "./aSuppr-lif.txt", 1000000);
#endif
	free (_passiveNeuron);
}

// Access function
int SpikeAntsAgentWorldModel::getCurrentStatus () {
  return _currentStatus;
}

// Spike Handling
// int SpikeAntsAgentWorldModel::isSpiking () {
//   if (_isFiring == 1) return 1;
//   else return 0;
// }

void SpikeAntsAgentWorldModel::addSpikeEvent () {
  _incomingSpikes++;
}

int SpikeAntsAgentWorldModel::getSpikeEvent () {
  int nbSp = _incomingSpikes;
  _incomingSpikes = -1;
  return nbSp;
}

// Neuron getter and setter
double SpikeAntsAgentWorldModel::getActivePotential () {
  return _activeNeuron->pot;
}

int SpikeAntsAgentWorldModel::updateActiveNeuron () {
  return update_qif (_activeNeuron, 10.);
}

void SpikeAntsAgentWorldModel::addPspActiveNeuron (int nbSpike) {
  add_input (_activeNeuron, (double) nbSpike * -1. * _saWeight);
}

void SpikeAntsAgentWorldModel::resetActiveNeuronPotential () {
  set_pot_qif (_activeNeuron, _saQifRest);
}

void SpikeAntsAgentWorldModel::addWinActiveNeuron () {
  add_input (_activeNeuron, _saQifWin);
}

double SpikeAntsAgentWorldModel::getPassivePotential () {
  return _passiveNeuron->pot;
}
int SpikeAntsAgentWorldModel::updatePassiveNeuron () {
  return update_lif (_passiveNeuron, 10.);
}

void SpikeAntsAgentWorldModel::addPspPassiveNeuron (int nbSpike) {
  add_input_lif (_passiveNeuron, (double)nbSpike * _saWeight);
}

