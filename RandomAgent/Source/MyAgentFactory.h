#pragma once
#include "WordleAgent/AgentFactory.h"
#include "MyAgent.h"


// factory to create my custom agent
class MyAgentFactory
{
public:

    // create my custom agent instance.
    // note that this method must return within the games "agent initialisation timelimit" to void disqualification.
    virtual std::unique_ptr<Agent> CreateAgent(Game& game) const
    {
        return std::make_unique<MyAgent>(game);
    }
};
