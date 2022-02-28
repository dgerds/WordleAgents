#pragma once
#include "WordleAgent/framework.h"
#include "WordleAgent/Game.h"


// wordle player agent abstract base-class
class Agent
{
public:
    
    // constructor.
    Agent(Game &game)
      : m_game(game) {}

    // get a const reference to the current game.
    const Game& GetGame() const
    {
        return m_game;
    }

    // get the name of the agent.
    // eg: "Einstein"
    virtual std::string GetName() const = 0;

    // return the agent's next guess at the solution.
    virtual std::string GetNextGuess() = 0;

private:

    const Game& m_game;
};
