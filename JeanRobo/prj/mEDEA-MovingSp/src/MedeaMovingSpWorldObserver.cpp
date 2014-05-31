/*
 * MedeaMovingSpWorldObserver.cpp
 * Roborobo
 *
 */

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/Observer.h"
#include "Observers/WorldObserver.h"

#include "mEDEA-MovingSp/include/MedeaMovingSpWorldObserver.h"
#include "mEDEA-MovingSp/include/MedeaSpWorldObserver.h"
#include "World/World.h"

/********************************************************************/

/* Constr/Destr */

MedeaMovingSpWorldObserver::MedeaMovingSpWorldObserver(World *__world) : MedeaSpWorldObserver(__world)
{
  _world = __world;
  
  // ====================================
  //	Line commented in order to allow setup network test
  if ( !gRadioNetwork)
    {
      gProperties.checkAndGetPropertyValue("gSparsity",&MedeaSpSharedData::gSparsity,true);
    }
  
  if ( !MedeaSpSharedData::gSwarmOnlineObsUsed)
    {
      std::cout << "Error : gSwarmOnlineObsUsed == false. The swarm online observer need some variables. Define this option to true or use another observer" << std::endl;
      exit(1);
    }
  
  if ( !gEnergyMode )
    {
      std::cout << "Error : gEnergyMode should be true to use SwarmOnlineObserver" << std::endl;
      exit(1);
    }
  // * iteration and generation counters
  
  _posNum=0;
  _lifeIterationCount = -1;
  _generationCount = -1;
  // 	coopEnergyPoints = std::vector<MedeaSpEnergyPoint*>(gMaxEnergyPoints);
  
  _firstIteration=true;
}

MedeaMovingSpWorldObserver::~MedeaMovingSpWorldObserver()
{
}


/* Methodes */

void MedeaMovingSpWorldObserver::step()
{
  if(_firstIteration)
    {
      /* Initialising environment */
      
      /** Energy **/
      
      int x0,x1,y0,y1;
      _firstIteration = false;
      gEnergyPoints.empty();
      
      x0 = gAreaWidth/2; x1 = gAreaWidth/2.0;
      y0 = gAreaHeight/2; y1 = gAreaHeight/2.0;
     
      Point2d positionSun0(x0,y0);
      Point2d positionSun1(x1,y1);
      
      coopEnergyPoints=new std::vector<MedeaSpEnergyPoint*>();
      coopEnergyPoints->push_back(new MedeaSpEnergyPoint(0));
      InanimateObject * pInaObj = (InanimateObject*) coopEnergyPoints->back();
      gWorld->addObject(pInaObj);
      coopEnergyPoints->push_back(new MedeaSpEnergyPoint(1));
      pInaObj = (InanimateObject*) coopEnergyPoints->back();
      gWorld->addObject(pInaObj);
      
      for(std::vector<MedeaSpEnergyPoint*>::iterator it= coopEnergyPoints->begin(); it!=coopEnergyPoints->end();it++){
	// 			(*it)->hide();
	if((*it)->getType() == 1)
	  (*it)->setPosition(positionSun1); 
	else
	  (*it)->setPosition(positionSun0); 
	(*it)->display();
	(*it)->setNHarverst(0);
	(*it)->setFixedLocationStatus(false);
      }
      
      /** Agents **/
     
      for(int i=0; i<gAgentCounter; i++)
	{
	  MedeaMovingSpAgentWorldModel *_wm = dynamic_cast<MedeaMovingSpAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
	  
	  _wm->_yReal = rand() % gAreaHeight;
	  _wm->_xReal = rand() % gAreaWidth;
	  
	  if(gVerbose)
	    {
	      std::cout << "y = " << _wm->_yReal << "\n";
	      std::cout << "x = " << _wm->_xReal << "\n";
	    }
	  
	}
    }
  
  _lifeIterationCount ++;

  // DEBUG
  if(gVerbose)
    {
      for(int i=0; i<gAgentCounter; i++)
	{
	  MedeaMovingSpAgentWorldModel *_wm = dynamic_cast<MedeaMovingSpAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
	  //std::cout << "Energy = " << _wm->getEnergyLevel() << "\n";
	  std::cout << "Received genomes = " << _wm->getGenomeList().size() << "\n";
	}
    }
  /* End of a generation */
  if(_lifeIterationCount >= MedeaSpSharedData::gEvaluationTime)
    {
      /** Intermediate report for the logFile **/

      int activeCount = 0;
      int r0 = 0;
      int r1 = 0;
      int both = 0;

      for(int i=0; i<gAgentCounter; i++) // for each agent
	{
	  MedeaMovingSpAgentWorldModel *_wm = dynamic_cast<MedeaMovingSpAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
	  
	  if(_wm->getActiveStatus())  // active agent
	    {
	      activeCount ++;
	      if((forageReward(_wm->getAbilityToForage(),1)>0) && (forageReward(_wm->getAbilityToForage(),0)>0)) {both ++;}
	      else if(forageReward(_wm->getAbilityToForage(),0)>0) {r0++;}
	      else if(forageReward(_wm->getAbilityToForage(),1)>0) {r1++;}
	    }
	}
      
      if(!gVerbose) {std::cout << "[" << activeCount <<"]";}
      gLogFile << gWorld->getIterations() << " : activeCount " <<" "<<both<<" "<<r0<<" "<<r1<< std::endl; // same as in mEDEA-sp/'s logFiles

      // TOTHINK: are there some additional informations which would be interesting to add at this point in the logFile ?

      if(activeCount <= 0)
	{
	  gLogFile.close();
	  std::cout<<"--> extinction" << gLogFilename <<std::endl;
	  exit(0);
	}
      
      /** Building Heatmap **/
      
      /*** Variables ***/
      int heatmapSize = 100; // arbitrary, same as in mEDEA-sp
      int maxDistance = sqrt(gAreaWidth*gAreaWidth + gAreaHeight*gAreaHeight)/2.0;
      int *distanceHeatmap;
      int *orientationHeatmap;
      distanceHeatmap    = new int[heatmapSize];
      orientationHeatmap = new int[heatmapSize];
      for (int i = 0 ; i != heatmapSize ; i++ )
	{
	  distanceHeatmap[i] = 0;
	  orientationHeatmap[i] = 0;
	}
      double xRef = gAreaWidth/2.0 ;
      double yRef = gAreaHeight/2.0 ;

      for(int i=0; i!=gAgentCounter; i++)
	{
	  MedeaMovingSpAgentWorldModel *wm = dynamic_cast<MedeaMovingSpAgentWorldModel*>(gWorld->getAgent(i)->getWorldModel());
	  
	  if(wm->getActiveStatus())   // for each active agent
	    {
	      double dist = getEuclidianDistance(xRef,yRef,wm->_xReal,wm->_yReal);
	      int indexDist = (int) dist * heatmapSize/maxDistance; // normalisation
	      distanceHeatmap[indexDist]++;
	      
	      double orient = acos((wm->_xReal -xRef) / ((double) dist));
	      
	      if((wm->_yReal - yRef) > 0) // be careful with the sign, cf MedeaSpWorldObserver.cpp
		{
		  orient = -orient;
		}
	      int indexOrient = (orient + M_PI) * heatmapSize / (2.0*M_PI);
	      orientationHeatmap[heatmapSize - 1 - ((indexOrient+(heatmapSize*3)/4))%heatmapSize]++; // cf MedeaSpWorldObserver.cpp
	    }
	}

  /* LogFile's update */

      std::string str_agentDistancesToRef = "";
      std::string str_agentOrientationsToRef = "";

	for(int i=0; i!=heatmapSize; i++)   // same as in mEDEA-sp
	  {
	    str_agentDistancesToRef += convertToString(distanceHeatmap[i]);
	    str_agentDistancesToRef += ",";
	    str_agentOrientationsToRef += convertToString(orientationHeatmap[i]);
	    str_agentOrientationsToRef += ",";
	    // TOTHINK: are there some additional informations which would be interesting to add at this point in the logFile ?
	  }
      
      delete [] distanceHeatmap;
      delete [] orientationHeatmap;
      
      // New generation

      _lifeIterationCount = 0;
      _generationCount++;
    }    
  
  /* Updates */
  updateEnvironmentResources();
  updateAllAgentsEnergyLevel();
  
  // Screenshot ultimate iteration
  
  if( gWorld->getIterations() == gMaxIt-2)
    {
      gDisplayMode = 0;
      gDisplaySensors = true;
    }
}



// Same as in MedeaSpWorldObserver, where it is private
double  MedeaMovingSpWorldObserver::forageReward(double G, double Q_E )
{
  if(Q_E == 0)Q_E=-1.0;
  double b=MedeaSpSharedData::gB;
  double n=MedeaSpSharedData::gN;
  double reward ;
  bool th=true;
  if(th)
    {
      reward=((tanh(b*(G-Q_E*n/100)*Q_E)+1)/(tanh(b)))/2*gEnergyPointValue; 
    }
	else
	  {
		n=n;
		b=b/100;
		double C = (b * exp(n) - exp(-n))/(1-b);
		reward = (exp(n*G*Q_E)+C)/(exp(n)+C)*gEnergyPointValue;
	  }
  if(reward<0.01) reward = 0;
  return reward; 
}


/* Update Methodes */

void MedeaMovingSpWorldObserver::updateEnvironmentResources()
{
  /* Reloading suns */
  for(std::vector<MedeaSpEnergyPoint*>::iterator it = coopEnergyPoints->begin(); it != coopEnergyPoints->end(); it++)
    {
      if(gWorld->getIterations() % (int(MedeaSpSharedData::gSunLifetime)) == 0) 
	{
	  (*it)->setNHarverst(0);
	}
      if((*it)->getType()==1)
	(*it)->setQ_E(MedeaSpSharedData::gNbAllowedRobotsBySun); // Usuall Q_E will be 50
      else
	(*it)->setQ_E(100-MedeaSpSharedData::gNbAllowedRobotsBySun);
    }
}


void MedeaMovingSpWorldObserver::updateAllAgentsEnergyLevel()
{
  int shuffledIndex[gAgentCounter];
  
  for(int i=0; i<gAgentCounter; i++) {shuffledIndex[i]=i;}
  for(int i=0; i<gAgentCounter-1; i++) // exchange randomly indexes with one other
    {	
      int r = i + (rand() % (gAgentCounter-i)); // Random remaining position.
      int tmp = shuffledIndex[i];
      shuffledIndex[i] = shuffledIndex[r]; 
      shuffledIndex[r] = tmp;
    }
  
  // For each agent
  for (int i=0; i != gAgentCounter; i++)
    {
      MedeaMovingSpAgentWorldModel *currAgentWM = dynamic_cast<MedeaMovingSpAgentWorldModel*>(gWorld->getAgent(shuffledIndex[i])->getWorldModel());

      // Checking if active wrt energy level
      if(currAgentWM->getEnergyLevel() <= 0) 
	{
	  currAgentWM->setActiveStatus(false);
	}

      /* We assume that, in this project, both types of energy are reachable, from any point of the environment. That's why we don't need to check if the current agent can harvest from the point where it is located. Anyway, if you want to run the same experience with some energyless points in the environment, you have to implement such a kind of settings. To this end, you may look at the "updateAllAgentsEnergyLevel" in S.Carrignon's "MedeaSpWorldObserver" class (project mEDEA-sp), from which this class is derived. */
      
      if(currAgentWM->getActiveStatus()) 
	{
	  Point2d posRobot(currAgentWM->_xReal,currAgentWM -> _yReal);   // graphic refresh
	  for(std::vector<MedeaSpEnergyPoint*>::iterator it = coopEnergyPoints->begin(); it<coopEnergyPoints->end(); it++)  // for each kind of energy ressource
	    {
	      if((*it)->getActiveStatus())
		{
		  double energyReachable = forageReward(currAgentWM->getAbilityToForage(),(*it)->getType());

		  if(gWorld->getIterations() > MedeaSpSharedData::gNoDenPenTime && energyReachable > 0)
		    {
		      (*it)->setQ_E((*it)->getQ_E()-1);
		      if((*it)->getQ_E() <= 0) {energyReachable = 0;}
		    }

		  double energyAdded;
		  /* Update energy level */
		  if(currAgentWM->getEnergyLevel() + energyReachable > MedeaSpSharedData::gEnergyMax)
		    {
		      currAgentWM->setEnergyLevel(MedeaSpSharedData::gEnergyMax);
		      energyAdded = currAgentWM->getEnergyCounterOfOneRessource((*it)->getType()) + double(MedeaSpSharedData::gEnergyMax) - currAgentWM->getEnergyLevel();
		    }
		  else
		    {
		      currAgentWM->setEnergyLevel(currAgentWM->getEnergyLevel() + energyReachable);

		      energyAdded = currAgentWM->getEnergyCounterOfOneRessource((*it)->getType()) + energyReachable;
		    }
		  currAgentWM->setEnergyCounterOfOneRessource((*it)->getType(),energyAdded);

		  currAgentWM->setDeltaEnergy(currAgentWM->getDeltaEnergy() + energyReachable);
		}
	    }
	}
      
      /* Energy consumption */
      if ((currAgentWM->getEnergyLevel() > 0.0) && (currAgentWM->getActiveStatus()))
	{
	  currAgentWM->setEnergyLevel(currAgentWM->getEnergyLevel() - 1.0);
	}
      currAgentWM->setDeltaEnergy(currAgentWM->getDeltaEnergy()-1.0);

      /* Agents whose energy is going down to zero */
      if((currAgentWM->getEnergyLevel() <= 0.0) && (currAgentWM->getActiveStatus()))
	{
	  currAgentWM->resetEnergyCounter();
	  currAgentWM->setMaturity(1);
	  
	  /** Debug **/
	  if(currAgentWM->_agentId == gAgentIndexFocus && gVerbose) {
	    std::cout << "Agent #" << gAgentIndexFocus << "is revived (energy was 0)." << std::endl;
	  }

	  currAgentWM->resetActiveGenome();
	  currAgentWM->setEnergyLevel(MedeaSpSharedData::gEnergyRevive);
	  currAgentWM->setEnergyCounterOfOneRessource(currAgentWM->getEnergyCounter().size()-1,MedeaSpSharedData::gEnergyRevive);

	  
	  // A dead robot isn't listening for a genome yet

	  currAgentWM->setActiveStatus(false);
	  currAgentWM->setWaitForGenome(false);
	  currAgentWM->getGenomeList().clear();
	  currAgentWM->getGenomeList().empty();
	}
    }
}
