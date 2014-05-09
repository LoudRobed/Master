/*
 *  MedeaAggregationAgentWorldModel.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 15/04/10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */

#include "mEDEA-aggregation/include/MedeaAggregationAgentWorldModel.h"

MedeaAggregationAgentWorldModel::MedeaAggregationAgentWorldModel()
{
	_dateOfBirth=0;
	_fatherId=-1;
	_lifeTime = 1;
	_energyHarvestingRate = 0.0;
	_status = ACTIVE;
	_idlenessTracker.reset();
}

MedeaAggregationAgentWorldModel::~MedeaAggregationAgentWorldModel()
{
}

double MedeaAggregationAgentWorldModel::getEnergyPointDirectionAngleValue()
{
	return _energyPointDirectionAngleValue;
}

double MedeaAggregationAgentWorldModel::getEnergyPointDistanceValue()
{
	return _energyPointDistanceValue;
}

double MedeaAggregationAgentWorldModel::getEnergyPointType()
{
	return _energyPointType;
}

void MedeaAggregationAgentWorldModel::setEnergyPointDirectionAngleValue( double __value )
{
	_energyPointDirectionAngleValue = __value;
}

void MedeaAggregationAgentWorldModel::setEnergyPointDistanceValue( double __value )
{
	_energyPointDistanceValue = __value;
}

void MedeaAggregationAgentWorldModel::setEnergyPointType( double __value )
{
	_energyPointType = __value;
}

int MedeaAggregationAgentWorldModel::getStatus()
{
	return _status;
}

void MedeaAggregationAgentWorldModel::setStatus( int __status )
{
	_status = __status;
}

double MedeaAggregationAgentWorldModel::getEnergyLevel()
{
	return _energyLevel;
}

void MedeaAggregationAgentWorldModel::setEnergyLevel(double inValue)
{
	_energyLevel = inValue;
}

double MedeaAggregationAgentWorldModel::getDeltaEnergy()
{
	return _deltaEnergy;
}

void MedeaAggregationAgentWorldModel::setDeltaEnergy(double inValue)
{
	_deltaEnergy = inValue;
}

void MedeaAggregationAgentWorldModel::setAngleToClosestEnergyPoint( double __value )
{
	_angleToClosestEnergyPoint = __value;
}

double MedeaAggregationAgentWorldModel::getAngleToClosestEnergyPoint()
{
	return _angleToClosestEnergyPoint;
}
		
void MedeaAggregationAgentWorldModel::setDistanceToClosestEnergyPoint( double __value )
{
	_distanceToClosestEnergyPoint = __value;
}

double MedeaAggregationAgentWorldModel::getDistanceToClosestEnergyPoint()
{
	return _distanceToClosestEnergyPoint;
}

void MedeaAggregationAgentWorldModel::setEnergyHarvestingRate(double __energyHarvestingRate)
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

double MedeaAggregationAgentWorldModel::getEnergyHarvestingRate()
{
	return _energyHarvestingRate;
}

void MedeaAggregationAgentWorldModel::setFatherId(int fathId)
{
	_fatherId = fathId;	
}

int MedeaAggregationAgentWorldModel::getFatherId()
{
	return _fatherId ;	
}

void MedeaAggregationAgentWorldModel::setMaturity(int maturity)
{
	_maturity = maturity;
}

int MedeaAggregationAgentWorldModel::getMaturity()
{
	return _maturity ;
}

void MedeaAggregationAgentWorldModel::setDateOfBirth(int dateOfBirth)
{
	_dateOfBirth = dateOfBirth;
}

int MedeaAggregationAgentWorldModel::getDateOfBirth()
{
	return _dateOfBirth ;	
}

void MedeaAggregationAgentWorldModel::setLifeTime(int lifeTime)
{
    _lifeTime = lifeTime;
}

int MedeaAggregationAgentWorldModel::getLifeTime()
{
    return _lifeTime;   
}

void MedeaAggregationAgentWorldModel::resetActiveGenome(int nbGene)
{
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
void MedeaAggregationAgentWorldModel::setWaitingAfterLifeSynchronization(bool isSynchronized)
{
	//nothing
}

//for compatibility issue with ReEvo
bool MedeaAggregationAgentWorldModel::getWaitingAfterLifeSynchronization()
{
	return false;
}


void MedeaAggregationAgentWorldModel::setUpGripper(GripperConnectionMechanism* gripper)
{
	_connection = gripper;
}

void MedeaAggregationAgentWorldModel::setGripperStatus(int status)
{
	_connection->setArmState(status);
}

int MedeaAggregationAgentWorldModel::getGripperStatus()
{
	return _connection->getArmState();
}

void MedeaAggregationAgentWorldModel::setFirstStep (bool firstStep)
{
	_firstStep = firstStep;
}

bool MedeaAggregationAgentWorldModel::getFirstStep()
{
	return _firstStep;
}

bool MedeaAggregationAgentWorldModel::getNewGenomeStatus()
{
	return _isNewGenome;
}

void MedeaAggregationAgentWorldModel::setNewGenomeStatus( bool __status )
{
	_isNewGenome = __status;
}
