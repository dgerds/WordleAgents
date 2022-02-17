
#include "MyAgent.h"


// constructor.
MyAgent::MyAgent(Game& game)
    : Agent(game)
{

}


// return the agent's next guess at the solution.
// note that this method must return within the games "agent guess timelimit" to avoid disqualification.
std::string MyAgent::GetNextGuess()
{
    return "wordle";
}

