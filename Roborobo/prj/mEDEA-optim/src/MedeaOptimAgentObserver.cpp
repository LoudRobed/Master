/*
 *  MedeaOptimAgentObserver.cpp
 *  Roborobo
 *
 *  current dev: Nicolas on 19/1/2011
 *
 */


#include "mEDEA-optim/include/MedeaOptimAgentObserver.h"

#include "World/World.h"
#include "Utilities/Misc.h"
#include "RoboroboMain/roborobo.h"
#include "mEDEA-optim/include/MedeaOptimPerceptronControlArchitecture.h"
#include <cmath>


#include "mEDEA-optim/include/MedeaOptimWorldObserver.h"


// *** *** *** *** ***


MedeaOptimAgentObserver::MedeaOptimAgentObserver( RobotAgentWorldModel *__wm )
{

	_wm = (MedeaOptimAgentWorldModel*)__wm;

	_wm->_minValue = -1.0;
	_wm->_maxValue = 1.0;

	_wm->_currentSigma = MedeaOptimSharedData::gSigmaRef;

	gProperties.checkAndGetPropertyValue("nbHiddenNeurons",&_wm->_nbHiddenNeurons,true);
	
	_wm->resetActiveGenome();

	_wm->setFitness(0.0);
	
	if ( gVerbose )
	{
		std::cout << "robot #" << _wm->_agentId << "\n" ;	
	}
}

MedeaOptimAgentObserver::~MedeaOptimAgentObserver()
{
	// nothing to do.
}

void MedeaOptimAgentObserver::reset()
{
	// nothing to do 
}

void MedeaOptimAgentObserver::step()
{
	// debug verbose
	if ( gVerbose && gInspectAgent && gAgentIndexFocus == _wm->_agentId )
	{
		std::cout << "target: " << _wm->getEnergyPointDirectionAngleValue() << std::endl;
	}

	// * genome spreading (current agent broadcasts its genome to all neighbors - ie. write its own genome in genomeList on neighboring agents)
	// note: could be move in WorldObserver to go from N^2 to Summation(N) complexity
	
	if ( _wm->getActiveStatus() == true )  	// broadcast only if agent is active (ie. not just revived) and deltaE>0.
	{
		for (int i = 0 ; i < gAgentCounter ; i++)
		{
			if ( ( i != _wm->_agentId ) && ( gRadioNetworkArray[_wm->_agentId][i] ) ) //&& (_wm->getEnergyLevel() > 0.0) ) --> always true as status is active
			{
				MedeaOptimAgentObserver* targetAgentObserver = dynamic_cast<MedeaOptimAgentObserver*>(gWorld->getAgent(i)->getObserver());
				if ( ! targetAgentObserver )
				{
					std::cerr << "Error from robot " << _wm->_agentId << " : the observer of robot " << i << " isn't a SwarmOnlineObserver" << std::endl;
					exit(1);
				}
				if ( MedeaOptimSharedData::gDynamicSigma == true )
				{
					float dice = float(rand() %100) / 100.0;
					float sigmaSendValue = 0.0;
					if ( ( dice >= 0.0 ) && ( dice < MedeaOptimSharedData::gProbAdd) )
					{
						sigmaSendValue = _wm->_currentSigma * ( 1 + MedeaOptimSharedData::gDynaStep );
						if (sigmaSendValue > MedeaOptimSharedData::gSigmaMax)
						{
							sigmaSendValue = MedeaOptimSharedData::gSigmaMax;
						}
					}
					else if ( ( dice >= MedeaOptimSharedData::gProbAdd ) && ( dice < MedeaOptimSharedData::gProbAdd+MedeaOptimSharedData::gProbSub) )
					{
						sigmaSendValue = _wm->_currentSigma * ( 1 - MedeaOptimSharedData::gDynaStep );
						if (sigmaSendValue < MedeaOptimSharedData::gSigmaMin)
						{
							sigmaSendValue = MedeaOptimSharedData::gSigmaMin;
						}
					}
					else
					{
						std::cerr << "Error : In SwarmOnlineObserver, the rand value is out of bound. The sum of MedeaOptimSharedData::gProbRef and MedeaOptimSharedData::gProbMax is probably not equal to one" << std::endl;
						exit(1);
					}
					//targetAgentObserver->writeGenome(_wm->_currentGenome, _wm->_agentId, sigmaSendValue);
					targetAgentObserver->writeGenome(_wm->_genome, _wm->_agentId, sigmaSendValue, _wm->getFitness()); // note: instant fitness
				}
				else
				{
					//targetAgentObserver->writeGenome(_wm->_currentGenome, _wm->_agentId, _wm->_currentSigma);
					targetAgentObserver->writeGenome(_wm->_genome, _wm->_agentId, _wm->_currentSigma, _wm->getFitness()); // note: instant fitness
				}
			}
		}
	}

	// * Genome selection/replacement

	if( dynamic_cast<MedeaOptimWorldObserver*>(gWorld->getWorldObserver())->getLifeIterationCount() >= MedeaOptimSharedData::gEvaluationTime-1 ) // at the end of a generation
	{
		// Display the current state of the controller
		gLogFile << "#GIteration: " << gWorld->getIterations() << " #Robot: " << _wm->_agentId
				 << " #Energy: " <<  _wm->getEnergyLevel()
				 << " #DeltaEnergy: " << _wm->getDeltaEnergy()
				 << " #GenomeListSize: " << _wm->_genomesList.size() <<std::endl;
			
		// note: at this point, agent got energy, wether because it was revived or because of remaining energy.
		if (_wm->_genomesList.size() > 0)
		{
			// case: 1+ genome(s) imported. Either (a) random pick (medea selection scheme) OR (b) fitness-based selection (user-defined objective case)
			// Then: agent is switched back to active (may not be needed)
			
//			if ( _wm->_agentId == gAgentIndexFocus ) // && gVerbose) // debug
//			{
//				std::cout << "** call selection operator **\n" << std::flush;
//			}
			
			//if ( ranf() < 0.5 )  // CURRENTLY: p=0.5
			//	pickRandomGenome();
			//else
				performGenomeSelectionWithTournament(7);
					
			_wm->setActiveStatus(true); // start again with new imported genome
		}
		else
		{
			// case: no imported genome - wait for new genome. -- agent continues being considered as inactive.
			
			gLogFile << "Info(" << gWorld->getIterations() << ") : robot nb." << _wm->_agentId
			//					<< " is trying a whole new genome" << std::endl;
								<< " is waiting for a new genome" << std::endl;

			_wm->resetActiveGenome(); // optional -- could be set to zeroes.
			_wm->setActiveStatus(false); // inactive robot *must* import a genome from others (ie. no restart).
		}
		
		//log the genome
		
		if ( _wm->getActiveStatus() == true )
		{
			gLogFile << "Info("<< gWorld->getIterations() <<") : robot nb."<< _wm->_agentId << " use genome :";
			for(unsigned int i=0; i<_wm->_genome.size(); i++)
			{
				gLogFile << std::fixed << std::showpoint << _wm->_genome[i] << " ";
			}
			gLogFile << std::endl;
		}

		//Re-initialize the main parameters

		_wm->setDeltaEnergy(0.0);
		

		//if ( gAgentIndexFocus == _wm->_agentId )				// debug: display nb of harvested energy points
		//	std::cout << "((" << _wm->getFitness() << "))";
		
		_wm->setFitness(0.0); // reset fitness value
	}	
}

// Apply tournament selection
void MedeaOptimAgentObserver::performGenomeSelectionWithTournament( int tournamentSize )
{

	if ( _wm->_genomesList.size() == 0 ) // should always be true (pre-condition to call)
	{
		std::cout << "[critical] AgentObserver::performGenomeSelectionWithTournament() called with an empty genome list." << std::endl;
		exit (-1);
	}
	

	// perform selection

	double bestFitness;
	int randomIndex;
	
	randomIndex = rand() % _wm->_genomesList.size();

//	if ( _wm->_agentId == gAgentIndexFocus ) // && gVerbose) // debug
//	{
//		std::cout << "\n{" << (randomIndex) << "/" << _wm->_genomesList.size() << ";" << _wm->_fitnessList.size() << ";" << _wm->_sigmaList.size() << "}\n";
//		std::map< int, double >::iterator it = _wm->_fitnessList.begin();
//		for ( int i = 0 ; i != _wm->_fitnessList.size() ; i++ )
//		{
//			std::cout << "it(" << i << "/"<<_wm->_fitnessList.size()<<") => robot no." << it->first << " with fitness " << _wm->_fitnessList[it->first] << " and sigma " << _wm->_sigmaList[it->first] << "\n" << std::flush;
//			it++;
//		}	
//	}
	
	std::map< int, double >::iterator itFitnessBest = _wm->_fitnessList.begin();
	for ( int i = 0 ; i != randomIndex ; i++ )
		itFitnessBest++;

	bestFitness = itFitnessBest->second;
	// itFitnessBest->second = FLOAT_MIN; // implement no-redraw  -- WARNING: ASSUME MAXIMIZATION PROBLEM
	
	for ( int i = 1 ; i < tournamentSize ; i++ )
	{
		randomIndex = rand() % _wm->_genomesList.size();

		std::map< int, double >::iterator itFitnessChallenger = _wm->_fitnessList.begin();
		for ( int i = 0 ; i != randomIndex ; i++ )
			itFitnessChallenger++;

		if ( itFitnessChallenger->second > bestFitness ) // strictly above
		{
			itFitnessBest = itFitnessChallenger;
			bestFitness = itFitnessBest->second;
			// ifFitnessChallenger->second = FLOAT_MIN; // implement no-redraw  -- WARNING: ASSUME MAXIMIZATION PROBLEM
		}
	}

	// update values for current agent
	// note: at this point, the important elements are: _wm->_genomesList[it->first], bestFitness and sigma[it->first] -- note it->first is ok for all list (same index numbering)

	_wm->_genome = _wm->_genomesList[itFitnessBest->first];
		
	// apply mutation
			
	if ( MedeaOptimSharedData::gDynamicSigma == true )
	{
		mutateWithBouncingBounds(_wm->_sigmaList[itFitnessBest->first]);  // sigma will be updated in WM in mutateWithBouncingBox method call.
	}
	else
	{
		mutateWithBouncingBounds(-1.00);
	}
			
	gLogFile << "Info(" << gWorld->getIterations() << ") : robot nb." << _wm->_agentId << " take the genome from the robot nb." << (*itFitnessBest).first << std::endl; // WARNING - correct sentence is "...from mating #"...

//	if ( _wm->_agentId == gAgentIndexFocus ) // && gVerbose) // debug
//	{
//		std::cout << "=> Picked robot no." << itFitnessBest->first << " with fitness " << _wm->_fitnessList[itFitnessBest->first] << "(="<< itFitnessBest->second << ") and sigma " << _wm->_sigmaList[itFitnessBest->first] << "\n" << std::flush;
//		std::cout << "=> genomeList.size before clearing is " << _wm->_genomesList.size() << std::endl << std::flush;
//	}


	_wm->setNewGenomeStatus(true);
	_wm->setFitness(0);
	
	_wm->_genomesList.clear();

//	if ( _wm->_agentId == gAgentIndexFocus ) // && gVerbose) // debug
//	{
//		std::cout << "=> genomeList.size after clearing is " << _wm->_genomesList.size() << std::endl << std::flush;
//		std::cout << "=> fitnessList.size before clearing is " << _wm->_fitnessList.size() << std::endl << std::flush;
//	}
	
	_wm->_fitnessList.clear();
	_wm->_sigmaList.clear();
	
//	if ( _wm->_agentId == gAgentIndexFocus ) // && gVerbose) // debug
//	{
//		std::cout << "=> fitnessList.size after clearing is " << _wm->_fitnessList.size() << std::endl  << std::flush;
//	}

	
}

void MedeaOptimAgentObserver::performGenomeSelectionWithPGTA_geneBased()
{
	// ...
}


void MedeaOptimAgentObserver::performGenomeSelectionWithPGTA_genomeBased()
{
	// ...
}


void MedeaOptimAgentObserver::pickRandomGenome()
{


//	if ( _wm->_agentId == gAgentIndexFocus ) // && gVerbose) // debug
//	{
//		std::cout << "\n{ genomeList.size = " << _wm->_genomesList.size() << ";" << _wm->_fitnessList.size() << ";" << _wm->_sigmaList.size() << "}\n";
//		std::map< int, double >::iterator it = _wm->_fitnessList.begin();
//		for ( int i = 0 ; i != _wm->_fitnessList.size() ; i++ )
//		{
//			std::cout << "it(" << i << "/"<<_wm->_fitnessList.size()<<") => robot no." << it->first << " with fitness " << _wm->_fitnessList[it->first] << " and sigma " << _wm->_sigmaList[it->first] << "\n" << std::flush;
//			it++;
//		}	
//	}

	if(_wm->_genomesList.size() == 0) // should always be true (pre-condition to call)
	{
		std::cout << "[critical] AgentObserver::pickRandomGenome() called with an empty genome list." << std::endl << std::flush;
		exit (-1);
	}
	
	int randomIndex = rand()%_wm->_genomesList.size();
	std::map<int, std::vector<double> >::iterator it = _wm->_genomesList.begin();
	while (randomIndex !=0 )
	{
		it ++;
		randomIndex --;
	}

	//_wm->_currentGenome = (*it).second;
	_wm->_genome = (*it).second;
			
	if ( MedeaOptimSharedData::gDynamicSigma == true )
	{
		mutateWithBouncingBounds(_wm->_sigmaList[(*it).first]);
	}
	else
	{
		mutateWithBouncingBounds(-1.00);
	}
			
	_wm->setNewGenomeStatus(true); 
	gLogFile << "Info(" << gWorld->getIterations() << ") : robot nb." << _wm->_agentId << " take the genome from the robot nb." << (*it).first << std::endl << std::flush;
			
//	if (_wm->_agentId == 1 && gVerbose) // debug
//		std::cout << "  Sigma is " << _wm->_sigmaList[(*it).first] << "." << std::endl;

//	if ( _wm->_agentId == gAgentIndexFocus ) // && gVerbose) // debug
//	{
//		std::cout << "=> Picked robot no." << it->first << " with fitness " << _wm->_fitnessList[it->first] << "and sigma " << _wm->_sigmaList[it->first] << "\n" << std::flush;
//		std::cout << "=> genomeList.size before clearing is " << _wm->_genomesList.size() << std::endl << std::flush;
//	}

	_wm->_genomesList.clear();	
	_wm->_fitnessList.clear(); // added 20100127
	_wm->_sigmaList.clear();   // added 20100127 (not critical, but should have been done before)

//	if ( _wm->_agentId == gAgentIndexFocus ) // && gVerbose) // debug
//	{
//		std::cout << "=> fitnessList.size after clearing is " << _wm->_fitnessList.size() << std::endl << std::flush;
//	}

}



void MedeaOptimAgentObserver::writeGenome(std::vector<double> genome, int senderId, float sigma, double fitness)
{
	_wm->_genomesList[senderId] = genome;
	_wm->_fitnessList[senderId] = fitness;
	if ( MedeaOptimSharedData::gDynamicSigma == true)
	{
		_wm->_sigmaList[senderId] = sigma;
	}

//	if (_wm->_agentId == gAgentIndexFocus ) // debug
//	{
//		std::cout << "agent #"  << gAgentIndexFocus << " stores genome(agent #" << senderId << ") -- genomeList.size is " << _wm->_genomesList.size() << std::endl;
//	}

}


void MedeaOptimAgentObserver::mutateWithBouncingBounds( float sigma)
{
	std::vector<double> genome; // store new genome values
	
	if ( MedeaOptimSharedData::gDynamicSigma == true)
	{
		_wm->_currentSigma = sigma; // update sigma
	}
	else
	{
		float randValue = float(rand() %100) / 100.0;
		if ( ( randValue >= 0.0 ) && ( randValue < MedeaOptimSharedData::gProbRef) )
		{
			_wm->_currentSigma = MedeaOptimSharedData::gSigmaRef;
		}
		else if ( ( randValue >= MedeaOptimSharedData::gProbRef ) && ( randValue < MedeaOptimSharedData::gProbMax+MedeaOptimSharedData::gProbRef) )
		{
			_wm->_currentSigma = MedeaOptimSharedData::gSigmaMax;
		}
		else
		{
			std::cerr << "Error : In SwarmOnlineObserver, the rand value is out of bound. The sum of MedeaOptimSharedData::gProbRef and MedeaOptimSharedData::gProbMax is probably not equal to one" << std::endl;
			exit(1);
		}
	}
	
	for (unsigned int i = 0 ; i != _wm->_genome.size() ; i++ )
	{
		double value = _wm->_genome[i] + getGaussianRand(0,_wm->_currentSigma);

		// bouncing upper/lower bounds
		if ( value < _wm->_minValue )
		{
			double range = _wm->_maxValue - _wm->_minValue;
			double overflow = - ( (double)value - _wm->_minValue );
			overflow = overflow - 2*range * (int)( overflow / (2*range) );
			if ( overflow < range )
				value = _wm->_minValue + overflow;
			else // overflow btw range and range*2
				value = _wm->_minValue + range - (overflow-range);
		}
		else
			if ( value > _wm->_maxValue )
			{
				double range = _wm->_maxValue - _wm->_minValue;
				double overflow = (double)value - _wm->_maxValue;
				overflow = overflow - 2*range * (int)( overflow / (2*range) );
				if ( overflow < range )
					value = _wm->_maxValue - overflow;
				else // overflow btw range and range*2
					value = _wm->_maxValue - range + (overflow-range);
			}
		
		genome.push_back(value);
	}
	
	// update genome
	_wm->_genome.clear();
	_wm->_genome = genome;
	
	gLogFile << std::fixed << std::showpoint << "Info(" << gWorld->getIterations() << ") : robot nb." << _wm->_agentId << " has mutate the genome with sigma : " << _wm->_currentSigma << std::endl;
}
