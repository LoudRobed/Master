/**
 * @file
 * @author Leo Cazenille <leo.cazenille@gmail.com>
 * TODO : Add formal description
 * History :
 *
 *
 */

#include "mEDEA-HGT/include/MedeaHGTAgentWorldModel.h"
#include "mEDEA-HGT/include/MedeaHGTNNControlArchitecture.h"
#include <neuralnetworks/MLP.h>


using namespace Neural;


MedeaHGTAgentWorldModel::MedeaHGTAgentWorldModel()
{
}

MedeaHGTAgentWorldModel::~MedeaHGTAgentWorldModel()
{
}

double MedeaHGTAgentWorldModel::getEnergyPointDirectionAngleValue()
{
	return _energyPointDirectionAngleValue;
}

double MedeaHGTAgentWorldModel::getEnergyPointDistanceValue()
{
	return _energyPointDistanceValue;
}

void MedeaHGTAgentWorldModel::setEnergyPointDirectionAngleValue( double value )
{
	_energyPointDirectionAngleValue = value;
}

void MedeaHGTAgentWorldModel::setEnergyPointDistanceValue( double value )
{
	_energyPointDistanceValue = value;
}

bool MedeaHGTAgentWorldModel::getActiveStatus()
{
	return _isActive;
}

void MedeaHGTAgentWorldModel::setActiveStatus( bool isActive )
{
	_isActive = isActive;
}

double MedeaHGTAgentWorldModel::getEnergyLevel()
{
	return _energyLevel;
}

void MedeaHGTAgentWorldModel::setEnergyLevel(double inValue)
{
	_energyLevel = inValue;
}

double MedeaHGTAgentWorldModel::getDeltaEnergy()
{
	return _deltaEnergy;
}

void MedeaHGTAgentWorldModel::setDeltaEnergy(double inValue)
{
	_deltaEnergy = inValue;
}

void MedeaHGTAgentWorldModel::setAngleToClosestEnergyPoint( double value )
{
	_angleToClosestEnergyPoint = value;
}

double MedeaHGTAgentWorldModel::getAngleToClosestEnergyPoint()
{
	return _angleToClosestEnergyPoint;
}

void MedeaHGTAgentWorldModel::setDistanceToClosestEnergyPoint( double value )
{
	_distanceToClosestEnergyPoint = value;
}

double MedeaHGTAgentWorldModel::getDistanceToClosestEnergyPoint()
{
	return _distanceToClosestEnergyPoint;
}

void MedeaHGTAgentWorldModel::setPopulationID(int populationId) {
	_populationID = populationId;
}

int MedeaHGTAgentWorldModel::getPopulationID() {
	return _populationID;
}

void MedeaHGTAgentWorldModel::setEncounteredAgentsDuringGeneration(int encounteredAgentsDuringGeneration) {
	_encounteredAgentsDuringGeneration = encounteredAgentsDuringGeneration;
}

int MedeaHGTAgentWorldModel::getEncounteredAgentsDuringGeneration() {
	return _encounteredAgentsDuringGeneration;
}

void MedeaHGTAgentWorldModel::resetActiveGenome()
{
	_nbInputs = _sensorCount + 4;
	_nbOutputs = 2;
	_nbHiddenLayers = 1;

	_nbNeuronsPerHiddenLayer = new std::vector<unsigned int>(_nbHiddenLayers);
	for(unsigned int i = 0; i < _nbHiddenLayers; i++)
		(*_nbNeuronsPerHiddenLayer)[i] = 5;

	unsigned int const nbGene = MedeaHGTNNControlArchitecture::computeRequiredNumberOfWeights(this);

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

