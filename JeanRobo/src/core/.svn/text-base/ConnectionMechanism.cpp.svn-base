#include "Agents/ConnectionMechanism.h"

ConnectionMechanism::ConnectionMechanism(RobotAgentConnectable* agent)
{
	_agent = agent;
	agent->customizeConnectionMechanism(this);
}

ConnectionMechanism::~ConnectionMechanism()
{
	delete _agent;	
}
