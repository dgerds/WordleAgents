
#include "framework.h"
#include "WordleAgent/Agent.h"
#include "WordleAgent/AgentFactory.h"
#include "WordleAgent/AgentFactoryDll.h"
#include "WordleAgent/Game.h"
#include "WordleAgent/Random.h"
#include "WordleAgent/OutputHelper.h"
#include <iostream>
#include <stdexcept>

namespace
{
    void PrintGuessResultAndLetters(const GuessResult& gr, const GameLetters& gl)
    {
        std::cout << " ";
        OutputHelper::Print(gr);
        std::cout << " - ";
        OutputHelper::Print(gl);
        std::cout << std::endl;
    }
}


int main()
{
    std::unique_ptr<AgentFactory> agent_factory;
    try
    {
        agent_factory = AgentFactoryDll::LoadPlugin("..\\x64\\Debug\\RandomAgent.dll");
        //agent_factory = AgentFactoryDll::LoadPlugin("..\\x64\\Release\\RandomAgent.dll");
    }
    catch (std::exception e)
    {
        std::cout << "### ERROR ### " << e.what() << std::endl;
        return -1;
    }

    WordList word_list;
    word_list.push_back("SKILL");
    word_list.push_back("DRILL");
    word_list.push_back("PUPIL");
    word_list.push_back("PILOT");
    word_list.push_back("IRATE");
    word_list.push_back("APPLE");
    word_list.push_back("PEACE");
    word_list.push_back("DREAM");
    word_list.push_back("DEBUG");
    word_list.push_back("AGENT");

    Game game("PILOT", 6, 300.0, 30.0, word_list);

    auto agent = agent_factory->CreateAgent(game);

    std::cout << "=======" << std::endl;

    while (!game.IsGameOver())
    {
        try
        {
            game.ProcessGuess(agent->GetNextGuess());
        }
        catch (std::exception e)
        {
            std::cout << "### ERROR ### " << e.what() << std::endl;
            return -1;
        }
        PrintGuessResultAndLetters(game.GetGameTable().back(), game.GetGameLetters());
    }

    std::cout << "=======" << std::endl;
    std::cout << std::endl;

    std::cout << "Game result: " << game.GetGameOverMessage() << std::endl;
    std::cout << "Game time: " << game.GetGameTime() << std::endl;
}

