/*
 *  MedeaAltUtilityAgentWorldModel.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 15/04/10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */

#include "mEDEA-altruism-utility/include/MedeaAltUtilityAgentWorldModel.h"

MedeaAltUtilityAgentWorldModel::MedeaAltUtilityAgentWorldModel()
{
	_energyHarvestingRate = 0.0;
	_totalEnergyHarvested = 0.0;
}

MedeaAltUtilityAgentWorldModel::~MedeaAltUtilityAgentWorldModel()
{
}

double MedeaAltUtilityAgentWorldModel::getEnergyPointDirectionAngleValue()
{
	return _energyPointDirectionAngleValue;
}

double MedeaAltUtilityAgentWorldModel::getEnergyPointDistanceValue()
{
	return _energyPointDistanceValue;
}

void MedeaAltUtilityAgentWorldModel::setEnergyPointDirectionAngleValue( double __value )
{
	_energyPointDirectionAngleValue = __value;
}

void MedeaAltUtilityAgentWorldModel::setEnergyPointDistanceValue( double __value )
{
	_energyPointDistanceValue = __value;
}

bool MedeaAltUtilityAgentWorldModel::getActiveStatus()
{
	return _isActive;
}

void MedeaAltUtilityAgentWorldModel::setActiveStatus( bool __isActive )
{
	_isActive = __isActive;
}

double MedeaAltUtilityAgentWorldModel::getEnergyLevel()
{
	return _energyLevel;
}

void MedeaAltUtilityAgentWorldModel::setEnergyLevel(double inValue)
{
	_energyLevel = inValue;
}

bool MedeaAltUtilityAgentWorldModel::getWaitingAfterLifeSynchronization()
{
	return _waitingAfterLifeSynchronization;
}

void MedeaAltUtilityAgentWorldModel::setWaitingAfterLifeSynchronization( bool isSynchronized )
{
	_waitingAfterLifeSynchronization = isSynchronized;
}

double MedeaAltUtilityAgentWorldModel::getDeltaEnergy()
{
	return _deltaEnergy;
}

void MedeaAltUtilityAgentWorldModel::setDeltaEnergy(double inValue)
{
	_deltaEnergy = inValue;
}

void MedeaAltUtilityAgentWorldModel::setAngleToClosestEnergyPoint( double __value )
{
	_angleToClosestEnergyPoint = __value;
}

double MedeaAltUtilityAgentWorldModel::getAngleToClosestEnergyPoint()
{
	return _angleToClosestEnergyPoint;
}
		
void MedeaAltUtilityAgentWorldModel::setDistanceToClosestEnergyPoint( double __value )
{
	_distanceToClosestEnergyPoint = __value;
}

double MedeaAltUtilityAgentWorldModel::getDistanceToClosestEnergyPoint()
{
	return _distanceToClosestEnergyPoint;
}

void MedeaAltUtilityAgentWorldModel::setEnergyHarvestingRate(double __energyHarvestingRate)
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

double MedeaAltUtilityAgentWorldModel::getEnergyHarvestingRate()
{
	return _energyHarvestingRate;
}

void MedeaAltUtilityAgentWorldModel::increaseTotalEnergyHarvested (double __value)
{
	if ( __value > 0.0 )
	{
		_totalEnergyHarvested += __value;
	}
}

void MedeaAltUtilityAgentWorldModel::resetTotalEnergyHarvested ()
{
	_totalEnergyHarvested = 0.0;
}

double MedeaAltUtilityAgentWorldModel::getTotalEnergyHarvested ()
{
	return _totalEnergyHarvested;
}

void MedeaAltUtilityAgentWorldModel::resetActiveGenome()
{
	int nbInput = _sensorCount + 5 ; //sensors + floorSensor + energyDirection + energyLevel + energyDistance  +bias
	int nbOutput = 3 ; // rotation + velocity + energyHarvestingRate
	int nbGene = ( nbInput * _nbHiddenNeurons ) + ( _nbHiddenNeurons * nbOutput) + nbOutput ; // from input to hidden layer + from hiddenLayer to output + from bias to output
	std::cout << std::flush ;
	_genome.clear();
	for ( int i = 0 ; i != nbGene ; i++ )
	{
		_genome.push_back(((rand()%800)/400.0)-1.0);
	}
	_currentGenome = _genome;
	setNewGenomeStatus(true);
	_genomesList.clear();
}
