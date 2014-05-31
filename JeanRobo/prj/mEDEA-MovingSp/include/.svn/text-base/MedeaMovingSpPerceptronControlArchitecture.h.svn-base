/*
 * MedeaMovingSpPerceptronControlArchitecture.h
 * Roborobo
 *
 * Created by Antoine on 04/04/2012
 *
 */

#ifndef MedeaMovingSpENERGYPERCEPTRONCONTROLARCHITECTURE_H
#define MedeaMovingSpENERGYPERCEPTRONCONTROLARCHITECTURE_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"
#include "Utilities/SDL_gfxRoborobo.h"

#include "BehaviorControlArchitectures/BehaviorControlArchitecture.h"
#include "mEDEA-MovingSp/include/MedeaSpPerceptronControlArchitecture.h"
#include "mEDEA-MovingSp/include/MedeaMovingSpGenome.h"
#include "mEDEA-MovingSp/include/MedeaMovingSpAgentWorldModel.h"
#include "mEDEA-MovingSp/include/MedeaMovingSpAgentObserver.h"

class MedeaMovingSpPerceptronControlArchitecture : public BehaviorControlArchitecture
{

 private:

  /* Features */

  int _iteration;
  MedeaMovingSpAgentWorldModel *_wm;

  MedeaMovingSpGenome _parameters; // vector<double> in mother class
  int _nbHiddenNeurons;

  //void searchClosestEnergyPoint(Point2d posRobot, std::vector<Point2d> energyPoints); // useless until now, but will maybe be used later

 public:

  /* Constructors & Destructors */
  MedeaMovingSpPerceptronControlArchitecture(RobotAgentWorldModel *__wm);
  ~MedeaMovingSpPerceptronControlArchitecture();


  /* Methods */

  void reset();
  void step();

};

#endif
