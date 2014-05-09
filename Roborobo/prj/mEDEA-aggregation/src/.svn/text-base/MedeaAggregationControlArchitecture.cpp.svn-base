/*
 *  MedeaAggregationControlArchitecture.cpp
 *  roborobo-online
 *
 *  imported from Jean-Marc on 21/12/09
 *  current dev: Nicolas on 1/4/2009
 *  moved in altruism by Jean-Marc on 17/09/2010
 *  modification by Jean-Marc on 24/22/2013 : 
 *    - add the possibity to use also CTRNN from neuralnetworks contrib
 *
 */

#include "mEDEA-aggregation/include/MedeaAggregationControlArchitecture.h"
#include "World/World.h"
#include "Utilities/Misc.h"
#include <math.h>

#include <neuralnetworks/CTRNN.h>

MedeaAggregationControlArchitecture::MedeaAggregationControlArchitecture( RobotAgentWorldModel *__wm )
{
	_wm = (MedeaAggregationAgentWorldModel*)__wm;
	_iteration = 0;
	
	_wm->setEnergyLevel(MedeaAggregationSharedData::gEnergyInit);
	_wm->setDeltaEnergy(0.0);

	_wm->setAngleToClosestEnergyPoint(0);
	_wm->setDistanceToClosestEnergyPoint(0);

	gProperties.checkAndGetPropertyValue("nbHiddenNeurons",&_wm->_nbHiddenNeurons,true);
	gProperties.checkAndGetPropertyValue("networkType",&_nnType,true);
	gProperties.checkAndGetPropertyValue("visibleTypeEP",&_typeEP,true);
	if(_typeEP == true)
	{
		//inputs : distance sensors + floor sensor + distance to energy point + angle to energy point + type of energy point + level of energy
		_wm->_nbInputs = _wm->_sensorCount+5;
	}
	else
	{
		//inputs : distance sensors + floor sensor + distance to energy point + angle to energy point + level of energy
		_wm->_nbInputs = _wm->_sensorCount+4;
	}
	createNN();
	
	_wm->setStatus(MedeaAggregationAgentWorldModel::ACTIVE);

	if ( gVerbose )
	{
		std::cout << "robot #" << _wm->_agentId << " perceptron \n" ;	
	}
}

MedeaAggregationControlArchitecture::~MedeaAggregationControlArchitecture()
{
	// nothing to do.
}

void MedeaAggregationControlArchitecture::createNN()
{
	if (_nnType.compare("CTRNN") == 0)
	{
		nn = new Neural::CTRNN(_wm->_nbInputs,3,_wm->_nbHiddenNeurons,0.1,10);
		_wm->_nbGenes = dynamic_cast<Neural::CTRNN*> (nn)->getNbParameters();
	}
	else
	{
		int nbOutput = 3 ; // rotation + velocity + gripper command
		_wm->_nbGenes = ( (_wm->_nbInputs + 1) * _wm->_nbHiddenNeurons ) + ( _wm->_nbHiddenNeurons * nbOutput) + nbOutput ; // from input to hidden layer + from hiddenLayer to output + from bias to output
		nn = NULL;
	}
	_wm->resetActiveGenome(_wm->_nbGenes);
}

void MedeaAggregationControlArchitecture::reset()
{
	_parameters.clear();
	_parameters = _wm->_currentGenome;
}


// perform one controller update
// set motor value using motor format.
void MedeaAggregationControlArchitecture::step()
{
	_iteration++;

	if ( _wm->getNewGenomeStatus() ) // check for new NN parameters
	{
		reset();
		_wm->setNewGenomeStatus(false);
	}

	if ( _wm->getStatus() == MedeaAggregationAgentWorldModel::ACTIVE )
	{

		if ( gVerbose && gInspectAgent && gAgentIndexFocus == _wm->_agentId )
		{
			std::cout << "tgt.in: " << _wm->getAngleToClosestEnergyPoint() << std::endl;// " (" << _wm->_agentAbsoluteOrientation << "," << angleToClosestEnergyPoint << ")" << std::endl;
		}

		_wm->_desiredTranslationalValue = 0.0;
		_wm->_desiredRotationalVelocity = 0.0;
	
		if (_nnType.compare("CTRNN") == 0)
		{
			//set the weights
			Neural::CTRNN* ctrnn = dynamic_cast<Neural::CTRNN*> (nn);
			ctrnn->setParameters(_parameters);

			//set the inputs
			int inputToUse = 0;
			for ( int inputToUse = 0 ; inputToUse < _wm->_sensorCount ; inputToUse++ )
			{
				ctrnn->setNeuronExternalInput(inputToUse,_wm->getSensorDistanceValue(inputToUse)/_wm->getSensorMaximumDistanceValue(inputToUse));
			}

			if(_wm->_floorSensor != 0)
				ctrnn->setNeuronExternalInput(inputToUse++, 1.0);
			else
				ctrnn->setNeuronExternalInput(inputToUse++, 0.0);
			// direction of the closest energy point
			ctrnn->setNeuronExternalInput(inputToUse++, _wm->getEnergyPointDirectionAngleValue());
			// direction of the closest energy point
			ctrnn->setNeuronExternalInput(inputToUse++, _wm->getEnergyPointDistanceValue());
			// type of energy point ahead
			if (_typeEP == true)
			{
				ctrnn->setNeuronExternalInput(inputToUse++, _wm->getEnergyPointType());
			}
			// energy level
			ctrnn->setNeuronExternalInput(inputToUse++, _wm->getEnergyLevel() / MedeaAggregationSharedData::gEnergyMax);

			ctrnn->step();

			//outputs 
			_wm->_desiredTranslationalValue = ctrnn->getNeuronOutput(0)*2.0-1.0;
			_wm->_desiredRotationalVelocity = ctrnn->getNeuronOutput(1)*2.0-1.0;

			// normalize to motor interval values
			_wm->_desiredTranslationalValue = _wm->_desiredTranslationalValue * gMaxTranslationalSpeed;
			_wm->_desiredRotationalVelocity = _wm->_desiredRotationalVelocity * gMaxRotationalSpeed;

			// normalize to motor interval values

			double commandGripper = ctrnn->getNeuronOutput(2);
			//apply the output value
			if (commandGripper < 0.5)
			{
				_wm->setGripperStatus(GripperConnectionMechanism::LOW);
			}
			else
			{
				_wm->setGripperStatus(GripperConnectionMechanism::HIGH);
			}

			_wm->setEnergyHarvestingRate(1.0);
		}
		else
		{
			perceptronStep();
		}
		
	}
}

void MedeaAggregationControlArchitecture::perceptronStep()
{

		std::vector<double> hiddenLayer;
		hiddenLayer.resize(_wm->_nbHiddenNeurons);
		for (int j= 0 ; j < _wm->_nbHiddenNeurons ; j++ )
		{
			hiddenLayer[j] = 0.0;
		}
		int geneToUse = 0;
		// ---- Build inputs ----

		// distance sensors
		for ( int i = 0 ; i < _wm->_sensorCount ; i++ )
		{
			for (int j= 0 ; j < _wm->_nbHiddenNeurons ; j++ )
			{
				// BUG: hiddenLayer[j] += tanh(_wm->_sensorCount) * _parameters[geneToUse] ;  // ??? !N - BUG di0319 !n -- sensor are NOT taken into account!
				hiddenLayer[j] += (_wm->getSensorDistanceValue(i)/_wm->getSensorMaximumDistanceValue(i)) * _parameters[geneToUse] ;  // !N - corrected BUG di0319 - use normalized sensor value in 0...1
				geneToUse ++;
			}
		}

		//floor sensor
		for (int j= 0 ; j < _wm->_nbHiddenNeurons ; j++ )
		{
			if ( _wm->_floorSensor != 0 )		// binary detector -- either something, or nothing.
				hiddenLayer[j] += 1.0  * _parameters[geneToUse];
			//hiddenLayer[j] += _wm->_floorSensor/255.0  * _parameters[geneToUse];
			geneToUse ++;
		}

		//direction of the closest energy point
		for (int j= 0 ; j < _wm->_nbHiddenNeurons ; j++ )
		{
			hiddenLayer[j] += _wm->getAngleToClosestEnergyPoint()  * _parameters[geneToUse];		
			geneToUse ++;
		}

		//distance to the closest energy point 
		for (int j= 0 ; j < _wm->_nbHiddenNeurons ; j++ )
		{
			hiddenLayer[j] += _wm->getDistanceToClosestEnergyPoint()  * _parameters[geneToUse]; 
			geneToUse ++;
		}

		// type of energy point ahead
		if (_typeEP == true)
		{
			for (int j= 0 ; j < _wm->_nbHiddenNeurons ; j++ )
			{
				hiddenLayer[j] +=  _wm->getEnergyPointType() * _parameters[geneToUse]; 
				geneToUse ++;
			}
		}

		//energy level
		for (int j= 0 ; j < _wm->_nbHiddenNeurons ; j++ )
		{
			hiddenLayer[j] +=  (_wm->getEnergyLevel()/MedeaAggregationSharedData::gEnergyMax)  * _parameters[geneToUse];  // !N : added: energy value normalization btw 0 and 1.
			geneToUse ++;
		}

		//bias
		for (int j= 0 ; j < _wm->_nbHiddenNeurons ; j++ )
		{
			hiddenLayer[j] += 1.0  * _parameters[geneToUse];
			geneToUse ++;
		}


		//activation function on hidden layer
		for (int j= 0 ; j < _wm->_nbHiddenNeurons ; j++ )
		{
			hiddenLayer[j] = tanh(hiddenLayer[j]);
		}
		
		//hiddenLayer to output
		_wm->_desiredTranslationalValue = 0;
		_wm->_desiredRotationalVelocity = 0;
		double commandGripper = 0.0;

		for (int j= 0 ; j < _wm->_nbHiddenNeurons ; j++ )
		{
			_wm->_desiredTranslationalValue += hiddenLayer[j] * _parameters[geneToUse] ;
			geneToUse ++;
		}
		for (int j= 0 ; j < _wm->_nbHiddenNeurons ; j++ )
		{
			_wm->_desiredRotationalVelocity += hiddenLayer[j] * _parameters[geneToUse] ;
			geneToUse ++;
		}
		for (int j= 0 ; j < _wm->_nbHiddenNeurons ; j++ )
		{
			commandGripper += hiddenLayer[j] * _parameters[geneToUse] ;
			geneToUse ++;
		}
		
		_wm->_desiredTranslationalValue += 1.0 * _parameters[geneToUse] ;
		geneToUse ++;
		_wm->_desiredRotationalVelocity += 1.0 * _parameters[geneToUse] ;
		geneToUse ++;
		commandGripper += 1.0 * _parameters[geneToUse] ;

		//activation function on output
		_wm->_desiredTranslationalValue = tanh( _wm->_desiredTranslationalValue ) ;  // !N note that tanh is optional for ANN outputs.
		_wm->_desiredRotationalVelocity = tanh( _wm->_desiredRotationalVelocity );
		commandGripper = tanh( commandGripper );
		commandGripper = (commandGripper+1.0)/2.0;

		// normalize to motor interval values
		_wm->_desiredTranslationalValue = _wm->_desiredTranslationalValue * gMaxTranslationalSpeed;
		_wm->_desiredRotationalVelocity = _wm->_desiredRotationalVelocity * gMaxRotationalSpeed;

		//apply the output value
		if (commandGripper < 0.5)
		{
			_wm->setGripperStatus(GripperConnectionMechanism::LOW);
		}
		else
		{
			_wm->setGripperStatus(GripperConnectionMechanism::HIGH);
		}

		_wm->setEnergyHarvestingRate(1.0);
}

