/*
 * MedeaMovingSpGenome.cpp
 * Roborobo
 *
 */

#include "mEDEA-MovingSp/include/MedeaMovingSpGenome.h"
#include <cstdlib>
#include <iostream>


/* Constructors & Destructors */

MedeaMovingSpGenome::MedeaMovingSpGenome() : BasicGenome()
{
  _gSkill = ((rand()%800) / 400.0) - 1.0; 
  _familyMark = ((rand()%800) / 400.0) - 1.0; 
  _strategy = 1;
}

MedeaMovingSpGenome::MedeaMovingSpGenome(int i, int  h, int o) : BasicGenome(i, h, o)
{
  _gSkill = ((rand()%800) / 400.0) - 1.0; 
  _familyMark = ((rand()%800) / 400.0) - 1.0; 
  _strategy = 1;
}

MedeaMovingSpGenome::~MedeaMovingSpGenome() {}


/* Getters & Setters */

double MedeaMovingSpGenome::getGSkill()
{
  return _gSkill;
}

void MedeaMovingSpGenome::setGSkill(double gskill)
{
  _gSkill = gskill;
}


double MedeaMovingSpGenome::getFamilyMark()
{
  return _familyMark;
}

void MedeaMovingSpGenome::setFamilyMark(double mark)
{
  _familyMark = mark;
}


int MedeaMovingSpGenome::getStrategy()
{
  return _strategy;
}

void MedeaMovingSpGenome::setStrategy(int strat)
{
  _strategy = strat;
}

