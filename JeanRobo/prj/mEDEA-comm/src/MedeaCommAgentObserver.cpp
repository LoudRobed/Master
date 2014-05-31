/*
 *  MedeaCommAgentObserver.cpp
 *  Roborobo
 *
 *  imported from Jean-Marc on 15/12/09
 *  current dev: Nicolas on 1/4/2009
 *
 */


#include "mEDEA-comm/include/MedeaCommAgentObserver.h"

#include "World/World.h"
#include "Utilities/Misc.h"
#include "RoboroboMain/roborobo.h"
#include "mEDEA-comm/include/MedeaCommPerceptronControlArchitecture.h"
#include <cmath>


#include "mEDEA-comm/include/MedeaCommWorldObserver.h"


// *** *** *** *** ***


MedeaCommAgentObserver::MedeaCommAgentObserver( RobotAgentWorldModel *__wm )
{
	_wm = (MedeaCommAgentWorldModel*)__wm;

	_wm->_minValue = -0.0;
	_wm->_maxValue = 0.0;

	_wm->_currentSigma = MedeaCommSharedData::gSigmaRef;
	_wm->setLifeTime(1);
	_wm->setWaitForGenome(false);
	_wm->setActiveStatus(true);
	_wm->_genomesList.clear();
	_wm->_sigmaList.clear();

	gProperties.checkAndGetPropertyValue("nbHiddenNeurons",&_wm->_nbHiddenNeurons,true);
	gProperties.checkAndGetPropertyValue("gNbMaxGenomeSelection",&nbMaxGenomeSelection,true);
	
	_wm->resetActiveGenome();
	_wm->setMaturity(0);
	
	if ( gVerbose )
	{
		std::cout << "robot #" << _wm->_agentId << "\n" ;	
	}
}

MedeaCommAgentObserver::~MedeaCommAgentObserver()
{
	// nothing to do.
}

void MedeaCommAgentObserver::reset()
{
	// nothing to do 
}

void MedeaCommAgentObserver::step()
{
	// debug verbose
	if ( gVerbose && gInspectAgent && gAgentIndexFocus == _wm->_agentId )
	{
		std::cout << "target: " << _wm->getAngleToClosestEnergyPoint() << std::endl;
	}

	// at the end of a generation
	if( 
		(_wm->getLifeTime() >= MedeaCommSharedData::gEvaluationTime && _wm->getWaitForGenome() && !(_wm->getActiveStatus()))
		||
		(_wm->getLifeTime() >= MedeaCommSharedData::gEvaluationTime && _wm->getActiveStatus())
	) 
	{		
		checkGenomeList(); //here we look if the genome list is empty. If yes, the robot will wait again during a generation, 
		_wm->setLifeTime(0);//if not the robot will be activated and able to move again. a both case it'll stay in this state during a generation, that's why lifetime is set back to 0.
		
	}

	// at the end of the dead time (maby redondancy between control variables), the robot state should be in a listened mode (waitforgeneome)
	if(_wm->getLifeTime() >= (MedeaCommSharedData::gEvaluationTime*(MedeaCommSharedData::gDeadTime+ double(rand()%10)/10.0)) && !(_wm->getWaitForGenome()) && !(_wm->getActiveStatus()))
	{
		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " listen" << std::endl;
		_wm->setWaitForGenome(true);
		_wm->setLifeTime(0);
	}
	
	//handle the maturity concept
	//
	if( _wm->getActiveStatus() && _wm->getMaturity() > 0)
	{
		_wm->setMaturity(_wm->getMaturity()+1);
		if(_wm->getMaturity() > MedeaCommSharedData::gEnergyRevive +10 )
		{
			_wm->setMaturity(0); //the robot will be able to spread its genome again
			gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " mature" << std::endl;
		}
		
	}


	//broadcast genome only if mature and active
	if ( _wm->getActiveStatus() == true && _wm->getMaturity()<=0)
	{
		for (int i = 0 ; i < gAgentCounter ; i++)
		{
			MedeaCommAgentObserver* targetAgentObserver = dynamic_cast<MedeaCommAgentObserver*>(gWorld->getAgent(i)->getObserver());
			if ( ( i != _wm->_agentId ) && ( gRadioNetworkArray[_wm->_agentId][i] ) ) //&& (_wm->getEnergyLevel() > 0.0) ) --> always true as status is active
			{
				if ( ! targetAgentObserver )
				{
					std::cerr << "Error from robot " << _wm->_agentId << " : the observer of robot " << i << " isn't a SwarmOnlineObserver" << std::endl;
					exit(1);
				}

				if((targetAgentObserver->_wm->getActiveStatus() ) || targetAgentObserver->_wm->getWaitForGenome())
				{
					if ( MedeaCommSharedData::gDynamicSigma == true )
					{
						float dice = float(rand() %100) / 100.0;
						float sigmaSendValue = 0.0;
						if ( ( dice >= 0.0 ) && ( dice < MedeaCommSharedData::gProbAdd) )
						{
							sigmaSendValue = _wm->_currentSigma * ( 1 + MedeaCommSharedData::gDynaStep );
							if (sigmaSendValue > MedeaCommSharedData::gSigmaMax)
							{
								sigmaSendValue = MedeaCommSharedData::gSigmaMax;
							}
						}
						else if ( ( dice >= MedeaCommSharedData::gProbAdd ) && ( dice < MedeaCommSharedData::gProbAdd+MedeaCommSharedData::gProbSub) )
						{
							sigmaSendValue = _wm->_currentSigma * ( 1 - MedeaCommSharedData::gDynaStep );
							if (sigmaSendValue < MedeaCommSharedData::gSigmaMin)
							{
								sigmaSendValue = MedeaCommSharedData::gSigmaMin;
							}
						}
						else
						{
							std::cerr << "Error : In SwarmOnlineObserver, the rand value is out of bound. The sum of MedeaCommSharedData::gProbRef and MedeaCommSharedData::gProbMax is probably not equal to one" << std::endl;
							exit(1);
						}
						targetAgentObserver->writeGenome(_wm->_currentGenome, _wm->_agentId + 1000 * _wm->getDateOfBirth(),sigmaSendValue);
					}
					else
					{
						targetAgentObserver->writeGenome(_wm->_currentGenome, _wm->_agentId + 1000 * _wm->getDateOfBirth() , _wm->_currentSigma);
					}
				}
			}
		}
	}

	//receive light cocmmunication from other robots when the robot is active
	if ( _wm->getActiveStatus() == true )
	{
		std::vector<double> receivedCommunication;
		for (int sector = 0 ; sector < MedeaCommSharedData::nbReceptionSector ; sector++)
		{
			receivedCommunication.push_back(0.0);
		}
		if (MedeaCommSharedData::receptionOn == true)
		{
			for (int i = 0 ; i < gAgentCounter ; i++)
			{
				MedeaCommAgentWorldModel *targetAgentWorldModel = dynamic_cast<MedeaCommAgentWorldModel*>( gWorld->getAgent(i)->getWorldModel() );
				Point2d posRobot(_wm->_xReal,_wm->_yReal);
				Point2d targetRobot(targetAgentWorldModel->getXReal(),targetAgentWorldModel->getYReal());
				double distance = getEuclidianDistance(posRobot,targetRobot);
				if ((distance < MedeaCommSharedData::receptionDistance) && (targetAgentWorldModel->getActiveStatus() == true) )
				{
					double angle = (atan2(targetRobot.y - posRobot.y , targetRobot.x - posRobot.x)/M_PI)*180.0;
					double diffAngle = angle - _wm->_agentAbsoluteOrientation;
					if ( diffAngle < -180.0 )
					{
						diffAngle += 360.0 ; 
					}
					if ( diffAngle > 180.0 )
					{
						diffAngle -= 360.0 ;
					}
					for (int sector = 0 ; sector < MedeaCommSharedData::nbReceptionSector ; sector++)
					{
						double lowBound = -180.0 + (double)sector*(360.0/(double)MedeaCommSharedData::nbReceptionSector);
						double highBound = -180.0+(double)(sector+1)*(360.0/(double)MedeaCommSharedData::nbReceptionSector);
						if (lowBound <= diffAngle && diffAngle < highBound)
						{
							receivedCommunication[sector] += targetAgentWorldModel->getCommunication();
						}
					}
				}
			}
		}
		for (int sector = 0 ; sector < MedeaCommSharedData::nbReceptionSector ; sector++)
		{
			receivedCommunication[sector] = receivedCommunication[sector] / gAgentCounter;
		}
		_wm->setReceivedCommunication(receivedCommunication);
	}

	_wm->setLifeTime(_wm->getLifeTime()+1);
}



void MedeaCommAgentObserver::checkGenomeList()
{

	if (_wm->_agentId == gAgentIndexFocus && gVerbose) // debug
	{
		std::cout << "agent #" << gAgentIndexFocus << " is renewed" << std::endl;
		std::cout << "agent #" << gAgentIndexFocus << " imported " << _wm->_genomesList.size() << " genomes. Energy is " << _wm->getEnergyLevel() << ". Status is "  << _wm->getActiveStatus() << "." <<std::endl;
	}

	// Display the current state of the controller
	gLogFile << gWorld->getIterations() << " : " << _wm->_agentId
			 << " Energy " <<  _wm->getEnergyLevel()
			 << " DeltaE " << _wm->getDeltaEnergy()
			 << " GenomeListSize " << _wm->_genomesList.size() <<std::endl;
			
	// note: at this point, agent got energy, wether because it was revived or because of remaining energy.
	if (_wm->_genomesList.size() > 0)
	{
		// case: 1+ genome(s) imported, random pick.
		
		_wm->setDateOfBirth(gWorld->getIterations());
		//randomElitismGenomeSelection();
		//tournamentGenomeSelection();
		pickRandomGenome();
		_wm->setWaitForGenome(false);
		_wm->setActiveStatus(true);

		//log the genome
		
		if ( _wm->getActiveStatus() == true )
		{
			gLogFile << gWorld->getIterations() <<" : "<< _wm->_agentId << " use ";				for(unsigned int i=0; i<_wm->_currentGenome.size(); i++)
			{
				gLogFile << std::fixed << std::showpoint << _wm->_currentGenome[i] << " ";
			}
			gLogFile << std::endl;
		}
	}
	else
	{
		// case: no imported genome - wait for new genome.
		
		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " wait " << std::endl;

		_wm->resetActiveGenome(); // optional -- could be set to zeroes.
		_wm->setWaitForGenome(true); // inactive robot *must* import a genome from others (ie. no restart).

		_wm->setActiveStatus(false);//The robot is waiting for genome but not active yet
	}
	
	//Re-initialize the main parameters
	_wm->setDeltaEnergy(0.0); 

}



void MedeaCommAgentObserver::pickRandomGenome()
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
		if ( MedeaCommSharedData::gDynamicSigma == true )
		{
			mutateWithBouncingBounds(_wm->_sigmaList[(*it).first]);
		}
		else
		{
			mutateWithBouncingBounds(-1.00);
		}
		
		_wm->setNewGenomeStatus(true); 
		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " t " << (*it).first << " s " << _wm->_currentSigma << std::endl;
		
		if (_wm->_agentId == 1 && gVerbose) // debug
			std::cout << "  Sigma is " << _wm->_sigmaList[(*it).first] << "." << std::endl;
		

		_wm->_sigmaList.clear();		
		_wm->_genomesList.clear();
	}
	//never reached
}

void MedeaCommAgentObserver::randomElitismGenomeSelection()
{
	if(_wm->_genomesList.size() != 0)
	{
		std::map<int, double> genotypicRelatedness;
		//compute the genotypic relatedness with the current genome for each genome in the list
		for (std::map<int, std::vector<double> >::iterator it = _wm->_genomesList.begin() ; it != _wm->_genomesList.end() ; it++)
		{
			double distance=0.0;
			for(unsigned int i=0;i < it->second.size() ; i++)
			{
				distance += pow(_wm->_currentGenome[i]-it->second[i],2);
			}
			distance = sqrt(distance) ;
			if (genotypicRelatedness.size() < unsigned(nbMaxGenomeSelection) )
			{
				genotypicRelatedness[it->first] = distance;
			}
			else
			{
				double highest = distance;
				int idHighest = it->first;
				//search if there is one genome with a highest genotypic distance
				for (std::map<int,double>::iterator itSearchHighest = genotypicRelatedness.begin() ; itSearchHighest != genotypicRelatedness.end() ; itSearchHighest++)
				{
					if (itSearchHighest->second > highest)
					{
						highest = itSearchHighest->second;
						idHighest = itSearchHighest->first;
					}
				}
				if (idHighest != it->first )
				{
					genotypicRelatedness.erase(idHighest);
					genotypicRelatedness[it->first] = distance;
				}
			}
		}

		//random selection
		int randomIndex = rand()%genotypicRelatedness.size();
		std::map<int, double>::iterator itRandom = genotypicRelatedness.begin();
		while (randomIndex !=0 )
		{
			itRandom ++;
			randomIndex --;
		}

		_wm->_currentGenome = _wm->_genomesList[itRandom->first];
		if ( MedeaCommSharedData::gDynamicSigma == true )
		{
			mutateWithBouncingBounds(_wm->_sigmaList[itRandom->first]);
		}
		else
		{
			mutateWithBouncingBounds(-1.00);
		}
		
		_wm->setNewGenomeStatus(true); 
		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " t " << itRandom->first << " s " << _wm->_currentSigma << std::endl;
		
		if (_wm->_agentId == 1 && gVerbose) // debug
			std::cout << "  Sigma is " << _wm->_sigmaList[itRandom->first] << "." << std::endl;
		
		
		_wm->_genomesList.clear();
		_wm->_sigmaList.clear();
	}
}

void MedeaCommAgentObserver::tournamentGenomeSelection()
{
	if(_wm->_genomesList.size() != 0)
	{
		std::map<int, std::vector<double> > genomesSample;

		//random selection
		int genomesListSize = _wm->_genomesList.size();
		for (int i = 0 ; (i< nbMaxGenomeSelection) && (i < genomesListSize) ; i++)
		{
			int randomIndex = rand()%_wm->_genomesList.size();
			std::map<int, std::vector<double> >::iterator itRandom = _wm->_genomesList.begin();
			while (randomIndex !=0 )
			{
				itRandom ++;
				randomIndex --;
			}
			genomesSample[itRandom->first] = itRandom->second;
			_wm->_genomesList.erase(itRandom);
		}

		//find the closest genome in the genome sample
		double lowest = 0.0;
		std::map<int, std::vector<double> >::iterator it = genomesSample.begin(); 
		for(unsigned int i=0;i < it->second.size() ; i++)
		{
			lowest += pow(_wm->_currentGenome[i]-it->second[i],2);
		}
		lowest = sqrt(lowest);
		int idLowest = it->first;
		it++;
		for ( ; it != genomesSample.end() ; it++)
		{
			double distance=0.0;
			for(unsigned int i=0;i < it->second.size() ; i++)
			{
				distance += pow(_wm->_currentGenome[i]-it->second[i],2);
			}
			distance = sqrt(distance);
			if ( distance < lowest)
			{
				lowest = distance;
				idLowest = it->first;
			}
		}

		_wm->_currentGenome = genomesSample[idLowest];
		if ( MedeaCommSharedData::gDynamicSigma == true )
		{
			mutateWithBouncingBounds(_wm->_sigmaList[idLowest]);
		}
		else
		{
			mutateWithBouncingBounds(-1.00);
		}
		_wm->setNewGenomeStatus(true); 
		_wm->_genomesList.clear();
		_wm->_sigmaList.clear();

		gLogFile << gWorld->getIterations() << " : " << _wm->_agentId << " t " << idLowest << " s " << _wm->_currentSigma << std::endl;
		if (_wm->_agentId == 1 && gVerbose) // debug
				std::cout << "  Sigma is " << _wm->_sigmaList[idLowest] << "." << std::endl;

	}
}



void MedeaCommAgentObserver::writeGenome(std::vector<double> genome, int senderId, float sigma)
{
		_wm->_genomesList[senderId] = genome;
		if ( MedeaCommSharedData::gDynamicSigma == true)
		{
			_wm->_sigmaList[senderId] = sigma;
		}

// 		gLogFile <<gWorld->getIterations()<< "agent #"  << _wm->_agentId << " size " << _wm->_genomesList.size() << "get:"<<senderId<<std::endl;

}


void MedeaCommAgentObserver::mutateWithBouncingBounds( float sigma)
{
	if ( MedeaCommSharedData::gDynamicSigma == true)
	{
		_wm->_currentSigma = sigma;
	}
	else
	{
		_wm->_currentSigma = MedeaCommSharedData::gSigmaRef;
	}
	
	for (unsigned int i = 0 ; i != _wm->_currentGenome.size() ; i++ )
	{
		double value = _wm->_currentGenome[i] + getGaussianRand(0,_wm->_currentSigma);
		// bouncing upper/lower bounds if those bounds are set to a value different than 0.0
		if ( ( _wm->_minValue != 0.0 ) && ( _wm->_maxValue != 0.0 ) )
		{
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
		}
		
		_wm->_currentGenome[i] = value;
	}
}

double MedeaCommAgentObserver::getCommunication()
{
	return _wm->getCommunication();
}
