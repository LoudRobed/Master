/*
 *  SpikeAntsWorldObserver.h
 *  roborobo-online
 *
 *  Created by Nicolas on 27/05/10.
 *
 */



#ifndef SPIKEANTSWORLDOBSERVER_H
#define SPIKEANTSWORLDOBSERVER_H

#include "RoboroboMain/common.h"
#include "RoboroboMain/roborobo.h"

#include "Observers/WorldObserver.h"

class World;

class SpikeAntsWorldObserver : public WorldObserver
{
private:
  bool _saRecFocPot;
  bool _saRecAgPos;
protected:

public:
  SpikeAntsWorldObserver( World *__world );
  ~SpikeAntsWorldObserver();
  
  void reset();
  void step();
  
};

#endif

