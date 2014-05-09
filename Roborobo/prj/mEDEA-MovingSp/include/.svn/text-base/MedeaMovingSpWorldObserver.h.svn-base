/*
 * MedeaMovingSpWorldObserver.h
 * Roborobo
 *
 */

#ifndef MEDEAMOVINGSPWORLDOBSERVER_H
#define MEDEAMOVINGSPWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "mEDEA-sp/include/MedeaSpWorldObserver.h"
#include "mEDEA-MovingSp/include/MedeaMovingSpAgentWorldModel.h"

class MedeaMovingSpWorldObserver : public MedeaSpWorldObserver
{
 public:
  
  /* Constr/Destr */

  MedeaMovingSpWorldObserver(World *__world);
  ~MedeaMovingSpWorldObserver();


  /* Methodes */

  void step(); // should be rewritten to modify logging files with new parameters of MovingSp genomes

  /** Updates **/
  void updateEnvironmentResources();
  void updateAllAgentsEnergyLevel();


 protected:

  bool _firstIteration;
  int _posNum;

 private:

  double forageReward(double G, double Q_E);
  
};

#endif
