#pragma once
#include "framework.h"
#include "WordleAgent/Agent.h"


// custom wordle player agent implementation
class MyAgent : public Agent
{
public:

    // constructor.
    MyAgent(Game& game);


    // get the name of the agent.
    // eg: "Einstein"
    virtual std::string GetName() const
    {
        return "Mr Random";
    }

    // return the agent's next guess at the solution.
    // note that this method must return within the games "agent guess timelimit" to avoid disqualification.
    virtual std::string GetNextGuess();

};
