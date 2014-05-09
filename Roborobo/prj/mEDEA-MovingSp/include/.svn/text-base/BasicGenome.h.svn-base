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

#ifndef BASICGENOME_H
#define BASICGENOME_H

#include <vector>        // Provides the STL vector class

class BasicGenome 
{
  
 protected:
  
  /* Features */
  
  int _nbInput;      // Number of inputs of the MLP
  int _nbOutput;     // Number of outputs of the MLP
  int _nbHidden;     // Number of hidden nodes in the MLP

  std::vector<double> synapsesIH;
  std::vector<double> synapsesHO;
  std::vector<double> synapsesB;

 public:

  /* Constructors & Destructors */

  BasicGenome();
  BasicGenome(int in, int hi, int ou);
  ~BasicGenome();

  
  /* Getters & Setters */
  
  std::vector<double> getSynapsesIH();
  void setSynapsesIH(std::vector<double> IH);
  
  std::vector<double> getSynapsesHO();
  void setSynapsesHO(std::vector<double> HO);
  
  std::vector<double> getSynapsesB();
  void setSynapsesB(std::vector<double> B);
  
};


#endif // BASICGENOME_H
