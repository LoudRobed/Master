/*
 *  MedeaCommPerceptronControlArchitecture.cpp
 *  roborobo-online
 *
 *  imported from Jean-Marc on 21/12/09
 *  current dev: Nicolas on 1/4/2009
 *  moved in altruism by Jean-Marc on 17/09/2010
 *
 */

#include "mEDEA-comm/include/MedeaCommPerceptronControlArchitecture.h"

#include "World/World.h"

#include "Utilities/Misc.h"

#include <math.h>

MedeaCommPerceptronControlArchitecture::MedeaCommPerceptronControlArchitecture( RobotAgentWorldModel *__wm )
{
	_wm = (MedeaCommAgentWorldModel*)__wm;
	_iteration = 0;

	_wm->setEnergyLevel(MedeaCommSharedData::gEnergyInit);
	_wm->setDeltaEnergy(0.0); 

	_wm->setAngleToClosestEnergyPoint(0);
	_wm->setDistanceToClosestEnergyPoint(0);
	_wm->setAction(0.0);
	std::vector<double> tmp;
	for (int i =0 ; i< MedeaCommSharedData::nbReceptionSector ; i++)
	{
		tmp.push_back(0.0);
	}
	_wm->setReceivedCommunication(tmp);

	gProperties.checkAndGetPropertyValue("nbHiddenNeurons",&_nbHiddenNeurons,true);
	
	_wm->setActiveStatus(true);

	if ( gVerbose )
	{
		std::cout << "robot #" << _wm->_agentId << " perceptron \n" ;	
	}
}

MedeaCommPerceptronControlArchitecture::~MedeaCommPerceptronControlArchitecture()
{
	// nothing to do.
}

void MedeaCommPerceptronControlArchitecture::reset()
{
	_parameters.clear();
	_parameters = _wm->_currentGenome;
}


// perform one controller update
// set motor value using motor format.
void MedeaCommPerceptronControlArchitecture::step()
{
	_iteration++;

	if ( _wm->getNewGenomeStatus() ) // check for new NN parameters
	{
		reset();
		_wm->setNewGenomeStatus(false);
	}

	if ( _wm->getActiveStatus() == true )
	{

		if ( gVerbose && gInspectAgent && gAgentIndexFocus == _wm->_agentId )
		{
			std::cout << "tgt.in: " << _wm->getAngleToClosestEnergyPoint() << std::endl;// " (" << _wm->_agentAbsoluteOrientation << "," << angleToClosestEnergyPoint << ")" << std::endl;
		}

		std::vector<double> hiddenLayer;
		hiddenLayer.resize(_nbHiddenNeurons);
		for (int j= 0 ; j < _nbHiddenNeurons ; j++ )
		{
			hiddenLayer[j] = 0.0;
		}

		int geneToUse = 0;

		// inputs to hidden Layer

		// distance sensors
		for ( int i = 0 ; i < _wm->_sensorCount ; i++ )
		{
			for (int j= 0 ; j < _nbHiddenNeurons ; j++ )
			{
				// BUG: hiddenLayer[j] += tanh(_wm->_sensorCount) * _parameters[geneToUse] ;  // ??? !N - BUG di0319 !n -- sensor are NOT taken into account!
				hiddenLayer[j] += (_wm->getSensorDistanceValue(i)/_wm->getSensorMaximumDistanceValue(i)) * _parameters[geneToUse] ;  // !N - corrected BUG di0319 - use normalized sensor value in 0...1
				geneToUse ++;
			}
		}

		//floor sensor
		for (int j= 0 ; j < _nbHiddenNeurons ; j++ )
		{
			if ( _wm->_floorSensor == 234 )	//234 on the floor sensor means energy point	
				hiddenLayer[j] += 1.0  * _parameters[geneToUse];
			//hiddenLayer[j] += _wm->_floorSensor/255.0  * _parameters[geneToUse];
			geneToUse ++;
		}

		//direction of the closest energy point 
		for (int j= 0 ; j < _nbHiddenNeurons ; j++ )
		{
			hiddenLayer[j] += _wm->getAngleToClosestEnergyPoint()  * _parameters[geneToUse];		
			geneToUse ++;
		}

		//distance to the closest energy point 
		for (int j= 0 ; j < _nbHiddenNeurons ; j++ )
		{
			hiddenLayer[j] += _wm->getDistanceToClosestEnergyPoint()  * _parameters[geneToUse]; 
			geneToUse ++;
		}

		//energy level
		for (int j= 0 ; j < _nbHiddenNeurons ; j++ )
		{
			hiddenLayer[j] +=  (_wm->getEnergyLevel()/MedeaCommSharedData::gEnergyMax)  * _parameters[geneToUse];  // !N : added: energy value normalization btw 0 and 1.
			geneToUse ++;
		}

		//reception of communication
		std::vector<double> receivedCommunication = _wm->getReceivedCommunication();
		for (int i= 0 ; i < MedeaCommSharedData::nbReceptionSector ; i++ )
		{
			for (int j= 0 ; j < _nbHiddenNeurons ; j++ )
			{
				hiddenLayer[j] +=  receivedCommunication[i]  * _parameters[geneToUse];
				geneToUse ++;
			}
		}

		//bias
		for (int j= 0 ; j < _nbHiddenNeurons ; j++ )
		{
			hiddenLayer[j] += 1.0  * _parameters[geneToUse];
			geneToUse ++;
		}


		//activation function on hidden layer
		for (int j= 0 ; j < _nbHiddenNeurons ; j++ )
		{
			hiddenLayer[j] = tanh(hiddenLayer[j]);
		}
		
		//hiddenLayer to output
		_wm->_desiredTranslationalValue = 0;
		_wm->_desiredRotationalVelocity = 0;
		double action = 0.0;
		double communication = 0.0;

		for (int j= 0 ; j < _nbHiddenNeurons ; j++ )
		{
			_wm->_desiredTranslationalValue += hiddenLayer[j] * _parameters[geneToUse] ;
			geneToUse ++;
		}
		for (int j= 0 ; j < _nbHiddenNeurons ; j++ )
		{
			_wm->_desiredRotationalVelocity += hiddenLayer[j] * _parameters[geneToUse] ;
			geneToUse ++;
		}
		for (int j= 0 ; j < _nbHiddenNeurons ; j++ )
		{
			action += hiddenLayer[j] * _parameters[geneToUse] ;
			geneToUse ++;
		}
		for (int j= 0 ; j < _nbHiddenNeurons ; j++ )
		{
			communication += hiddenLayer[j] * _parameters[geneToUse] ;
			geneToUse ++;
		}
		
		_wm->_desiredTranslationalValue += 1.0 * _parameters[geneToUse] ;
		geneToUse ++;
		_wm->_desiredRotationalVelocity += 1.0 * _parameters[geneToUse] ;
		geneToUse ++;
		action += 1.0 * _parameters[geneToUse] ;
		geneToUse ++;
		communication += 1.0 * _parameters[geneToUse] ;

		//activation function on output
		_wm->_desiredTranslationalValue = tanh( _wm->_desiredTranslationalValue ) ;  // !N note that tanh is optional for ANN outputs.
		_wm->_desiredRotationalVelocity = tanh( _wm->_desiredRotationalVelocity );
		action = tanh(action);
		action = (action+1.0)/2.0;
		communication = tanh(communication);
		communication = (communication+1.0)/2.0;

		// normalize to motor interval values
		_wm->_desiredTranslationalValue = _wm->_desiredTranslationalValue * gMaxTranslationalSpeed;
		_wm->_desiredRotationalVelocity = _wm->_desiredRotationalVelocity * gMaxRotationalSpeed;

		//apply the output value
		_wm->setAction(action);
		_wm->setCommunication(communication);


	}

}

