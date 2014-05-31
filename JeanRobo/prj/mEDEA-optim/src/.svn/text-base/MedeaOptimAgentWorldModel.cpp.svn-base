/*
 *  MedeaOptimAgentWorldModel.cpp
 *
 *  Created by Nicolas on 19/1/2011
 *
 */

#include "mEDEA-optim/include/MedeaOptimAgentWorldModel.h"

MedeaOptimAgentWorldModel::MedeaOptimAgentWorldModel()
{
}

MedeaOptimAgentWorldModel::~MedeaOptimAgentWorldModel()
{
}

double MedeaOptimAgentWorldModel::getEnergyPointDirectionAngleValue()
{
	return _energyPointDirectionAngleValue;
}

double MedeaOptimAgentWorldModel::getEnergyPointDistanceValue()
{
	return _energyPointDistanceValue;
}

void MedeaOptimAgentWorldModel::setEnergyPointDirectionAngleValue( double __value )
{
	_energyPointDirectionAngleValue = __value;
}

void MedeaOptimAgentWorldModel::setEnergyPointDistanceValue( double __value )
{
	_energyPointDistanceValue = __value;
}

bool MedeaOptimAgentWorldModel::getActiveStatus()
{
	return _isActive;
}

void MedeaOptimAgentWorldModel::setActiveStatus( bool __isActive )
{
	_isActive = __isActive;
}

double MedeaOptimAgentWorldModel::getEnergyLevel()
{
	return _energyLevel;
}

void MedeaOptimAgentWorldModel::setEnergyLevel(double inValue)
{
	_energyLevel = inValue;
}

double MedeaOptimAgentWorldModel::getDeltaEnergy()
{
	return _deltaEnergy;
}

void MedeaOptimAgentWorldModel::setDeltaEnergy(double inValue)
{
	_deltaEnergy = inValue;
}

void MedeaOptimAgentWorldModel::setAngleToClosestEnergyPoint( double __value )
{
	_angleToClosestEnergyPoint = __value;
}

double MedeaOptimAgentWorldModel::getAngleToClosestEnergyPoint()
{
	return _angleToClosestEnergyPoint;
}
		
void MedeaOptimAgentWorldModel::setDistanceToClosestEnergyPoint( double __value )
{
	_distanceToClosestEnergyPoint = __value;
}

double MedeaOptimAgentWorldModel::getDistanceToClosestEnergyPoint()
{
	return _distanceToClosestEnergyPoint;
}

void MedeaOptimAgentWorldModel::setFitness( double __value )
{
	_fitnessValue = __value;
}

double MedeaOptimAgentWorldModel::getFitness()
{
	return _fitnessValue;
}

void MedeaOptimAgentWorldModel::resetActiveGenome()
{
	int nbInput = _sensorCount + 5 ; //sensors + floorSensor + energyDirection + energyLevel + energyDistance  +bias
	int nbOutput = 2 ; // rotation + velocity 
	int nbGene = ( nbInput * _nbHiddenNeurons ) + ( _nbHiddenNeurons * nbOutput) + nbOutput ; // from input to hidden layer + from hiddenLayer to output + from bias to output
	
	std::cout << std::flush ;
	
	_genome.clear();
	
	for ( int i = 0 ; i != nbGene ; i++ )
	{
		_genome.push_back(((rand()%800)/400.0)-1.0);
	}

	// Add special gene for MedeaOptim : gene_{convertToFitness_{ratio}}

	double range = _maxValue - _minValue;
	double value = ranf()*range-(range/2.0);  // ultimately defined btw _wm->_minValue and _wm->_maxValue, normalized btw 0 and 1 when using.
	_genome.push_back(value);

	//std::cout << "gene_cr = " << value << std::endl; // debug

	setNewGenomeStatus(true);
	
	_fitnessList.clear();
	_genomesList.clear();
	_sigmaList.clear();
	
//	if ( _agentId == gAgentIndexFocus ) // && gVerbose) // debug
//	{
//		std::cout << "!!! agent #" << gAgentIndexFocus << " reset.\n";
//	}
}
