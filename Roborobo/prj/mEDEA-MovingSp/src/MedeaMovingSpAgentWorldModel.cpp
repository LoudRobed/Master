/*
 *  MedeaMovingSpAgentWorldModel.cpp
 *  roborobo-online
 *
 *  Created by Antoine on 21/03/12.
 *
 */

#include "mEDEA-MovingSp/include/MedeaMovingSpAgentWorldModel.h"
#include "mEDEA-sp/include/MedeaSpSharedData.h"

/*** Constructors & Destructors ***/

MedeaMovingSpAgentWorldModel::MedeaMovingSpAgentWorldModel() : MedeaSpAgentWorldModel()
{
  int nbIn =  8 +/*_sensorCount*/ + 1 + MedeaSpSharedData::gNbTypeResource *2 + 1;
  int nbHi = 5;
  int nbOu = 2;
  currentGenome = MedeaMovingSpGenome(nbIn,nbHi,nbOu);
}

MedeaMovingSpAgentWorldModel::~MedeaMovingSpAgentWorldModel()
{
}



/*** Getters & Setters ***/

std::vector<MedeaMovingSpGenome> MedeaMovingSpAgentWorldModel::getGenomeList()
{
  return _genomesList;
}

void MedeaMovingSpAgentWorldModel::addGenomeToList(MedeaMovingSpGenome genome)
{
  _genomesList.push_back(genome);
}

int MedeaMovingSpAgentWorldModel::getGenomeListSize()
{
  return _genomesList.size();
}


MedeaMovingSpGenome MedeaMovingSpAgentWorldModel::getCurrentGenome()
{
  return currentGenome;
}

void MedeaMovingSpAgentWorldModel::setCurrentGenome(MedeaMovingSpGenome genome)
{
  currentGenome = genome;
}

/*
double MedeaMovingSpAgentWorldModel::getDistanceFromClosestRobot() 
{
  return _distanceFromClosestRobot;
}
void MedeaMovingSpAgentWorldModel::setDistanceFromClosestRobot(double dist)
{
  _distanceFromClosestRobot = dist;
}
*/

double MedeaMovingSpAgentWorldModel::getFamilyMark()
{
  return currentGenome.getFamilyMark();
}
void MedeaMovingSpAgentWorldModel::setFamilyMark(double mark)
{
  currentGenome.setFamilyMark(mark);
}

int MedeaMovingSpAgentWorldModel::getStrategy()
{
  return currentGenome.getStrategy();
}
void MedeaMovingSpAgentWorldModel::setStrategy(int strat)
{
  currentGenome.setStrategy(strat);  
}


double MedeaMovingSpAgentWorldModel::getAbilityToForage()
{
  return currentGenome.getGSkill();
}
/*** Methods ***/


void MedeaMovingSpAgentWorldModel::resetActiveGenome()  // pour le moment, d'après la version antérieure
{
  int nbInput = 8 /*_sensorCount*/ + 1 + MedeaSpSharedData::gNbTypeResource *2 + 1 ; //sensors + floorSensor + energyDirection * gNbTypeResource +  energyDistance  * gNbTypeResource+ energyLevel
  int nbHidden = 5; //_nbHiddenNeurons;
  int nbOutput = 2 ; // rotation + velocity 
  
  
  currentGenome = MedeaMovingSpGenome(nbInput,nbHidden,nbOutput);
  setNewGenomeStatus(true);
  _genomesList.clear();
}
