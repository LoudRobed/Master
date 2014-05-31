/*
 * MedeaMovingSpAgentObserver.h
 * Roborobo
 * 
 */

#ifndef MEDEAMOVINGSPAGENTOBSERVER_H
#define MEDEAMOVINGSPAGENTOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "mEDEA-sp/include/MedeaSpAgentWorldModel.h"
#include "mEDEA-MovingSp/include/MedeaMovingSpAgentWorldModel.h"
#include "mEDEA-sp/include/MedeaSpAgentObserver.h"

class MedeaMovingSpAgentObserver : public MedeaSpAgentObserver
{

 protected:

  MedeaMovingSpAgentWorldModel *_wm;

 public:

  /* Constr/Destr */

  MedeaMovingSpAgentObserver(RobotAgentWorldModel *__wm);
  ~MedeaMovingSpAgentObserver();


  /* Methodes */

  void selectNextGenome();    // Used to select the favorite genome on the list depending on the selection strategy
  
  void writeGenome(MedeaMovingSpGenome genome, float sigma);
  
  void step();
 
  void checkGenomeList();
  
  void pickRandomGenome();

  void mutateWithBouncingBounds(float sigma);

 private:

  double bouncing(double value);

};

#endif
