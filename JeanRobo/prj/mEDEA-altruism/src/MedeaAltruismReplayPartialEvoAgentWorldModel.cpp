/*
 *  MedeaAltruismReplayPartialEvoAgentWorldModel.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 15/04/10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *  moved in ReplayPartialEvo by Jean-Marc on 17/12/2010
 *
 */

#include "mEDEA-altruism/include/MedeaAltruismReplayPartialEvoAgentWorldModel.h"

MedeaAltruismReplayPartialEvoAgentWorldModel::MedeaAltruismReplayPartialEvoAgentWorldModel()
{
	_energyHarvestingRate = 0.0;
	_totalEnergyHarvested = 0.0;
}

MedeaAltruismReplayPartialEvoAgentWorldModel::~MedeaAltruismReplayPartialEvoAgentWorldModel()
{
}

double MedeaAltruismReplayPartialEvoAgentWorldModel::getEnergyPointDirectionAngleValue()
{
	return _energyPointDirectionAngleValue;
}

double MedeaAltruismReplayPartialEvoAgentWorldModel::getEnergyPointDistanceValue()
{
	return _energyPointDistanceValue;
}

void MedeaAltruismReplayPartialEvoAgentWorldModel::setEnergyPointDirectionAngleValue( double __value )
{
	_energyPointDirectionAngleValue = __value;
}

void MedeaAltruismReplayPartialEvoAgentWorldModel::setEnergyPointDistanceValue( double __value )
{
	_energyPointDistanceValue = __value;
}

bool MedeaAltruismReplayPartialEvoAgentWorldModel::getActiveStatus()
{
	return _isActive;
}

void MedeaAltruismReplayPartialEvoAgentWorldModel::setActiveStatus( bool __isActive )
{
	_isActive = __isActive;
}

double MedeaAltruismReplayPartialEvoAgentWorldModel::getEnergyLevel()
{
	return _energyLevel;
}

void MedeaAltruismReplayPartialEvoAgentWorldModel::setEnergyLevel(double inValue)
{
	_energyLevel = inValue;
}

bool MedeaAltruismReplayPartialEvoAgentWorldModel::getWaitingAfterLifeSynchronization()
{
	return _waitingAfterLifeSynchronization;
}

void MedeaAltruismReplayPartialEvoAgentWorldModel::setWaitingAfterLifeSynchronization( bool isSynchronized )
{
	_waitingAfterLifeSynchronization = isSynchronized;
}

double MedeaAltruismReplayPartialEvoAgentWorldModel::getDeltaEnergy()
{
	return _deltaEnergy;
}

void MedeaAltruismReplayPartialEvoAgentWorldModel::setDeltaEnergy(double inValue)
{
	_deltaEnergy = inValue;
}

void MedeaAltruismReplayPartialEvoAgentWorldModel::setAngleToClosestEnergyPoint( double __value )
{
	_angleToClosestEnergyPoint = __value;
}

double MedeaAltruismReplayPartialEvoAgentWorldModel::getAngleToClosestEnergyPoint()
{
	return _angleToClosestEnergyPoint;
}
		
void MedeaAltruismReplayPartialEvoAgentWorldModel::setDistanceToClosestEnergyPoint( double __value )
{
	_distanceToClosestEnergyPoint = __value;
}

double MedeaAltruismReplayPartialEvoAgentWorldModel::getDistanceToClosestEnergyPoint()
{
	return _distanceToClosestEnergyPoint;
}

void MedeaAltruismReplayPartialEvoAgentWorldModel::setEnergyHarvestingRate(double __energyHarvestingRate)
{
	if (__energyHarvestingRate < 0.0)
	{
		_energyHarvestingRate = 0.0;
	}
	else if (__energyHarvestingRate > 1.0)
	{
		_energyHarvestingRate = 1.0;
	}
	else
	{
		_energyHarvestingRate = __energyHarvestingRate;
	}
}

double MedeaAltruismReplayPartialEvoAgentWorldModel::getEnergyHarvestingRate()
{
	return _energyHarvestingRate;
}

void MedeaAltruismReplayPartialEvoAgentWorldModel::setPrevX (double inPrevX)
{
	_prevX = inPrevX;
}

double MedeaAltruismReplayPartialEvoAgentWorldModel::getPrevX ()
{
	return _prevX;
}

void MedeaAltruismReplayPartialEvoAgentWorldModel::setPrevY (double inPrevY)
{
	_prevY = inPrevY;
}

double MedeaAltruismReplayPartialEvoAgentWorldModel::getPrevY ()
{
	return _prevY;
}

void MedeaAltruismReplayPartialEvoAgentWorldModel::increaseTotalEnergyHarvested (double __value)
{
	if ( __value > 0.0 )
	{
		_totalEnergyHarvested += __value;
	}
}

void MedeaAltruismReplayPartialEvoAgentWorldModel::resetTotalEnergyHarvested ()
{
	_totalEnergyHarvested = 0.0;
}

double MedeaAltruismReplayPartialEvoAgentWorldModel::getTotalEnergyHarvested ()
{
	return _totalEnergyHarvested;
}

void MedeaAltruismReplayPartialEvoAgentWorldModel::resetActiveGenome()
{
	int nbInput = _sensorCount + 5 ; //sensors + floorSensor + energyDirection + energyLevel + energyDistance  +bias
	int nbOutput = 3 ; // rotation + velocity + energyHarvestingRate
	int nbGene = ( nbInput * _nbHiddenNeurons ) + ( _nbHiddenNeurons * nbOutput) + nbOutput ; // from input to hidden layer + from hiddenLayer to output + from bias to output
	std::cout << std::flush ;
	_currentGenome.clear();
	for ( int i = 0 ; i != nbGene ; i++ )
	{
		_currentGenome.push_back(((rand()%800)/400.0)-1.0);
	}
	setNewGenomeStatus(true);
	_genomesList.clear();
}
