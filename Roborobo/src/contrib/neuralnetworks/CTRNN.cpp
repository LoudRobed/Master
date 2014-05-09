/**
 * @file
 * @author Jean-Marc Montanier <montanier.jeanmarc@gmail.com>
 *
 *
 */

#include <neuralnetworks/CTRNN.h>
#include <sstream>
#include <iostream>

using namespace Neural;


/* --------------------- CTRNN --------------------- */

CTRNN::~CTRNN() {
	// ...
}

CTRNN::CTRNN(unsigned int nbInputs, unsigned int nbOutputs, unsigned int nbHiddenNeurons,
		double stepSize,
		unsigned int nbStep,
		boost::numeric::ublas::matrix<double> matrixWeights,
		boost::numeric::ublas::matrix<double> matrixWeightsInputs,
		boost::numeric::ublas::vector<double> biases,
		boost::numeric::ublas::vector<double> gains,
		boost::numeric::ublas::vector<double> taus,
		boost::numeric::ublas::vector<double> Rtaus) :
		RecurrentNeuralNetwork(nbInputs, nbOutputs,nbHiddenNeurons,matrixWeights,matrixWeightsInputs),
		_stepSize(stepSize),
		_nbStep(nbStep),
		_biases(biases),
		_gains(gains),
		_taus(taus),
		_Rtaus(Rtaus)
{
	if(_biases.size() != _size)
		throw "the size of biases doesn't match the number of neurons";

	if(_gains.size() != _size)
		throw "the size of gains doesn't match the number of neurons";

	if(_taus.size() != _size)
		throw "the size of taus doesn't match the number of neurons";

	if(_Rtaus.size() != _size)
		throw "the size of Rtaus doesn't match the number of neurons";
}

CTRNN::CTRNN(unsigned int nbInputs, unsigned int nbOutputs, unsigned int nbHiddenNeurons,
		double stepSize,
		unsigned int nbStep,
		boost::numeric::ublas::matrix<double> matrixWeights,
		boost::numeric::ublas::matrix<double> matrixWeightsInputs) :
		RecurrentNeuralNetwork(nbInputs, nbOutputs,nbHiddenNeurons,matrixWeights,matrixWeightsInputs),
		_stepSize(stepSize),
		_nbStep(nbStep)
{
	_biases.resize(_size);
	for (unsigned int i = 0; i < _biases.size (); ++ i)
	{
		_biases(i) = 0.0;
	}

	_gains.resize(_size);
	for (unsigned int i = 0; i < _gains.size (); ++ i)
	{
		_gains(i) = 0.0;
	}

	_taus.resize(_size);
	_Rtaus.resize(_size);
	for (unsigned int i = 0; i < _taus.size (); ++ i)
	{
		setNeuronTimeConstant(i , 0.0);
	}
}

CTRNN::CTRNN(unsigned int nbInputs, unsigned int nbOutputs, unsigned int nbHiddenNeurons,
		double stepSize,
		unsigned int nbStep) :
		RecurrentNeuralNetwork(nbInputs, nbOutputs,nbHiddenNeurons),
		_stepSize(stepSize),
		_nbStep(nbStep)
{
	_biases.resize(_size);
	for (unsigned int i = 0; i < _biases.size (); ++ i)
	{
		_biases(i) = 0.0;
	}

	_gains.resize(_size);
	for (unsigned int i = 0; i < _gains.size (); ++ i)
	{
		_gains(i) = 0.0;
	}

	_taus.resize(_size);
	_Rtaus.resize(_size);
	for (unsigned int i = 0; i < _taus.size (); ++ i)
	{
		setNeuronTimeConstant(i , 0.0);
	}
}

CTRNN::CTRNN(CTRNN const& other) : RecurrentNeuralNetwork(other) 
{
	_stepSize = other._stepSize;
	_nbStep = other._nbStep;
	_biases = other._biases;
	_gains = other._gains;
	_taus = other._taus;
	_Rtaus = other._Rtaus;
}

double CTRNN::sigmoid(double x)
{
	return 1.0/(1.0 + exp(-x));
}


double CTRNN::inverseSigmoid(double y)
{
  return log(y/(1-y));
}

//TODO: optimize with vector operation
void CTRNN::eulerStep()
{  
	for (unsigned int i = 0 ; i < _size ; i++) 
	{
		double input = 0.0;

		for (unsigned int j = 0 ; j < _nbInputs ; j++)
		{
			input += _matrixWeightsInputs(j,i) * _externalInputs(j);
		}

    for (unsigned int j = 0 ; j < _size ; j++)
		{
      input += _matrixWeights(j,i) * _outputs(j);
		}

    _states(i) += _stepSize * _Rtaus(i) * (input - _states(i));
  }

  // Update the outputs of all neurons.
  for (unsigned int i = 0 ; i < _size; i++)
	{
  	_outputs(i) = sigmoid( _gains(i) * ( _states(i) + _biases(i) ) );
	}
}

void CTRNN::step()
{
	for(unsigned int i = 0 ; i <= _nbStep ; i++)
	{
		eulerStep();
	}
}

void CTRNN::setParameters(std::vector<double> parameters)
{
	int parameterId = 0 ; 

	for (unsigned int i = 0; i < _matrixWeights.size1 (); ++ i)
	{
		for (unsigned int j = 0; j < _matrixWeights.size2 (); ++ j)
			_matrixWeights(i,j) = parameters[parameterId++];
	}

	for (unsigned int i = 0; i < _matrixWeightsInputs.size1 (); ++ i)
	{
		for (unsigned int j = 0; j < _matrixWeightsInputs.size2 (); ++ j)
			_matrixWeightsInputs(i,j) = parameters[parameterId++];
	}

	for (unsigned int i = 0; i < _biases.size (); ++ i)
	{
		_biases(i) = parameters[parameterId++];
	}

	for (unsigned int i = 0; i < _gains.size (); ++ i)
	{
		_gains(i) = parameters[parameterId++];
	}

	for (unsigned int i = 0; i < _taus.size (); ++ i)
	{
		setNeuronTimeConstant(i , parameters[parameterId++]);
	}
}

std::string CTRNN::toString() const 
{
	return RecurrentNeuralNetwork::toString();
}

void CTRNN::setNeuronBias(unsigned int neuron, double value)
{
	_biases(neuron) = value;
}

double CTRNN::getNeuronBias(unsigned int neuron)
{
	return _biases(neuron);
}

void CTRNN::setNeuronGain(unsigned int neuron, double value)
{
	_gains(neuron) = value;
}

double CTRNN::getNeuronGain(unsigned int neuron)
{
	return _gains(neuron);
}

void CTRNN::setNeuronTimeConstant(unsigned int neuron, double value)
{
	//heuristic: lower bond for a time constant at 0.1
	//note: having a too low time constant result in very high values during the computation of the status of the neurons

	if (value < 0.1) value = 0.1;
	_taus(neuron) = value;
	_Rtaus(neuron) = 1.0/value;
}

double CTRNN::getNeuronTimeConstant(unsigned int neuron)
{
	return _taus(neuron);
}

void CTRNN::setStepSize(double stepSize)
{
	_stepSize = stepSize;
}

void CTRNN::setNeuronOutput(unsigned int neuron, double value)
{
	_outputs(neuron) = value;
}

double CTRNN::getStepSize()
{
	return _stepSize;
}

void CTRNN::setNbStep(unsigned int nbStep)
{
	_nbStep = nbStep;
}

double CTRNN::getNbStep()
{
	return _nbStep;
}

unsigned int CTRNN::computeRequiredNumberOfWeights() 
{
		return (_nbInputs * _size) + (_size * _size);
}

int CTRNN::getNbParameters()
{
	int nbParameters = 0;
	//matrix weights
	nbParameters += _size * _size;
	//matrix weights from input
	nbParameters += _nbInputs * _size;
	//vector biases
	nbParameters += _size;
	//vector gains
	nbParameters += _size;
	//vector time constant (tau - Rau is set automatically)
	nbParameters += _size;

	return nbParameters;
}

std::string CTRNN::getNNTypeName() 
{
	return "CTRNN";
}

CTRNN* CTRNN::clone() const 
{
	return new CTRNN(*this);
}

