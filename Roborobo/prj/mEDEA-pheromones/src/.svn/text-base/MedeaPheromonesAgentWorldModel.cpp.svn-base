/**
 * @file
 * @author Nicolas Bredeche <nicolas.bredeche@gmail.com>
 * 
 * History :
 *  - imported from medea-basic project on 16/6/2012
 *
 */

#include "mEDEA-pheromones/include/MedeaPheromonesAgentWorldModel.h"
#include "mEDEA-pheromones/include/MedeaPheromonesControlArchitecture.h"
#include <neuralnetworks/MLP.h>


using namespace Neural;


MedeaPheromonesAgentWorldModel::MedeaPheromonesAgentWorldModel()
{
}

MedeaPheromonesAgentWorldModel::~MedeaPheromonesAgentWorldModel()
{
}

double MedeaPheromonesAgentWorldModel::getEnergyPointDirectionAngleValue()
{
	return _energyPointDirectionAngleValue;
}

double MedeaPheromonesAgentWorldModel::getEnergyPointDistanceValue()
{
	return _energyPointDistanceValue;
}

void MedeaPheromonesAgentWorldModel::setEnergyPointDirectionAngleValue( double value )
{
	_energyPointDirectionAngleValue = value;
}

void MedeaPheromonesAgentWorldModel::setEnergyPointDistanceValue( double value )
{
	_energyPointDistanceValue = value;
}

bool MedeaPheromonesAgentWorldModel::getActiveStatus()
{
	return _isActive;
}

void MedeaPheromonesAgentWorldModel::setActiveStatus( bool isActive )
{
	_isActive = isActive;
}

double MedeaPheromonesAgentWorldModel::getEnergyLevel()
{
	return _energyLevel;
}

void MedeaPheromonesAgentWorldModel::setEnergyLevel(double inValue)
{
	_energyLevel = inValue;
}

double MedeaPheromonesAgentWorldModel::getDeltaEnergy()
{
	return _deltaEnergy;
}

void MedeaPheromonesAgentWorldModel::setDeltaEnergy(double inValue)
{
	_deltaEnergy = inValue;
}

void MedeaPheromonesAgentWorldModel::setAngleToClosestEnergyPoint( double value )
{
	_angleToClosestEnergyPoint = value;
}

double MedeaPheromonesAgentWorldModel::getAngleToClosestEnergyPoint()
{
	return _angleToClosestEnergyPoint;
}

void MedeaPheromonesAgentWorldModel::setDistanceToClosestEnergyPoint( double value )
{
	_distanceToClosestEnergyPoint = value;
}

double MedeaPheromonesAgentWorldModel::getDistanceToClosestEnergyPoint()
{
	return _distanceToClosestEnergyPoint;
}


void MedeaPheromonesAgentWorldModel::resetActiveGenome()
{
	_nbInputs = _sensorCount + 4;
	_nbOutputs = 2;
	_nbHiddenLayers = 1;

	_nbNeuronsPerHiddenLayer = new std::vector<unsigned int>(_nbHiddenLayers);
	for(unsigned int i = 0; i < _nbHiddenLayers; i++)
		(*_nbNeuronsPerHiddenLayer)[i] = 5;

	unsigned int const nbGene = MedeaPheromonesControlArchitecture::computeRequiredNumberOfWeights(this);

	std::cout << std::flush ;
	_genome.clear();
	for ( unsigned int i = 0 ; i != nbGene ; i++ )
	{
		_genome.push_back(((rand()%800)/400.0)-1.0);
	}
	_currentGenome = _genome;
	setNewGenomeStatus(true);
	_genomesList.clear();
}

