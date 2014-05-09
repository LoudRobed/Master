/*
 * BasicGenome.cpp
 * Roborobo
 *
 */

#include "mEDEA-MovingSp/include/BasicGenome.h"
#include "mEDEA-MovingSp/include/MedeaSpSharedData.h"
#include <cstdlib>
#include <iostream>

/* Constructors & Destructors */

BasicGenome::BasicGenome() // troubles with the numbers of nodes, mustn't be used
{
  std::cout << "BasicGenome \n";
  std::cout<< "nbInput=" << _nbInput << "  nbHidden=" << _nbHidden << " nbOutput=" << _nbOutput << "\n"; 
  /*
  for(int ih=0;ih<(_nbInput * _nbHidden);ih++)
    {
      synapsesIH.push_back(((rand()%800)/400.0)-1.0);
      // std::cout << ih << "\n";
    }

  for(int ho=0;ho<(_nbHidden * _nbOutput);ho++)
    {
      synapsesHO.push_back(((rand()%800)/400.0)-1.0);
    }
 for(int b=0;b<(_nbHidden);b++)
    {
    synapsesB.push_back(((rand()%800)/400.0)-1.0);
    }
  */
}

BasicGenome::BasicGenome(int in, int hi, int ou)
{
  _nbInput = in;
  _nbHidden = hi;
  _nbOutput = ou;

  //BasicGenome();
  for(int ih=0;ih<(_nbInput * _nbHidden);ih++)
    {
      synapsesIH.push_back(((rand()%800)/400.0)-1.0);
      // std::cout << ih << "\n";
    }
  
  for(int ho=0;ho<(_nbHidden * _nbOutput);ho++)
    {
      synapsesHO.push_back(((rand()%800)/400.0)-1.0);
    }
  for(int b=0;b<(_nbHidden);b++)
    {
      synapsesB.push_back(((rand()%800)/400.0)-1.0);
    }
}


BasicGenome::~BasicGenome()
{
}



/* Getters and Setters */

std::vector<double> BasicGenome::getSynapsesIH() 
{
  return synapsesIH;
}

void BasicGenome::setSynapsesIH(std::vector<double> IH)
{
  synapsesIH.clear();
  int s = IH.size();
  for(int i=0; i<s; i++)
    {
      synapsesIH.push_back(IH.at(i));
    }
}


std::vector<double> BasicGenome::getSynapsesHO()
{
  return synapsesHO;
}

void BasicGenome::setSynapsesHO(std::vector<double> HO)
{
  synapsesHO.clear();
  int s = HO.size();
  for(int i=0; i<s; i++)
    {
      synapsesHO.push_back(HO.at(i)); 
    }
}


std::vector<double> BasicGenome::getSynapsesB()
{
  return synapsesB;
}

void BasicGenome::setSynapsesB(std::vector<double> B)
{
  synapsesB.clear();
  int s = B.size();
  for(int i=0; i<s; i++)
    {
      synapsesB.push_back(B.at(i)); 
    }
}

