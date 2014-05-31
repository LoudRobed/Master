/*
 * MedeaMovingSpAgentObserver.cpp
 * Roborobo
 *
 */

#include "mEDEA-MovingSp/include/MedeaMovingSpAgentObserver.h"
#include "World/World.h"
#include "mEDEA-MovingSp/include/MedeaMovingSpAgentWorldModel.h"
#include "mEDEA-sp/include/MedeaSpAgentObserver.h"
#include "WorldModels/RobotAgentWorldModel.h"

/**************************************************************/

/* Consr/Destr */

MedeaMovingSpAgentObserver::MedeaMovingSpAgentObserver(RobotAgentWorldModel *__wm) : MedeaSpAgentObserver(__wm)
{
  //  MedeaSpAgentObserver(*__wm);
  _wm = (MedeaMovingSpAgentWorldModel*)__wm;
  
  _wm->_minValue = -1.0;
  _wm->_maxValue = 1.0;
  _wm->_currentSigma = MedeaSpSharedData::gSigmaRef;
  _wm->setLifeTime(1);
  _wm->setWaitForGenome(false);
  _wm->setActiveStatus(true);
  gProperties.checkAndGetPropertyValue("nbHiddenNeurons",&_wm->_nbHiddenNeurons,true);
  
    _wm->resetActiveGenome();
  
  if ( gVerbose )
    {
      std::cout << "in AgentObserver:\n";
      std::cout << "robot #" << _wm->_agentId << "\n" ;	
    }
}

MedeaMovingSpAgentObserver::~MedeaMovingSpAgentObserver() {}


/* Methodes */

void MedeaMovingSpAgentObserver::selectNextGenome()
{
  if(_wm->getGenomeList().size() != 0) // security, but should be optional
    {
      double bestDiff = 3.0; // means infinite
      int bestGenome = -1;   //  not in the list
      unsigned int it;
      int i = 0;
      std::vector<MedeaMovingSpGenome> genomes = _wm->getGenomeList();
      if(_wm->getStrategy() == 1)
	/* Selection of the closest lower familyMark */
	{
	  for(it = 0;it < genomes.size();it++) // for each genome in _wm's genome list
	    {
	      double currFam = genomes.at(it).getFamilyMark();

	      if(currFam <= _wm->getFamilyMark()) 
		{
		  if(bestDiff > (_wm->getFamilyMark() - currFam))
		    {
		      bestDiff = _wm->getFamilyMark() - currFam;
		      bestGenome = i;
		    }
		}
	      i ++;
	    }
	}
      else if(_wm->getStrategy() == 2) 
	/* Selection of the closest upper familyMark */
	{
	  for(it=0; it < genomes.size() ;it++) // for each genome in _wm's genome list
	    {
	      double currFam = genomes.at(it).getFamilyMark();

	      if(currFam >= _wm->getFamilyMark()) 
		{
		  if(bestDiff > (currFam - _wm->getFamilyMark() ))
		    {
		      bestDiff = currFam - _wm->getFamilyMark();
		      bestGenome = i;
		    }
		}
	      i ++;
	    }
	}
      else if(_wm->getStrategy() == 3)
	/* Selecion of the closest familyMark, without regard to the direction */
	{
	  for(it=0; it < genomes.size() ;it++) // for each genome in _wm's genome list
	    {
	      double currFam = genomes.at(it).getFamilyMark();

	      if(bestDiff > abs((_wm->getFamilyMark() - currFam)))
		{
		  bestDiff = abs(_wm->getFamilyMark() - currFam);
		  bestGenome = i;
		}
	      i ++;
	    }
	 
	}
      else 
	{
	  MedeaSpAgentObserver::pickRandomGenome(); // should be avoided in Medea-MovingSp
	}
      if(bestGenome == -1) // none of the genomes in the list had a lower familyMark
   {
	      MedeaSpAgentObserver::pickRandomGenome();
	    }
 else 
	    {
	      double familyAux = _wm->getCurrentGenome().getFamilyMark();
	      int stratAux = _wm->getCurrentGenome().getStrategy();
	      _wm->setCurrentGenome(_wm->getGenomeList().at(bestGenome));
	      familyAux = (familyAux + _wm->getCurrentGenome().getFamilyMark()) / 2.0;
	      if(MedeaSpSharedData::gDynamicSigma)
		{
		  mutateWithBouncingBounds(_wm->_sigmaList[it]);
		}
	      else
		{
		  mutateWithBouncingBounds(-1.0);
		}

	      _wm->getCurrentGenome().setFamilyMark(familyAux);
	      _wm->getCurrentGenome().setStrategy(stratAux);

	      _wm->setNewGenomeStatus(true);
	      _wm->setFatherId(it); // TOCHECK
	      
	      gLogFile << gWorld->getIterations() << " : " << _wm->_agentId + 1000 * _wm->getDateOfBirth() << " takes " << _wm->getFatherId() << std::endl;
	      
	      // Debug
	      if((_wm->_agentId == 1) && gVerbose)
		{
		  std::cout << "Sigma is " << _wm->_sigmaList[it] << "." << std::endl;
		}

	      _wm->getGenomeList().clear();
	    }
    }
}

void MedeaMovingSpAgentObserver::writeGenome(MedeaMovingSpGenome genome, float sigma)
{
  _wm->addGenomeToList(genome);
  if(MedeaSpSharedData::gDynamicSigma) 
    { 
      _wm->_sigmaList[_wm->getGenomeList().size()] = sigma;
    }
}



void MedeaMovingSpAgentObserver::step()
{
 
  /* End of a generation */
  if( 
     (_wm->getLifeTime() >= MedeaSpSharedData::gEvaluationTime && _wm->getWaitForGenome() && !(_wm->getActiveStatus()))
     ||
     (_wm->getLifeTime() >= MedeaSpSharedData::gEvaluationTime && _wm->getActiveStatus())
      )
    {
      	/**
	         * Like in mother class::
		 * Mechanism to print the values of the energy counters :
		 * 	It occurs when the state of an active robot change ie :
		 * 	1. When a robot Die (ie run out of energy)
		 * 	2. At the end of a generation.
		 * The following lines implement the second part, the first part is done when a agent die (in WorldObserver)
		 * */

      if(_wm->getActiveStatus())
	{
	  _wm->resetEnergyCounter();
	}
      
      checkGenomeList(); // If the list is empty, the robot will have to wait one more generation
      _wm->setLifeTime(0);
    }

  // When dead time ends (maybe redundancy between control and vars), the robot's state should be in listening mode.
  if(_wm->getLifeTime() >= (MedeaSpSharedData::gEvaluationTime + rand()%10) && !(_wm->getWaitForGenome()) && !(_wm->getActiveStatus()))
    {
      _wm->setWaitForGenome(true);
      _wm->setLifeTime(0);
    }

  /* Treatment of maturity concept */  

  if(_wm->getActiveStatus() && _wm->getMaturity() > 0)
    {
      _wm->setMaturity(_wm->getMaturity()+1);
      if(_wm->getMaturity() > MedeaSpSharedData::gEvaluationTime + 1)
	{
	  _wm->setMaturity(0); // The robot can spread its genome again
	}
    }

  /* Broadcast */
  if(_wm->getActiveStatus() && (_wm->getMaturity()<=0))
    {
      for(int i=0; i<gAgentCounter; i++) // for each agent
	{
	  // if this agent isn't the current agent and is geographically reachable by broadcasting
	  if((i != _wm->_agentId) && (gRadioNetworkArray[_wm->_agentId][i]))
	    {
	      MedeaMovingSpAgentObserver* targetAgentObserver = dynamic_cast<MedeaMovingSpAgentObserver*>(gWorld->getAgent(i)->getObserver());
	      	      
	      if(!targetAgentObserver)
		{
		  std::cerr << "Error from robot " << _wm->_agentId << " : the observer of robot " << i << " isn't a SwarmOnlineObserver" << std::endl;
		  exit(1);
		}
	      
	      if((targetAgentObserver->_wm->getActiveStatus()) || targetAgentObserver->_wm->getWaitForGenome())
		{
		  if(MedeaSpSharedData::gDynamicSigma)
		    {
		      float dice = float(rand() % 100) / 100.0;
		      float sigmaSendValue = 0.0;
		      
		      if((dice >= 0.0) && (dice < MedeaSpSharedData::gProbAdd))
			{
			  sigmaSendValue = _wm->_currentSigma * (1 + MedeaSpSharedData::gDynaStep);
			  if(sigmaSendValue > MedeaSpSharedData::gSigmaMax)
			    {
			      sigmaSendValue = MedeaSpSharedData::gSigmaMax;
			    }
			}
		      else
			if ((dice >= MedeaSpSharedData::gProbAdd) && (dice < MedeaSpSharedData::gProbAdd+MedeaSpSharedData::gProbSub))
			  {
			    sigmaSendValue = _wm->_currentSigma * (1-MedeaSpSharedData::gDynaStep);
			    if (sigmaSendValue < MedeaSpSharedData::gSigmaMin)
			      {
				sigmaSendValue = MedeaSpSharedData::gSigmaMin;
			      }
			  }
			else
			  {
			    std::cerr << "Error : In SwarmOnlineObserver, the rand value is out of bound. The sum of MedeaSpSharedData::gProbRef and MedeaSpSharedData::gProbMax is probably not equal to one" << std::endl;
			    exit(1);
			  }
		      targetAgentObserver->writeGenome(_wm->getCurrentGenome(),sigmaSendValue);
		    }
	      else
		{
		  targetAgentObserver->writeGenome(_wm->getCurrentGenome(),_wm->_currentSigma);
		}
		}
	    }
	}
    }
  _wm->setLifeTime(_wm->getLifeTime() + 1);
}

  
  
void MedeaMovingSpAgentObserver::checkGenomeList()
{
  // Debug
  if(_wm->_agentId == gAgentIndexFocus && gVerbose)
    {
      std::cout << "agent #" << gAgentIndexFocus << " is renewed" << std::endl;
      std::cout << "agent #" << gAgentIndexFocus << " imported " << _wm->getGenomeList().size() << " genomes. Energy is " << _wm->getEnergyLevel() << ". Status is " << _wm->getActiveStatus() << "." << std::endl;
    }

  /* Case of imported genome(s) */
  if(_wm->getGenomeList().size() > 0) 
    {
      _wm->setDateOfBirth(gWorld->getIterations());
      selectNextGenome();
      _wm->setWaitForGenome(false);
      _wm->setActiveStatus(true);
      /** Print the new genome on the logFile **/
      gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " uses " << _wm->getAbilityToForage();
      gLogFile << " at " << _wm->getXReal() << std::endl;
    }
  
  /* Case waiting for genome (not imported) */
  else
    {
      _wm->resetActiveGenome();
      _wm->setWaitForGenome(true);
      _wm->setActiveStatus(false);
    }
}



void MedeaMovingSpAgentObserver::pickRandomGenome()
{
  if(_wm->getGenomeListSize() != 0) // expected to be always true when this method is called
    {
      int size = _wm->getGenomeListSize();
      int randomIndex = rand() % size;
      
      int it = 0;
      
      while(randomIndex != 0)
	{
	  it ++;
	  randomIndex--;
	}
      
      _wm->setCurrentGenome(_wm->getGenomeList().at(it));

      if(MedeaSpSharedData::gDynamicSigma)
	{
	  mutateWithBouncingBounds(_wm->_sigmaList[it]);
	}
      else
	{
	  mutateWithBouncingBounds(-1.0);
	}
      
      _wm->setNewGenomeStatus(true);
      _wm->setFatherId(it); // TOCHECK

      gLogFile << gWorld->getIterations() << " : " << _wm->_agentId + 1000 * _wm->getDateOfBirth() << " takes " << _wm->getFatherId() << std::endl;

      // Debug
      if((_wm->_agentId == 1) && gVerbose)
	{
	  std::cout << "Sigma is " << _wm->_sigmaList[it] << "." << std::endl;

	  _wm->getGenomeList().clear();
	}
    }
  // Shouldn't be reached
}


void MedeaMovingSpAgentObserver::mutateWithBouncingBounds(float sigma)
{
  MedeaMovingSpGenome genAux = _wm->getCurrentGenome();  // MedeaMovingSpGenome();


  /* Value of the sigma parameter */

  if(MedeaSpSharedData::gDynamicSigma)
    {
      _wm->_currentSigma = sigma;
    }
  else
    {
      float randValue = float(rand() % 100)/100.0;
      if((randValue >= 0.0) && (randValue < MedeaSpSharedData::gProbRef))
	{
	  _wm->_currentSigma = MedeaSpSharedData::gSigmaRef;
	}
      else if((randValue >= MedeaSpSharedData::gProbRef) && (randValue < MedeaSpSharedData::gProbMax + MedeaSpSharedData::gProbRef))
	{
	  _wm->_currentSigma = MedeaSpSharedData::gSigmaMax;
	}
      else
	{
	  std::cerr << "Error : In SwarmOnlineObserver, the rand value is out of bound. The sum of MedeaSpSharedData::gProbRef and MedeaSpSharedData::gProbMax is probably not equal to one" << std::endl;
	  exit(1);
	}
    }

  /* Transitions of the new MLP controller */

  /** Synapses IH **/
  std::vector<double> IH = genAux.getSynapsesIH();
  for(unsigned int i=0; i<IH.size(); i++)
    {
      double value = IH.at(i) + getGaussianRand(0,_wm->_currentSigma);
      value = bouncing(value);
      IH.at(i) = value;
    }
  genAux.setSynapsesIH(IH);

  /** Synapses HO **/
  std::vector<double> HO = genAux.getSynapsesHO();
  for(unsigned int i=0; i<HO.size(); i++)
    {
      double value = HO.at(i) + getGaussianRand(0, _wm->_currentSigma);
      value = bouncing(value);
      HO.at(i) = value;
    }
  genAux.setSynapsesHO(HO);

  /** Synapses B **/
  std::vector<double> B = genAux.getSynapsesB();
  for(unsigned int i=0; i<B.size(); i++)
    {
      double value = B.at(i) + getGaussianRand(0, _wm->_currentSigma);
      value = bouncing(value);
      B.at(i) = value;
    }
  genAux.setSynapsesB(B);

  /* gSkill */
  double vgskill = genAux.getGSkill();
  vgskill = bouncing(vgskill);
  genAux.setGSkill(vgskill);

  // familyMark and strategy are in selectNextGenome

  /* Update */

  _wm->setCurrentGenome(genAux);
}


double MedeaMovingSpAgentObserver::bouncing(double value)
{
  if(value < _wm->_minValue)
    {
      double range = _wm->_maxValue - _wm->_minValue;
      double overflow = -((double)value - _wm->_minValue);
      overflow = overflow - 2*range*(int)(overflow/(2*range));
      if(overflow < range) {value = _wm->_minValue + overflow;}
      // else = overflow in [range; 2*range]
      else {value = _wm->_minValue + range - (overflow - range);}
    }

  else if(value > _wm->_maxValue)
    {
      double range = _wm->_maxValue - _wm->_minValue;
      double overflow = (double)value - _wm->_maxValue;
      overflow = overflow - 2*range * (int)(overflow/(2*range));
      if (overflow < range) {value = _wm->_maxValue - overflow;}
      // else = overflow in [range; 2*range]
      else {value = _wm->_maxValue - range + (overflow-range);}
    }

  return value;
}
