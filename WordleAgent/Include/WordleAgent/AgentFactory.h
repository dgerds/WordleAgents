#pragma once
#include "WordleAgent/framework.h"
#include "WordleAgent/Agent.h"


// abstract factory to create wordle agents
class AgentFactory
{
public:

    // destructor
    virtual ~AgentFactory() {}
    
    // create an agent instance.
    virtual std::unique_ptr<Agent> CreateAgent(Game &game) const = 0;

};
