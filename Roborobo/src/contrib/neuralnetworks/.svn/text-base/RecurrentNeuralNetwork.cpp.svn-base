/**
 * @file
 * @author Jean-Marc Montanier <montanier.jeanmarc@gmail.com>
 *
 *
 */

#include <neuralnetworks/RecurrentNeuralNetwork.h>
#include <sstream>
#include <iostream>

using namespace Neural;


/* --------------------- RecurrentNeuralNetwork --------------------- */

RecurrentNeuralNetwork::~RecurrentNeuralNetwork() {
	// ...
}

RecurrentNeuralNetwork::RecurrentNeuralNetwork(unsigned int nbInputs, unsigned int nbOutputs, unsigned int nbHiddenNeurons) :
		NeuralNetwork(nbInputs, nbOutputs),
		_nbHiddenNeurons(nbHiddenNeurons)
{
	_size = nbOutputs + nbHiddenNeurons;
	_states.resize(_size);
	for (unsigned int i = 0; i < _states.size (); ++ i)
	{
		_states(i) = 0.0;
	}

	_outputs.resize(_size);
	for (unsigned int i = 0; i < _outputs.size (); ++ i)
	{
		_outputs(i) = 0.0;
	}

	_externalInputs.resize(nbInputs);
	for (unsigned int i = 0; i < _externalInputs.size (); ++ i)
	{
		_externalInputs(i) = 0.0;
	}

	_matrixWeights.resize(_size,_size);
	for (unsigned int i = 0; i < _matrixWeights.size1 (); ++ i)
	{
		for (unsigned int j = 0; j < _matrixWeights.size2 (); ++ j)
			_matrixWeights(i,j) = 0.0;
	}

	_matrixWeightsInputs.resize(nbInputs,_size);
	for (unsigned int i = 0; i < _matrixWeightsInputs.size1 (); ++ i)
	{
		for (unsigned int j = 0; j < _matrixWeightsInputs.size2 (); ++ j)
			_matrixWeightsInputs(i,j) = 0.0;
	}

	if(_size == 0)
		throw "nbNeurons cannot be 0";
}

RecurrentNeuralNetwork::RecurrentNeuralNetwork(unsigned int nbInputs, unsigned int nbOutputs, unsigned int nbHiddenNeurons,
		boost::numeric::ublas::matrix<double> matrixWeights,
		boost::numeric::ublas::matrix<double> matrixWeightsInputs) :
		NeuralNetwork(nbInputs, nbOutputs),
		_matrixWeights(matrixWeights),
		_matrixWeightsInputs(matrixWeightsInputs),
		_nbHiddenNeurons(nbHiddenNeurons)
{
	_size = nbOutputs + nbHiddenNeurons;
	_states.resize(_size);
	for (unsigned int i = 0; i < _states.size (); ++ i)
	{
		_states(i) = 0.0;
	}

	_outputs.resize(_size);
	for (unsigned int i = 0; i < _outputs.size (); ++ i)
	{
		_outputs(i) = 0.0;
	}

	_externalInputs.resize(nbInputs);
	for (unsigned int i = 0; i < _externalInputs.size (); ++ i)
	{
		_externalInputs(i) = 0.0;
	}
	
	if(_size == 0)
		throw "nbNeurons cannot be 0";
}


RecurrentNeuralNetwork::RecurrentNeuralNetwork(RecurrentNeuralNetwork const& other) : NeuralNetwork(other) {
	_nbHiddenNeurons = other._nbHiddenNeurons;
	_matrixWeights = other._matrixWeights;
}

void RecurrentNeuralNetwork::setConnectionWeight(unsigned int from, unsigned int to, double weight)
{
	_matrixWeights(from,to) = weight;
}

double RecurrentNeuralNetwork::getConnectionWeight(unsigned int from, unsigned int to)
{
	return _matrixWeights(from,to);
}

void RecurrentNeuralNetwork::setConnectionWeightInput(unsigned int from, unsigned int to, double weight)
{
	_matrixWeightsInputs(from,to) = weight;
}

double RecurrentNeuralNetwork::getConnectionWeightInput(unsigned int from, unsigned int to)
{
	return _matrixWeightsInputs(from,to);
}


void RecurrentNeuralNetwork::setNeuronExternalInput(unsigned int neuron, double value)
{
	_externalInputs(neuron) = value;
}

double RecurrentNeuralNetwork::getNeuronExternalInput(unsigned int neuron)
{
	return _externalInputs(neuron);
}

void RecurrentNeuralNetwork::setNeuronState(unsigned int neuron, double value)
{
	_states(neuron) = value;
}

double RecurrentNeuralNetwork::getNeuronState(unsigned int neuron)
{
	return _states(neuron);
}

double RecurrentNeuralNetwork::getNeuronOutput(unsigned int neuron)
{
	return _outputs(neuron);
}

std::string RecurrentNeuralNetwork::toString() const 
{
	return NeuralNetwork::toString();
}
