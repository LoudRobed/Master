/*
 * MedeaMovingSpPerceptronControlArchitecture.cpp
 * Roborobo
 *
 * imported from Simon on 04/04/2012
 *
 */

#include "mEDEA-MovingSp/include/MedeaMovingSpPerceptronControlArchitecture.h"
#include "mEDEA-MovingSp/include/MedeaSpPerceptronControlArchitecture.h"
#include "World/World.h"
#include "Utilities/Misc.h"
#include "mEDEA-MovingSp/include/MedeaMovingSpWorldObserver.h"
#include "mEDEA-MovingSp/include/MedeaMovingSpGenome.h"



/* Constructors & Destructors */

MedeaMovingSpPerceptronControlArchitecture::MedeaMovingSpPerceptronControlArchitecture(RobotAgentWorldModel *__wm) // : MedeaSpPerceptronControlArchitecture(__wm)
{
  _wm = (MedeaMovingSpAgentWorldModel*) __wm;
  //  _parameters = _wm->getCurrentGenome();
  _iteration = 0;
  _nbHiddenNeurons = 5;

  _wm->setEnergyLevel(MedeaSpSharedData::gEnergyInit);
  _wm->setDeltaEnergy(0.0);

  // Initialising
  // Each energy type is reachable from everywhere
  for(int i=0; i<MedeaSpSharedData::gNbTypeResource;i++)
    {
      _wm->setAngleToClosestEnergyPoint(i,0);
      _wm->setDistanceToClosestEnergyPoint(i,0);
      _wm->setEnergyPointDirectionAngleValue(i,0);
      _wm->setEnergyPointDistanceValue(i,0);
    }

  gProperties.checkAndGetPropertyValue("nbHiddenNeurons",&_nbHiddenNeurons,true);
  _wm->setActiveStatus(true);
  if(gVerbose)
    {
      std::cout << "in PCA:\n";
      std::cout << "robot #" << _wm->_agentId << "\nperceptron\n";
      // std::cout << "H=" << _nbHiddenNeurons;
    }
}

MedeaMovingSpPerceptronControlArchitecture::~MedeaMovingSpPerceptronControlArchitecture() {}


/* Main Methods */

void MedeaMovingSpPerceptronControlArchitecture::reset()
{
  //_parameters.~MedeaMovingSpGenome();
  _parameters = _wm->getCurrentGenome();
}

void MedeaMovingSpPerceptronControlArchitecture::step()
{
  _iteration++;

  if(_wm->getNewGenomeStatus())
    {
      reset();
      _wm->setNewGenomeStatus(false);
    }

  _wm->_desiredTranslationalValue=0.0;
  _wm->_desiredRotationalVelocity=0.0;

  /* 
   * From now on, the energy points will be treated via the WorldObserver
   * So the gEnergyPoints mustn't be used anymore.
   */

  MedeaMovingSpWorldObserver *wo = dynamic_cast< MedeaMovingSpWorldObserver * >(_wm->_world->getWorldObserver()); 

  std::vector<MedeaSpEnergyPoint*> *allEP = wo->getEnergyPoints();


  /* Energy points distance management, as in mother class */

  if(_wm->getActiveStatus())
    {
      double angleToClosestEnergyPoint = 0.0;
      double shortestDistance = 0.0;
      Point2d posRobot(_wm->_xReal, _wm->_yReal);

      for(int i=0; i<MedeaSpSharedData::gNbTypeResource; i++)
	{
	  std::vector<MedeaSpEnergyPoint*>::iterator closestPoint = allEP->begin();
	  // Looking for the 1st point of the good type
	  while ((int) ((*closestPoint)->getType()) != 1)
	    {
	      closestPoint++;
	    }

	  shortestDistance = getEuclidianDistance(posRobot, (*closestPoint)->getPosition()); // useful only if there are some energyless points in the environment, which isn't the 1st aim of this project

	  for(std::vector<MedeaSpEnergyPoint*>::iterator it = allEP->begin(); it<allEP->end(); it++)
	    {
	      if((*it)->getType() == i)
		{
		  double newDistance = getEuclidianDistance (posRobot, (*it)->getPosition());
		  if(newDistance < shortestDistance)
		    {
		      shortestDistance = newDistance;
		      closestPoint = it;
		    }
		}
	    }
	  /** Orientations Computing (cf mother class) **/
	  
	  angleToClosestEnergyPoint = (atan2((*closestPoint)->getPosition().y-posRobot.y,(*closestPoint)->getPosition().x-	posRobot.x)/M_PI)*180.0;
	  angleToClosestEnergyPoint += 360.0 ;
	  angleToClosestEnergyPoint = computeModulo(angleToClosestEnergyPoint,360.0);
	  if ( angleToClosestEnergyPoint > 180 ) // force btw -180 and 180
	    angleToClosestEnergyPoint -= 360.0;
	  
	  //compute the angle between the actual orientation of the robot and the orientation of the closest energy point ( in degree between -180 and 180 )
	  double diffAngleToClosestEnergyPoint= angleToClosestEnergyPoint -  _wm->_agentAbsoluteOrientation ;
	  if ( diffAngleToClosestEnergyPoint< -180.0 )
	    {
	      diffAngleToClosestEnergyPoint+= 360.0 ; 
	    }
	  if ( diffAngleToClosestEnergyPoint> 180.0 )
	    {
	      diffAngleToClosestEnergyPoint-= 360.0 ;
	    }
	  
	  //cast the diffAngle between -1 and 1
	  diffAngleToClosestEnergyPoint= diffAngleToClosestEnergyPoint/ 180.0 ; 
	  _wm->setEnergyPointDirectionAngleValue(i,diffAngleToClosestEnergyPoint);
	  
	  //cast the shortest distance between 0 and 1
	  if ( shortestDistance > gSensorRange )
	    shortestDistance = 1.0;
	  else
	    shortestDistance = shortestDistance / (double)gSensorRange;
	  _wm->setEnergyPointDistanceValue(i,shortestDistance);
	  
	  //		if ( gAgentIndexFocus == _wm->_agentId )
	  if ( gVerbose && gInspectAgent && gAgentIndexFocus == _wm->_agentId )
	    {
	      std::cout << "SunSensorValue: " << _wm->getEnergyPointDirectionAngleValue(i) << " , " << _wm->getEnergyPointDistanceValue(i) << std::endl;			
	    }
	}

      /* MLP Computation */
      
      std::vector<double> hiddenLayer; // neurons
      hiddenLayer.resize(_nbHiddenNeurons);
      for(int j=0; j<_nbHiddenNeurons; j++)
	{
	  hiddenLayer[j] = 0.0;
	}
      
      int synapseToUse = 0;
      
      /** IH computation **/

      /*** Distance sensors ***/

      for(int i=0; i<_wm->_sensorCount; i++) // for each sensor (input)
	{
	  for(int j=0; j<_nbHiddenNeurons; j++) // for each hidden neuron
	    {
	      hiddenLayer[j] += (_wm->getSensorDistanceValue(i)/_wm->getSensorMaximumDistanceValue(i)) * _parameters.getSynapsesIH().at(synapseToUse);  // hidden neurons update
	      synapseToUse ++;
	    }
	}
      
      /*** Floor sensor ***/
      for(int j=0; j<_nbHiddenNeurons; j++)
	{
	  if(_wm->_floorSensor != 0)  // there is something or not, binary sensor
	    {
	      hiddenLayer[j] += 1.0 * _parameters.getSynapsesIH().at(synapseToUse);
	      synapseToUse++;
	    }


	  /*** Closest energy point ***/
	  for(int i=0; i<MedeaSpSharedData::gNbTypeResource; i++)
	    {
	      for(int j=0; j<_nbHiddenNeurons; j++)
		{
		  hiddenLayer[j] += _wm->getEnergyPointDistanceValue(i) * _parameters.getSynapsesIH().at(synapseToUse);
		  synapseToUse++;
		}
	    }
	  
	  
	  /*** Energy Level ***/
	  for(int j=0; j<_nbHiddenNeurons; j++)
	    {
	      hiddenLayer[j] += (_wm->getEnergyLevel()/MedeaSpSharedData::gEnergyMax) * _parameters.getSynapsesIH().at(synapseToUse);
	      synapseToUse++;
	    }
	  
	  
	  /*** Bias ***/
	  for(int j=0; j<_nbHiddenNeurons; j++)
	    {
	      hiddenLayer[j] += 1.0 * _parameters.getSynapsesB().at(j);
	    }


	  /** HO Computation **/
	  
	  synapseToUse = 0;
	  
	  _wm->_desiredTranslationalValue = 0;
	  _wm->_desiredRotationalVelocity = 0;
	  
	  for(int j=0; j<_nbHiddenNeurons; j++)
	    {
	      _wm->_desiredTranslationalValue += hiddenLayer[j] * _parameters.getSynapsesHO().at(synapseToUse);
	      synapseToUse++;
	    }
	  
	  for(int j=0; j<_nbHiddenNeurons; j++)
	    {
	      _wm->_desiredRotationalVelocity += hiddenLayer[j] * _parameters.getSynapsesHO().at(synapseToUse);
	      synapseToUse++;
	    }
	  /*
	    _wm->_desiredTranslationalValue += 1.0 * _parameters.getSynapsesHO().at(synapseToUse);
	  synapseToUse++;
	  
	  _wm->_desiredRotationalVelocity += 1.0 * _parameters.getSynapsesHO().at(synapseToUse);
	  */
	  //activation function on output
	  _wm->_desiredTranslationalValue = tanh( _wm->_desiredTranslationalValue ) ;  // !N note that tanh is optional for ANN outputs.
	  _wm->_desiredRotationalVelocity = tanh( _wm->_desiredRotationalVelocity );
	  
	  // normalize to motor interval values
	  _wm->_desiredTranslationalValue = _wm->_desiredTranslationalValue * gMaxTranslationalSpeed;
	  _wm->_desiredRotationalVelocity = _wm->_desiredRotationalVelocity * gMaxRotationalSpeed;
	
	}
    }
}


/* Auxiliary Methods */
/*
void MedeaMovingSpPerceptronControlArchitecture::searchClosestEnergyPoint(Point2d posRobot, std::vector<Point2d> energyPoints)
{
  // TODO (or not ?)
}
*/
