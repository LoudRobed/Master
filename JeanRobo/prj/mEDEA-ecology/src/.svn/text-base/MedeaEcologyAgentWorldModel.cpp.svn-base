/**
 * @file
 * @author Nicolas Bredeche <nicolas.bredeche@gmail.com>
 * 
 * History :
 *  - imported from medea-basic project on 16/6/2012
 *
 */


#include "mEDEA-ecology/include/MedeaEcologyAgentWorldModel.h"
#include "mEDEA-ecology/include/MedeaEcologyControlArchitecture.h"
#include <neuralnetworks/MLP.h>


using namespace Neural;


MedeaEcologyAgentWorldModel::MedeaEcologyAgentWorldModel()
{
}

MedeaEcologyAgentWorldModel::~MedeaEcologyAgentWorldModel()
{
}

double MedeaEcologyAgentWorldModel::getEnergyPointDirectionAngleValue()
{
	return _energyPointDirectionAngleValue;
}

double MedeaEcologyAgentWorldModel::getEnergyPointDistanceValue()
{
	return _energyPointDistanceValue;
}

void MedeaEcologyAgentWorldModel::setEnergyPointDirectionAngleValue( double value )
{
	_energyPointDirectionAngleValue = value;
}

void MedeaEcologyAgentWorldModel::setEnergyPointDistanceValue( double value )
{
	_energyPointDistanceValue = value;
}

bool MedeaEcologyAgentWorldModel::getActiveStatus()
{
	return _isActive;
}

void MedeaEcologyAgentWorldModel::setActiveStatus( bool isActive )
{
	_isActive = isActive;
}

double MedeaEcologyAgentWorldModel::getEnergyLevel()
{
	return _energyLevel;
}

void MedeaEcologyAgentWorldModel::setEnergyLevel(double inValue)
{
	_energyLevel = inValue;
}

double MedeaEcologyAgentWorldModel::getDeltaEnergy()
{
	return _deltaEnergy;
}

void MedeaEcologyAgentWorldModel::setDeltaEnergy(double inValue)
{
	_deltaEnergy = inValue;
}

void MedeaEcologyAgentWorldModel::setAngleToClosestEnergyPoint( double value )
{
	_angleToClosestEnergyPoint = value;
}

double MedeaEcologyAgentWorldModel::getAngleToClosestEnergyPoint()
{
	return _angleToClosestEnergyPoint;
}

void MedeaEcologyAgentWorldModel::setDistanceToClosestEnergyPoint( double value )
{
	_distanceToClosestEnergyPoint = value;
}

double MedeaEcologyAgentWorldModel::getDistanceToClosestEnergyPoint()
{
	return _distanceToClosestEnergyPoint;
}


void MedeaEcologyAgentWorldModel::resetActiveGenome()
{
	_nbInputs = _sensorCount + 4;
	_nbOutputs = 2;
	_nbHiddenLayers = 1;

	_nbNeuronsPerHiddenLayer = new std::vector<unsigned int>(_nbHiddenLayers);
	for(unsigned int i = 0; i < _nbHiddenLayers; i++)
		(*_nbNeuronsPerHiddenLayer)[i] = 5;

	unsigned int const nbGene = MedeaEcologyControlArchitecture::computeRequiredNumberOfWeights(this);

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

