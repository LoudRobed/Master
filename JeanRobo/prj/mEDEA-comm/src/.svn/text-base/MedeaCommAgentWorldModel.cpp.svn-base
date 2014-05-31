/*
 *  MedeaCommAgentWorldModel.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 15/04/10.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */

#include "mEDEA-comm/include/MedeaCommAgentWorldModel.h"

MedeaCommAgentWorldModel::MedeaCommAgentWorldModel()
{
	_dateOfBirth=0;
	_waitForGenome=false;
	_fatherId=-1;
	_lifeTime = 1;
	_isInContest = false;
	_energyLevel = MedeaCommSharedData::gEnergyInit;
	_desiredTranslationalValue = 0.0;
	_desiredRotationalVelocity = 0.0;
	_communication = 0 ;
}

MedeaCommAgentWorldModel::~MedeaCommAgentWorldModel()
{
}

bool MedeaCommAgentWorldModel::getActiveStatus()
{
	return _isActive;
}

void MedeaCommAgentWorldModel::setActiveStatus( bool __isActive )
{
	_isActive = __isActive;
}

double MedeaCommAgentWorldModel::getEnergyLevel()
{
	return _energyLevel;
}

void MedeaCommAgentWorldModel::setEnergyLevel(double inValue)
{
	_energyLevel = inValue;
}

double MedeaCommAgentWorldModel::getDeltaEnergy()
{
	return _deltaEnergy;
}

void MedeaCommAgentWorldModel::setDeltaEnergy(double inValue)
{
	_deltaEnergy = inValue;
}

void MedeaCommAgentWorldModel::setAngleToClosestEnergyPoint( double __value )
{
	_angleToClosestEnergyPoint = __value;
}

double MedeaCommAgentWorldModel::getAngleToClosestEnergyPoint()
{
	return _angleToClosestEnergyPoint;
}
		
void MedeaCommAgentWorldModel::setDistanceToClosestEnergyPoint( double __value )
{
	_distanceToClosestEnergyPoint = __value;
}

double MedeaCommAgentWorldModel::getDistanceToClosestEnergyPoint()
{
	return _distanceToClosestEnergyPoint;
}

void MedeaCommAgentWorldModel::setAction( double __value )
{
	_action = __value;
}

double MedeaCommAgentWorldModel::getAction ()
{
	return _action;
}

void MedeaCommAgentWorldModel::setReceivedCommunication( std::vector<double> __value )
{
	_receivedCommunication = __value;
}

std::vector<double> MedeaCommAgentWorldModel::getReceivedCommunication ()
{
	return _receivedCommunication;
}

void MedeaCommAgentWorldModel::setCommunication( double __value )
{
	_communication = __value;
}

double MedeaCommAgentWorldModel::getCommunication ()
{
	return _communication;
}

void MedeaCommAgentWorldModel::setIsInContest( bool __value )
{
	_isInContest = __value;
}

bool MedeaCommAgentWorldModel::getIsInContest ()
{
	return _isInContest;
}

void MedeaCommAgentWorldModel::setFatherId(int fathId)
{
	_fatherId = fathId;	
}

int MedeaCommAgentWorldModel::getFatherId()
{
	return _fatherId ;
}

void MedeaCommAgentWorldModel::setMaturity(int maturity)
{
	_maturity = maturity;
}

int MedeaCommAgentWorldModel::getMaturity()
{
	return _maturity ;
}

void MedeaCommAgentWorldModel::setDateOfBirth(int dateOfBirth)
{
	_dateOfBirth = dateOfBirth;
}

int MedeaCommAgentWorldModel::getDateOfBirth()
{
	return _dateOfBirth ;	
}

void MedeaCommAgentWorldModel::setLifeTime(int lifeTime)
{
    _lifeTime = lifeTime;
}

int MedeaCommAgentWorldModel::getLifeTime()
{
    return _lifeTime;   
}

void MedeaCommAgentWorldModel::setWaitForGenome(bool wait)
{
    _waitForGenome = wait;
}

bool MedeaCommAgentWorldModel::getWaitForGenome()
{
    return _waitForGenome;
}

void MedeaCommAgentWorldModel::resetActiveGenome()
{
	int nbInput = _sensorCount + 5 + MedeaCommSharedData::nbReceptionSector ; //sensors + floorSensor + energyDirection + energyDistance + energyLevel + bias + reception
	int nbOutput = 4 ; // rotation + velocity + action + communication
	int nbGene = ( nbInput * _nbHiddenNeurons ) + ( _nbHiddenNeurons * nbOutput) + nbOutput ; // from input to hidden layer + from hiddenLayer to output + from bias to output
	_currentGenome.clear();
	for ( int i = 0 ; i != nbGene ; i++ )
	{
		_currentGenome.push_back(((rand()%800)/400.0)-1.0);
	}
	setNewGenomeStatus(true);
	_genomesList.clear();
}
