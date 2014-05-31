/*
 *  MedeaAltruismAgentWorldModel.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 15/04/10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */

#include "mEDEA-altruism/include/MedeaAltruismAgentWorldModel.h"

MedeaAltruismAgentWorldModel::MedeaAltruismAgentWorldModel()
{
	_dateOfBirth=0;
	_waitForGenome=false;
	_fatherId=-1;
	_lifeTime = 1;
	_energyHarvestingRate = 0.0;
	_idlenessTracker.reset();
}

MedeaAltruismAgentWorldModel::~MedeaAltruismAgentWorldModel()
{
}

double MedeaAltruismAgentWorldModel::getEnergyPointDirectionAngleValue()
{
	return _energyPointDirectionAngleValue;
}

double MedeaAltruismAgentWorldModel::getEnergyPointDistanceValue()
{
	return _energyPointDistanceValue;
}

void MedeaAltruismAgentWorldModel::setEnergyPointDirectionAngleValue( double __value )
{
	_energyPointDirectionAngleValue = __value;
}

void MedeaAltruismAgentWorldModel::setEnergyPointDistanceValue( double __value )
{
	_energyPointDistanceValue = __value;
}

bool MedeaAltruismAgentWorldModel::getActiveStatus()
{
	return _isActive;
}

void MedeaAltruismAgentWorldModel::setActiveStatus( bool __isActive )
{
	_isActive = __isActive;
}

double MedeaAltruismAgentWorldModel::getEnergyLevel()
{
	return _energyLevel;
}

void MedeaAltruismAgentWorldModel::setEnergyLevel(double inValue)
{
	_energyLevel = inValue;
}

double MedeaAltruismAgentWorldModel::getDeltaEnergy()
{
	return _deltaEnergy;
}

void MedeaAltruismAgentWorldModel::setDeltaEnergy(double inValue)
{
	_deltaEnergy = inValue;
}

void MedeaAltruismAgentWorldModel::setAngleToClosestEnergyPoint( double __value )
{
	_angleToClosestEnergyPoint = __value;
}

double MedeaAltruismAgentWorldModel::getAngleToClosestEnergyPoint()
{
	return _angleToClosestEnergyPoint;
}
		
void MedeaAltruismAgentWorldModel::setDistanceToClosestEnergyPoint( double __value )
{
	_distanceToClosestEnergyPoint = __value;
}

double MedeaAltruismAgentWorldModel::getDistanceToClosestEnergyPoint()
{
	return _distanceToClosestEnergyPoint;
}

void MedeaAltruismAgentWorldModel::setEnergyHarvestingRate(double __energyHarvestingRate)
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

double MedeaAltruismAgentWorldModel::getEnergyHarvestingRate()
{
	return _energyHarvestingRate;
}

void MedeaAltruismAgentWorldModel::setFatherId(int fathId)
{
	_fatherId = fathId;	
}

int MedeaAltruismAgentWorldModel::getFatherId()
{
	return _fatherId ;	
}

void MedeaAltruismAgentWorldModel::setMaturity(int maturity)
{
	_maturity = maturity;
}

int MedeaAltruismAgentWorldModel::getMaturity()
{
	return _maturity ;
}

void MedeaAltruismAgentWorldModel::setDateOfBirth(int dateOfBirth)
{
	_dateOfBirth = dateOfBirth;
}

int MedeaAltruismAgentWorldModel::getDateOfBirth()
{
	return _dateOfBirth ;	
}

void MedeaAltruismAgentWorldModel::setLifeTime(int lifeTime)
{
    _lifeTime = lifeTime;
}

int MedeaAltruismAgentWorldModel::getLifeTime()
{
    return _lifeTime;   
}

void MedeaAltruismAgentWorldModel::setWaitForGenome(bool wait)
{
    _waitForGenome = wait;
}

bool MedeaAltruismAgentWorldModel::getWaitForGenome()
{
    return _waitForGenome;
}


void MedeaAltruismAgentWorldModel::resetActiveGenome()
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


//TODO : recode ReEvo
//for compatibility issue with ReEvo
void MedeaAltruismAgentWorldModel::setWaitingAfterLifeSynchronization(bool isSynchronized)
{
	//nothing
}

//for compatibility issue with ReEvo
bool MedeaAltruismAgentWorldModel::getWaitingAfterLifeSynchronization()
{
	return false;
}
