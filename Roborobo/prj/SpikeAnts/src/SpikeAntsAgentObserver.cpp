/*
 *  SpikeAntsAgentObserver.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 27/05/10.
 *
 */

#include "SpikeAnts/include/SpikeAntsAgentObserver.h"

SpikeAntsAgentObserver::SpikeAntsAgentObserver( )
{
}

SpikeAntsAgentObserver::SpikeAntsAgentObserver( RobotAgentWorldModel *__wm )
{
  _wm = (SpikeAntsAgentWorldModel*)__wm;  
}

SpikeAntsAgentObserver::~SpikeAntsAgentObserver()
{
  // nothing to do.
}

void SpikeAntsAgentObserver::reset()
{
  // nothing to do.
}

void SpikeAntsAgentObserver::step()
{
  int ret = 0;
  int rcvSpike = -1;

  // spiking neurons update
  if (_wm->_currentStatus == SpikeAntsAgentWorldModel::OBSERVE) {
	 if (! _wm->_saUnboundObs)	 // bounded observation period
		_wm->_saObsTimer--;
	 if ((_wm->_saObsTimer == 0) && (_wm->getActivePotential () < _wm->_saQifVth)) {
		/* End of observation and active neuron won't spike soon */
		/* Call it a draw */
		/* state OBSERVE -> SIESTA */
		_wm->_currentStatus = SpikeAntsAgentWorldModel::SIESTA;
		_wm->_saSleepTimer = _wm->_saGroom;
		ret += _wm->updateActiveNeuron ();
		ret += 2 * _wm->updatePassiveNeuron ();
	 }
	 else if ((_wm->_saObsTimer == 0) && (_wm->getActivePotential () > _wm->_saQifVth)) {
		/* End of observation and active neuron will fire soon */
		/* state OBSERVE -> WORK */
		ret += _wm->updateActiveNeuron ();
		ret += 2 * _wm->updatePassiveNeuron ();
		_wm->_currentStatus = SpikeAntsAgentWorldModel::WORK;
		if (! _wm->_saUnboundFor) _wm->_saForageTimer = _wm->_saForage;
		else _wm->_saForageTimer = 0;
	 }
	 else {
		rcvSpike = _wm->getSpikeEvent ();
		if (rcvSpike > 0) {
		  if ( gVerbose ) 
			 std::cout << "SENDSPIKE " << _wm->_agentId << " has received " << rcvSpike << " spikes" << std::endl;
		  _wm->addPspActiveNeuron (rcvSpike);
		  _wm->addPspPassiveNeuron (rcvSpike);
		}
	 }
	 if (_wm->updatePassiveNeuron ()) {
		ret += 2;
		_wm->_currentStatus = SpikeAntsAgentWorldModel::SIESTA;
		_wm->_saSleepTimer = _wm->_saGroom;
		_wm->resetActiveNeuronPotential ();
	 }
	 else _wm->addWinActiveNeuron ();
	 if (_wm->updateActiveNeuron ()) {
		ret += 1;
		_wm->_currentStatus = SpikeAntsAgentWorldModel::WORK;
		if (! _wm->_saUnboundFor) _wm->_saForageTimer = _wm->_saForage;
		else _wm->_saForageTimer = 0;
	 }
  }
  else if (_wm->_currentStatus == SpikeAntsAgentWorldModel::WORK) {
	 if (! _wm->_saUnboundFor)	_wm->_saForageTimer--; // bounded foraging period
	 else _wm->_saForageTimer++;

	 if (((! _wm->_saUnboundFor) && (_wm->_saForageTimer == 0)) ||
		  ((_wm->_saUnboundFor) && (_wm->_saForageSuccess != 0))){
		_wm->_currentStatus = SpikeAntsAgentWorldModel::SLEEP;
		_wm->_saSleepTimer = _wm->_saSleep;
		gLogFile << "STATUSALLFORAGE " << _wm->_agentId << " " << _wm->_saForageSuccess << std::endl;		
		_wm->_saForageSuccess = 0;
		_wm->resetActiveNeuronPotential ();
		ret += _wm->updateActiveNeuron ();
	 }
	 else if (_wm->updateActiveNeuron ()) {
		ret += 1;
	 }
	 ret += 2 * _wm->updatePassiveNeuron ();
  }
  else if ((_wm->_currentStatus ==  SpikeAntsAgentWorldModel::SIESTA) ||
			  (_wm->_currentStatus ==  SpikeAntsAgentWorldModel::SLEEP)) {
	 _wm->_saSleepTimer--;
	 ret += _wm->updateActiveNeuron ();
	 ret += 2 * _wm->updatePassiveNeuron ();
	 if (_wm->_saSleepTimer == 0) {
		_wm->_currentStatus = SpikeAntsAgentWorldModel::OBSERVE;
		_wm->_saObsTimer = _wm->_saObs;
	 }
  }
  _wm->_isFiring = ret;
}


