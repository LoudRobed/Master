/**
 * @file
 * @author Leo Cazenille <leo.cazenille@gmail.com>
 * TODO : Add formal description
 * History :
 *
 *
 */



#include "mEDEA-HGT/include/MedeaHGTAgentObserver.h"
#include "World/World.h"
#include "Utilities/Misc.h"
#include "RoboroboMain/roborobo.h"
#include "mEDEA-HGT/include/MedeaHGTNNControlArchitecture.h"
#include <cmath>
#include "mEDEA-HGT/include/MedeaHGTWorldObserver.h"
#include <string>


// *** *** *** *** ***


MedeaHGTAgentObserver::MedeaHGTAgentObserver( RobotAgentWorldModel *wm )
{
	_wm = (MedeaHGTAgentWorldModel*)wm;

	_wm->_minValue = -1.0;
	_wm->_maxValue = 1.0;

	_wm->_currentSigma = MedeaHGTSharedData::gSigmaRef;

	_wm->resetActiveGenome();

	if ( gVerbose )
	{
		std::cout << "robot #" << _wm->_agentId << "\n" ;
	}
}

MedeaHGTAgentObserver::~MedeaHGTAgentObserver()
{
	// nothing to do.
}

void MedeaHGTAgentObserver::reset()
{
	// nothing to do
}

void MedeaHGTAgentObserver::step()
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
			if ( ( i != _wm->_agentId ) && ( gRadioNetworkArray[_wm->_agentId][i] ) )
			{
				MedeaHGTAgentObserver* targetAgentObserver = dynamic_cast<MedeaHGTAgentObserver*>(gWorld->getAgent(i)->getObserver());
				if ( ! targetAgentObserver )
				{
					std::cerr << "Error from robot " << _wm->_agentId << " : the observer of robot " << i << " isn't a SwarmOnlineObserver" << std::endl;
					exit(1);
				}

				_wm->setEncounteredAgentsDuringGeneration(_wm->getEncounteredAgentsDuringGeneration() + 1);

				if( targetAgentObserver->_wm->getPopulationID() == _wm->getPopulationID() ) {
					if(MedeaHGTSharedData::gActiveHGTBetweenAgentsOfSamePopulation)
						HGTGenomeSpreading(targetAgentObserver);
					else
						SimpleGenomeSpreading(targetAgentObserver);
				} else {
					if(MedeaHGTSharedData::gActiveHGTBetweenAgentsOfDifferentPopulations)
						HGTGenomeSpreading(targetAgentObserver);
					else
						SimpleGenomeSpreading(targetAgentObserver);
				}

			}
		}
	}

	// * Genome selection/replacement

	if( dynamic_cast<MedeaHGTWorldObserver*>(gWorld->getWorldObserver())->getLifeIterationCount() >= MedeaHGTSharedData::gEvaluationTime-1 ) // at the end of a generation
	{
		if (_wm->_agentId == gAgentIndexFocus && gVerbose) // debug
		{
			std::cout << "agent #" << gAgentIndexFocus << " is renewed" << std::endl;
			std::cout << "agent #" << gAgentIndexFocus << " imported " << _wm->_genomesList.size() << " genomes. Energy is " << _wm->getEnergyLevel() << ". Status is "  << _wm->getActiveStatus() << "." <<std::endl;
		}

		// Display the current state of the controller
		gLogFile << "#GIteration: " << gWorld->getIterations() << " #Robot: " << _wm->_agentId
				 << " #Energy: " <<  _wm->getEnergyLevel()
				 << " #DeltaEnergy: " << _wm->getDeltaEnergy()
				 << " #GenomeListSize: " << _wm->_genomesList.size() <<std::endl;

		// note: at this point, agent got energy, whether because it was revived or because of remaining energy.
		if (
				(int)_wm->_genomesList.size() >= MedeaHGTSharedData::gNumberOfGenomeExchangesToStayAlive &&
				_wm->getEncounteredAgentsDuringGeneration() >= MedeaHGTSharedData::gNumberOfEncounteredAgentsToStayAlive
		   )
		{
			// case: more than gNumberOfGenomeExchangesToStayAlive genome(s) imported, random pick.

			pickRandomGenome();
			_wm->setActiveStatus(true); // !N.20100407 : revive takes imported genome if any
		}
		else
		{
			// case: no imported genome - wait for new genome.

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

		if ( MedeaHGTSharedData::gExperimentNumber == 1 || MedeaHGTSharedData::gExperimentNumber == 2 )
		{
			_wm->setDeltaEnergy(0.0); // !n : used to be 10.0
		}

		_wm->setEncounteredAgentsDuringGeneration(0);
	}
}


void MedeaHGTAgentObserver::SimpleGenomeSpreading(MedeaHGTAgentObserver* targetAgentObserver) {
	if ( MedeaHGTSharedData::gDynamicSigma == true ) {
		float dice = float(rand() %100) / 100.0;
		float sigmaSendValue = 0.0;
		if ( ( dice >= 0.0 ) && ( dice < MedeaHGTSharedData::gProbAdd) ) {
			sigmaSendValue = _wm->_currentSigma * ( 1 + MedeaHGTSharedData::gDynaStep );
			if (sigmaSendValue > MedeaHGTSharedData::gSigmaMax) {
				sigmaSendValue = MedeaHGTSharedData::gSigmaMax;
			}
		} else if ( ( dice >= MedeaHGTSharedData::gProbAdd ) && ( dice < MedeaHGTSharedData::gProbAdd+MedeaHGTSharedData::gProbSub) ) {
			sigmaSendValue = _wm->_currentSigma * ( 1 - MedeaHGTSharedData::gDynaStep );
			if (sigmaSendValue < MedeaHGTSharedData::gSigmaMin) {
				sigmaSendValue = MedeaHGTSharedData::gSigmaMin;
			}
		} else {
			std::cerr << "Error : In SwarmOnlineObserver, the rand value is out of bound. The sum of MedeaHGTSharedData::gProbRef and MedeaHGTSharedData::gProbMax is probably not equal to one" << std::endl;
			exit(1);
		}
		targetAgentObserver->writeGenome(_wm->_currentGenome, _wm->_agentId, sigmaSendValue);
	} else {
		targetAgentObserver->writeGenome(_wm->_currentGenome, _wm->_agentId, _wm->_currentSigma);
	}
}

void MedeaHGTAgentObserver::HGTGenomeSpreading(MedeaHGTAgentObserver* targetAgentObserver) {
	// Compute proportion of genome to exchange
	double const diffProportion = MedeaHGTSharedData::gMaxProportionOfGenesTransferedByCrossover - MedeaHGTSharedData::gMinProportionOfGenesTransferedByCrossover;
	assert(diffProportion >= 0.0);
	double const proportionOfGenome = MedeaHGTSharedData::gMinProportionOfGenesTransferedByCrossover +
		((double)rand()/(double)RAND_MAX) * diffProportion;
	assert(proportionOfGenome >= 0.0 && proportionOfGenome <= 1.0);
	unsigned int const nbOfGenesToChange = (unsigned int)((double)(targetAgentObserver->_wm->_currentGenome.size()) * proportionOfGenome);
	assert(nbOfGenesToChange >= 0 && nbOfGenesToChange <= targetAgentObserver->_wm->_currentGenome.size());
	
	// Compute new genome
	std::vector<double> newGenome = targetAgentObserver->_wm->_currentGenome;
	if(MedeaHGTSharedData::gDoHGTByBunch) {
		// Compute beginning of bunch
		unsigned int beginningOfBunch = 0;
		if(newGenome.size() > nbOfGenesToChange)
			beginningOfBunch = rand() % (newGenome.size() - nbOfGenesToChange);
		// Copy portion of local genome into new genome
		for(unsigned int i = 0; i < nbOfGenesToChange; i++) {
			newGenome[i + beginningOfBunch] = _wm->_currentGenome[i + beginningOfBunch];
		}

	} else {
		std::vector<bool> changedGenes(newGenome.size(), false);
		for(unsigned int i = 0; i < nbOfGenesToChange; i++) {
			while(true) {
				// Find gene to change
				unsigned int const geneID = rand() % newGenome.size();
				if(!changedGenes[geneID]) {
					// Copy gene from local genome
					newGenome[geneID] = _wm->_currentGenome[geneID];
					changedGenes[geneID] = true;
				}
			}
		}
	}

	// Compute sigma
	float sigmaSendValue = 0.0;
	if ( MedeaHGTSharedData::gDynamicSigma == true ) {
		float dice = float(rand() %100) / 100.0;
		if ( ( dice >= 0.0 ) && ( dice < MedeaHGTSharedData::gProbAdd) ) {
			sigmaSendValue = _wm->_currentSigma * ( 1 + MedeaHGTSharedData::gDynaStep );
			if (sigmaSendValue > MedeaHGTSharedData::gSigmaMax) {
				sigmaSendValue = MedeaHGTSharedData::gSigmaMax;
			}
		} else if ( ( dice >= MedeaHGTSharedData::gProbAdd ) && ( dice < MedeaHGTSharedData::gProbAdd+MedeaHGTSharedData::gProbSub) ) {
			sigmaSendValue = _wm->_currentSigma * ( 1 - MedeaHGTSharedData::gDynaStep );
			if (sigmaSendValue < MedeaHGTSharedData::gSigmaMin) {
				sigmaSendValue = MedeaHGTSharedData::gSigmaMin;
			}
		} else {
			std::cerr << "Error : In SwarmOnlineObserver, the rand value is out of bound. The sum of MedeaHGTSharedData::gProbRef and MedeaHGTSharedData::gProbMax is probably not equal to one" << std::endl;
			exit(1);
		}
	} else {
		sigmaSendValue = _wm->_currentSigma;
	}

	// Send new genome
	targetAgentObserver->writeGenome(newGenome, _wm->_agentId, sigmaSendValue);
}


void MedeaHGTAgentObserver::pickRandomGenome()
{
	if(_wm->_genomesList.size() != 0)
	{
		int randomIndex = rand()%_wm->_genomesList.size();
		std::map<int, std::vector<double> >::iterator it = _wm->_genomesList.begin();
		while (randomIndex !=0 )
		{
			it ++;
			randomIndex --;
		}

		_wm->_currentGenome = (*it).second;
		if ( MedeaHGTSharedData::gDynamicSigma == true )
		{
			mutateWithBouncingBounds(_wm->_sigmaList[(*it).first]);
		}
		else
		{
			mutateWithBouncingBounds(-1.00);
		}

		_wm->setNewGenomeStatus(true);
		gLogFile << "Info(" << gWorld->getIterations() << ") : robot nb." << _wm->_agentId << " take the genome from the robot nb." << (*it).first << std::endl;

		if (_wm->_agentId == 1 && gVerbose) // debug
			std::cout << "  Sigma is " << _wm->_sigmaList[(*it).first] << "." << std::endl;


		_wm->_genomesList.clear();
	}
}



void MedeaHGTAgentObserver::writeGenome(std::vector<double> genome, int senderId, float sigma)
{
	_wm->_genomesList[senderId] = genome;
	if ( MedeaHGTSharedData::gDynamicSigma == true)
	{
		_wm->_sigmaList[senderId] = sigma;
	}
	/*
	if (_wm->_agentId ==  gAgentIndexFocus ) // debug
	{
		std::cout << "agent #"  << gAgentIndexFocus << " list size is " << _wm->_genomesList.size() << std::endl;
	}
    */
}


void MedeaHGTAgentObserver::mutateWithBouncingBounds( float sigma)
{
	_wm->_genome.clear();

	if ( MedeaHGTSharedData::gDynamicSigma == true)
	{
		_wm->_currentSigma = sigma;
	}
	else
	{
		float randValue = float(rand() % 100) / 100.0;
		if ( ( randValue >= 0.0 ) && ( randValue < MedeaHGTSharedData::gProbRef) )
		{
			_wm->_currentSigma = MedeaHGTSharedData::gSigmaRef;
		}
		else if ( ( randValue >= MedeaHGTSharedData::gProbRef ) && ( randValue < MedeaHGTSharedData::gProbMax+MedeaHGTSharedData::gProbRef) )
		{
			_wm->_currentSigma = MedeaHGTSharedData::gSigmaMax;
		}
		else
		{
			std::cerr << "Error : In SwarmOnlineObserver, the rand value is out of bound. The sum of MedeaHGTSharedData::gProbRef and MedeaHGTSharedData::gProbMax is probably not equal to one" << std::endl;
			exit(1);
		}
	}

	for (unsigned int i = 0 ; i != _wm->_currentGenome.size() ; i++ )
	{
		double value = _wm->_currentGenome[i] + getGaussianRand(0,_wm->_currentSigma);
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
		else if ( value > _wm->_maxValue )
		{
			double range = _wm->_maxValue - _wm->_minValue;
			double overflow = (double)value - _wm->_maxValue;
			overflow = overflow - 2*range * (int)( overflow / (2*range) );
			if ( overflow < range )
				value = _wm->_maxValue - overflow;
			else // overflow btw range and range*2
				value = _wm->_maxValue - range + (overflow-range);
		}

		_wm->_genome.push_back(value);
	}

	_wm->_currentGenome = _wm->_genome;
	gLogFile << std::fixed << std::showpoint << "Info(" << gWorld->getIterations() << ") : robot nb." << _wm->_agentId << " has mutate the genome with sigma : " << _wm->_currentSigma << std::endl;
}

