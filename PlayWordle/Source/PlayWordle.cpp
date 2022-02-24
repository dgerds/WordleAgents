
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
    // define the command line arguments
    struct Args
    {
        Args(int num_games,
            std::string plugin_filename)
          : num_games(num_games),
            plugin_filename(plugin_filename) {}

        int num_games;
        std::string plugin_filename;
    };

    void PrintGuessResultAndLetters(const GuessResult& gr, const GameLetters& gl)
    {
        std::cout << " | ";
        OutputHelper::Print(gr);
        std::cout << " | ";
        OutputHelper::Print(gl);
        std::cout << std::endl;
    }

    void PrintHeader()
    {
        std::cout << " =====================" << std::endl;
        std::cout << " | Wordle Agent Game |" << std::endl;
        std::cout << " =====================" << std::endl;
        std::cout << std::endl;
    }

    void PrintUsage()
    {        
        std::cout << std::endl;
        std::cout << " Usage:    PlayWordle.exe num_games plugin_filename" << std::endl;
        std::cout << std::endl;
        std::cout << " Example:  PlayWordle.exe 5 MyGame.dll" << std::endl;
        std::cout << std::endl;
    }

    std::unique_ptr<Args> ParseArgs(int argc, char** argv)
    {
        if (argc != 3)
        {
            throw std::runtime_error("Incorrect number of command line arguments");
        }
        return std::make_unique<Args>(std::stoi(argv[1]), argv[2]);
    }
}


int main(int argc, char** argv)
{
    PrintHeader();

    // parse the command line args
    std::unique_ptr<Args> args;
    try
    {
        args = ParseArgs(argc, argv);
    }
    catch (std::exception e)
    {
        std::cout << "### ERROR ### " << e.what() << std::endl;
        PrintUsage();
        return -1;
    }

    // load the player's custom agent factory
    std::unique_ptr<AgentFactory> agent_factory;
    try
    {
        agent_factory = AgentFactoryDll::LoadPlugin(args->plugin_filename);
    }
    catch (std::exception e)
    {
        std::cout << "### ERROR ### " << e.what() << std::endl;
        return -2;
    }
    std::cout << "Loaded player agent: " << args->plugin_filename << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << std::endl;

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

    std::vector<Game> game_list;
    for (int g = 0; g < args->num_games; g++)
    {
        // create a new game
        Game game = Game("PILOT", 6, 300.0, 30.0, word_list);

        // create a new player agent instance
        auto agent = agent_factory->CreateAgent(game);

        // print the game header
        std::cout << "Game #" << (g + 1) << std::endl;
        std::cout << std::endl;
        std::cout << " =========" << std::endl;

        // play the game until it's over
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

        // print the game footer stats
        std::cout << " =========" << std::endl;
        std::cout << std::endl;
        std::cout << "Game result: " << game.GetGameOverMessage() << std::endl;
        std::cout << "Game time: " << game.GetGameTimeMs() << " ms" << std::endl;
        std::cout << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << std::endl;

        // add this game to the completed list
        game_list.push_back(game);
    }

    // calculate the states
    int overall_count = 0;
    double overall_ms = 0.0;
    for (size_t i = 0; i < game_list.size(); i++)
    {
        if (game_list[i].IsGameSolved())
        {
            overall_count++;
        }
        overall_ms += game_list[i].GetGameTimeMs();
    }

    // print the overall stats
    std::cout << "Overall solved: " << overall_count << " of " << game_list.size() << std::endl;
    std::cout << "Overall time:   " << overall_ms << " ms" << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << std::endl;
}

