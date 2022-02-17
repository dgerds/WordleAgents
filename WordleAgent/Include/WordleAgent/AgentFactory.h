#pragma once
#include "WordleAgent/framework.h"
#include "WordleAgent/Agent.h"


// abstract factory to create wordle agents
class AgentFactory
{
public:
    
    // create an agent instance.
    // note that this method must return within the games "agent initialisation timelimit" to void disqualification.
    virtual std::unique_ptr<Agent> CreateAgent(Game &game) const = 0;

};
