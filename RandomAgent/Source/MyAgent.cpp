
#include "MyAgent.h"
#include "WordleAgent/Random.h"
#include <iostream>


// constructor.
MyAgent::MyAgent(Game& game)
    : Agent(game)
{
    // do any preprocessing here
}


// return the agent's next guess at the solution.
// note that this method must return within the games "agent guess timelimit" to avoid disqualification.
std::string MyAgent::GetNextGuess()
{
    // get the word list
    auto& word_list = GetGame().GetWordList();

    // return a random item from the word list
    return word_list[Random::GetRandomInt(0, static_cast<int>(word_list.size()-1))];
}

