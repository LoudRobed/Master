/*
 * MedeaMovingSpAgentWorldModel.h
 * roborobo-online
 *
 * Created by Antoine on 20/03/12
 *
 */

#ifndef MedeaMovingSpAGENTWORDLMODEL_H
#define MedeaMovingSpAGENTWORDLMODEL_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "MedeaMovingSpGenome.h"
#include "MedeaSpAgentWorldModel.h"

class MedeaMovingSpAgentWorldModel : public MedeaSpAgentWorldModel
{
  
 protected:

  std::vector<MedeaMovingSpGenome>  _genomesList;  
  MedeaMovingSpGenome currentGenome;

 public:

  /*** Constructors & Destructors ***/
  
  MedeaMovingSpAgentWorldModel();
  ~MedeaMovingSpAgentWorldModel();


  /*** Getters & Setters ***/
  
  std::vector<MedeaMovingSpGenome> getGenomeList();
  void addGenomeToList(MedeaMovingSpGenome genome);

  int getGenomeListSize();

  MedeaMovingSpGenome getCurrentGenome();
  void setCurrentGenome(MedeaMovingSpGenome genome);
    
  double getDistanceFromClosestRobot();
  void setDistanceFromClosestRobot(double dist);

  double getFamilyMark();
  void setFamilyMark(double mark);

  int getStrategy();
  void setStrategy(int strat);

  double getAbilityToForage();


  /***  Methods ***/

  void resetActiveGenome();
};

#endif
