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
    virtual std::string GetNextGuess();

private:

    WordSet m_word_set;
};
