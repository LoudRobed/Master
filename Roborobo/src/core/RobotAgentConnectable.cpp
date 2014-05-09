/*
 *  RobotAgentConnectable.cpp
 *  roborobo
 *
 *  Created by Jean-Marc on 22/03/13.
 *
 */

#include <cmath>
#include <cstring>

#include "Config/GlobalConfigurationLoader.h"

#include "Agents/RobotAgentConnectable.h"
#include "SDL_collide.h"
#ifdef MACOSX
#include "SDL_ttf/SDL_ttf.h"
#else
#include "SDL/SDL_ttf.h"
#endif

#include "Organism.h"

RobotAgentConnectable::RobotAgentConnectable(World *__world) :
RobotAgent( __world)
{
	_organism = NULL;
	_customConnectionMechanism = NULL;
	_connectionMechanismCustomized = false;
	connected = new std::vector<RobotAgentConnectable*>();
}

RobotAgentConnectable::~RobotAgentConnectable()
{
	delete connected;
	delete _wm;
	delete _customConnectionMechanism;
}

void RobotAgentConnectable::setConnectToOthers(int __connectToOthers) {
	_connectToOthers = __connectToOthers;
}

int RobotAgentConnectable::getConnectToOthers() {
	return _connectToOthers;
}

/**
 * This function is used to set a connection mechanism that one provided by default
 */
void RobotAgentConnectable::customizeConnectionMechanism(ConnectionMechanism* customConnectionMechanism)
{
	_customConnectionMechanism = customConnectionMechanism;
	_connectionMechanismCustomized = true;
}

/**
 * This function returns a pointer to the connection mechanism currently used
 * If no custom connection mechanism has been specified, a NULL pointer is returned
 */
ConnectionMechanism* RobotAgentConnectable::getConnectionMechanism()
{
 	if (_connectionMechanismCustomized == true)
	{
		return _customConnectionMechanism;
	}
	else
	{
		return NULL;
	}
}


/**
 * This function sets up connections between robots who are close enough to
 * each other and have their connection ring set to 1.
 */
void RobotAgentConnectable::setUpConnections() {
	if (_connectionMechanismCustomized == true)
	{
		_customConnectionMechanism->setUpConnections();
	}
	else
	{
		int nAgents = _wm->_world->getNbOfAgent();
		int id = _wm->_agentId;

		if (this->isPartOfOrganism()) {
			if (this->getConnectToOthers() == RobotAgentConnectable::NEGATIVE) {
				this->letGoOfOrganism();
			}
			if (this->connected->empty()) {
				this->letGoOfOrganism();
			}
		}
		for (int i = 0; i < nAgents; i++) {
			RobotAgentConnectable* other = dynamic_cast<RobotAgentConnectable*>(_wm->_world->getAgent(i));
			if(other == 0)
			{
				std::cerr << "Agent" << i << "isn't of type RobotAgentConnectable" << std::endl;
				std::cerr << "Every  agents in the simulation should be of type RobotAgentConnectable" << std::endl;
				exit(1);
			}
			RobotAgentWorldModel *otherWM = (RobotAgentWorldModel*) other->getWorldModel();
			int otherId = otherWM->_agentId;

			if (otherId != id) {
				// If they're out of bounds, ignore.
				// This happens at the start of the simulation sometimes and can lead
				// to false positives
				if (this->isOutOfBounds() || other->isOutOfBounds()) {
					return;
				}

				double x1, y1, x2, y2;
				x1 = this->_wm->_xReal;
				y1 = this->_wm->_yReal;
				x2 = other->_wm->_xReal;
				y2 = other->_wm->_yReal;

				// Are they within range?
				if (SDL_CollideBoundingCircle(this->getAgentMask(), x1, y1, other->getAgentMask(), x2, y2, gConnectionGap)) {
					// connect to other robot
					if ((this->getConnectToOthers() == RobotAgentConnectable::POSITIVE) && (other->getConnectToOthers() == RobotAgentConnectable::POSITIVE)) {
						this->connectToRobot(other);
					}
				}
			}
		}
	}
}

void RobotAgentConnectable::connectToRobot(RobotAgentConnectable* other) {

	if (this->isPartOfOrganism() && other->isPartOfOrganism()
		&& this->getOrganism()->getId() == other->getOrganism()->getId()) {
		// the same organism, do nothing.
	} else if (other->isPartOfOrganism() && this->isPartOfOrganism()
		&& other->getOrganism()->getId() != this->getOrganism()->getId()) {
		// two different organisms
		Organism* o1 = this->getOrganism();
		Organism* o2 = other->getOrganism();

		this->addNeighbour(other);
		RobotAgentConnectable* toAdd = dynamic_cast<RobotAgentConnectable*>(gWorld->getAgent(this->_wm->_agentId)); 
		if(toAdd == 0)
		{
			std::cerr << "Agent" << this->_wm->_agentId << "isn't of type RobotAgentConnectable" << std::endl;
			std::cerr << "Every  agents in the simulation should be of type RobotAgentConnectable" << std::endl;
			exit(1);
		}
		other->addNeighbour(toAdd);

		// merge smaller into larger
		if (o1->size() >= o2->size()) {
			//gLogFile << "Merging organism " << o2->getId() << " into " << o1->getId() << std::endl;

			//other->clickOnto(this, o2);

			o2->mergeInto(o1);
			o2->setInactive();
			//Organism::remove(o2);
			//delete o2;
		} else {
			//gLogFile << "Merging organism " << o1->getId() << " into " << o2->getId() << std::endl;

			//this->clickOnto(other, o1);

			o1->mergeInto(o2);
			o1->setInactive();
			
			//Organism::remove(o1);
			//delete o1;
		}
	} else if (other->isPartOfOrganism()) {
		Organism* organism = other->getOrganism();
		RobotAgentConnectable* toAdd = dynamic_cast<RobotAgentConnectable*>(gWorld->getAgent(this->_wm->_agentId)); 
		if(toAdd == 0)
		{
			std::cerr << "Agent" << this->_wm->_agentId << "isn't of type RobotAgentConnectable" << std::endl;
			std::cerr << "Every  agents in the simulation should be of type RobotAgentConnectable" << std::endl;
			exit(1);
		}
		organism->addRobot(toAdd);
		this->setOrganism(organism);

		this->addNeighbour(other);
		other->addNeighbour(toAdd);

		//this->clickOnto(other);
		//gLogFile << "Adding agent " << this->_wm->_agentId << " to organism: " << organism->getId() << std::endl;
	} else if (this->isPartOfOrganism()) {
		Organism* organism = this->getOrganism();
		organism->addRobot(other);
		other->setOrganism(organism);

		this->addNeighbour(other);
		RobotAgentConnectable* toAdd = dynamic_cast<RobotAgentConnectable*>(gWorld->getAgent(this->_wm->_agentId)); 
		if(toAdd == 0)
		{
			std::cerr << "Agent" << this->_wm->_agentId << "isn't of type RobotAgentConnectable" << std::endl;
			std::cerr << "Every  agents in the simulation should be of type RobotAgentConnectable" << std::endl;
			exit(1);
		}
		other->addNeighbour(toAdd);

		//other->clickOnto(this);
		//gLogFile << "Adding agent " << other->_wm->_agentId << " to organism: " << organism->getId() << std::endl;
	} else {
		Organism* organism = new Organism();
		//gLogFile << "Creating new organism: " << organism->getId() << " robots: " << this->_wm->_agentId << ", " << other->_wm->_agentId << std::endl;
		RobotAgentConnectable* toAdd = dynamic_cast<RobotAgentConnectable*>(gWorld->getAgent(this->_wm->_agentId)); 
		if(toAdd == 0)
		{
			std::cerr << "Agent" << this->_wm->_agentId << "isn't of type RobotAgentConnectable" << std::endl;
			std::cerr << "Every  agents in the simulation should be of type RobotAgentConnectable" << std::endl;
			exit(1);
		}
		organism->addRobot(toAdd);
		organism->addRobot(other);

		this->setOrganism(organism);
		other->setOrganism(organism);

		this->addNeighbour(other);
		other->addNeighbour(toAdd);

		Organism::add(organism);

		//this->clickTogether(other);
	}
}

void RobotAgentConnectable::addNeighbour(RobotAgentConnectable* neighbour) {
	this->connected->push_back(neighbour);
}

void RobotAgentConnectable::removeNeighbour(RobotAgentConnectable* neighbour) {
	std::vector<RobotAgentConnectable*>::iterator it;
	for (it = this->connected->begin(); it != this->connected->end(); it++) {
		if ((*it)->_wm->_agentId == neighbour->_wm->_agentId) {
			this->connected->erase(it);
			return;
		}
	}
}

std::vector<RobotAgentConnectable*> *RobotAgentConnectable::getConnected() {
	return this->connected;
}

bool RobotAgentConnectable::isOutOfBounds() {
	//If the dot went too far to the left or right
	if ((this->_x < 0) || (this->_x + gAgentWidth > gAreaWidth)) {
		return true;
	}
	//If the dot went too far up or down
	if ((this->_y < 0) || (this->_y + gAgentHeight > gAreaHeight)) {
		return true;
	}
	return false;
}

void RobotAgentConnectable::letGoOfOrganism() {
	if (!gUseOrganisms) return;

	if (this->isPartOfOrganism()) {
		//gLogFile << "Agent: " << this->_wm->_agentId << " letting go of organism: " << this->getOrganism()->getId() << std::endl;
		RobotAgentConnectable* toRemove = dynamic_cast<RobotAgentConnectable*>(gWorld->getAgent(this->_wm->_agentId)); 
		if(toRemove == 0)
		{
			std::cerr << "Agent" << this->_wm->_agentId << "isn't of type RobotAgentConnectable" << std::endl;
			std::cerr << "Every  agents in the simulation should be of type RobotAgentConnectable" << std::endl;
			exit(1);
		}
		this->getOrganism()->removeRobot(toRemove);

		std::vector<RobotAgentConnectable*>::iterator it;
		for (it = this->connected->begin(); it != this->connected->end(); it++) {
			(*it)->removeNeighbour(toRemove);
		}
		this->connected->clear();
	}
}

void RobotAgentConnectable::setOrganism(Organism* __organism) {
	if (!gUseOrganisms) return;

	_organism = __organism;
}

Organism* RobotAgentConnectable::getOrganism() {
	return _organism;
}

bool RobotAgentConnectable::isPartOfOrganism() {
	return _organism != NULL;
}

/**
 * Check whether the other robot is in the same organism
 * @param other
 * @return
 */
bool RobotAgentConnectable::isPartOfSameOrganism(RobotAgentConnectable* other) {
	std::vector<RobotAgentConnectable*>::iterator it;
	if (this->isPartOfOrganism()) {
		for (it = this->_organism->agents.begin(); it != this->_organism->agents.end(); it++) {
			if ((*it)->_wm->_agentId == other->_wm->_agentId) {
				return true;
			}
		}
	}
	return false;
}
