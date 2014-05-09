/*
 * MedeaMovingSpGenome.h
 * Created by Antoine on 29/03/2012
 *
 * On the previous mEDEA projects, genomes were implemented in tables,
 * and it has already returned efficient results. Anyway, as they 
 * become more and more complex by adding new informations, it becomes
 * easier to be lost while developping them. So, in order to make sure
 * that the programmers still understand what they manipulate, this class
 * gives an object representation of the genomes, where the quality of
 * an attribute (gene) depends on what it is and not where it is in the
 * chain.
 *
 */

#ifndef MEDEAMOVINGSPGENOME_H
#define MEDEAMOVINGSPGENOME_H

#include "mEDEA-MovingSp/include/BasicGenome.h"

class MedeaMovingSpGenome: public BasicGenome
{
 protected:

  /* Features */

  double _gSkill;      // ability to forage
  double _familyMark;  // gene for selection of the next genome
  int _strategy;       // way to chose next genome depending on familyMark

 public:

  /* Constr/Destr */

  MedeaMovingSpGenome();
  MedeaMovingSpGenome(int i, int h, int o);
  ~MedeaMovingSpGenome();


  /* Getters & Setters */

  double getGSkill();
  void setGSkill(double gskill);

  double getFamilyMark();
  void setFamilyMark(double mark);

  int  getStrategy();
  void setStrategy(int strat);
};


#endif //MEDEAMOVINGSPGENOME_H
