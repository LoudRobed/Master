/*
 *  MedeaCommSharedData.h
 *  roborobo-online
 *
 *  Created by Nicolas on 3/06/10.
 *
 */

#ifndef MEDEACOMMSHAREDDATA_H
#define MEDEACOMMSHAREDDATA_H

class MedeaCommSharedData {
	
	public: 
	
	static bool gDynamicSigma; //if defined to true, modify sigma in a dynamic way. Each robot start with sigma at gSigmaRef and then igma can change between gSigmaMin and gSigmaMax. If defined to true, gSigmaMin, gProbAdd, gProbSub, gDynaStep should be defined
	static double gSigmaMin; // used with gDynamicSigma defined to true
	static double gProbAdd; //probability to increase the value of the current sigma
	static double gProbSub; //probability to decrease the value of the current sigma
	static double gDynaStep; //step used in the drecrease or increas of the value of sigma
	static double gSigmaRef; // reference value of sigma
	static double gSigmaMax; // maximal value of sigma
	static double gProbRef; // probability of transmitting the current genome mutated with sigma ref
	static double gProbMax; // probability of transmitting the current genome mutatued withe sigma ref
	static int gEvaluationTime; // how long a controller will be evaluated on a robot
//	static int gMaxEvaluation; // how long a controller will be evaluated on a robot UNUSED

	static double energyPointValueMax;
	static bool singleAccess;

	static bool receptionOn; //set to true in order to use the communication. If this value is false, null values are place on the reception sectors
	static int nbReceptionSector; //space of reception is divided in nbReceptionSector equal part
	static double receptionDistance; //distance of reception of the communication of leds (independent from the communication of genome)

	static double gDeadTime;
	static double gEnergyMax; // maximum energy given -- used for initialization, revive and max threshold
	static double gEnergyRevive; // energy given after revive
	static double gEnergyInit; // energy given at start-up
};


#endif
