
#include "framework.h"
#include "WordleAgent/Agent.h"
#include "WordleAgent/AgentFactory.h"
#include "WordleAgent/AgentFactoryDll.h"
#include "WordleAgent/Game.h"
#include "WordleAgent/Random.h"
#include "WordleAgent/OutputHelper.h"
#include "WordleAgent/CsvReader.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace
{
    // word length
    // this is the only place the word length is defined, so can be easily changed to configuration if required
    const int GAME_WORD_LENGTH = 5;

    // max number of guesses allowed
    // this is the only place the word length is defined, so can be easily changed to configuration if required
    const int MAX_NUM_GUESSES = 6;

    // define the command line arguments
    struct Args
    {
        Args(std::string plugin_filename,
             int num_games,
             std::vector<std::string> word_list)
            : num_games(num_games),
              plugin_filename(plugin_filename),
              solution_list(word_list)
        {
            // ensure the solutions are in uppercase
            for (auto& str : solution_list)
            {
                Game::ToUpper(str);
            }
        }

        int num_games;
        std::string plugin_filename;
        std::vector<std::string> solution_list;
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
        std::cout << " Usage:    PlayWordle.exe plugin_filename num_games [solution_1 solution_2 solution_3 ... solution_n]" << std::endl;
        std::cout << std::endl;
        std::cout << " Example:  PlayWordle.exe MyGame.dll 5" << std::endl;
        std::cout << " Example:  PlayWordle.exe MyGame.dll 3 PILOT APPLE SKILL" << std::endl;
        std::cout << std::endl;
    }

    std::unique_ptr<Args> ParseArgs(int argc, char** argv)
    {
        std::vector<std::string> arg_vec(argv + 1, argv + argc);
        if (arg_vec.size() < 2)
        {
            throw std::runtime_error("Incorrect number of command line arguments");
        }
        return std::make_unique<Args>(arg_vec[0], std::stoi(arg_vec[1]), std::vector<std::string>(arg_vec.begin() + 2, arg_vec.end()));
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

    // load the word list from disk
    std::vector<std::string> word_list;
    try
    {
        // read the csv file
        CsvReader csv_reader("wordlist5.csv");
        // for each item, ensure its the right length and uppercase, then add it to the word list
        for (const auto& item : csv_reader.GetContent())
        {
            if (item.length() == GAME_WORD_LENGTH)
            {
                word_list.push_back(Game::ToUpperCopy(item));
            }
            else
            {
                throw std::runtime_error("Item in word list is not the correct length: " + item);
            }
        }
    }
    catch (std::exception e)
    {
        std::cout << "### ERROR ### " << e.what() << std::endl;
        return -1;
    }
    std::cout << "Loaded word list: " << word_list.size() << std::endl;
    
    // sanity check any solutions provided on the command line are contained in the word list
    for (const auto& item : args->solution_list)
    {
        if (std::find(word_list.begin(), word_list.end(), item) == word_list.end())
        {
            std::cout << "### ERROR ### Solution provided on the command line is not in the word list: " << item << std::endl;
            return -1;
        }
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

    Timer timer;
    std::vector<Game> game_list;
    for (int g = 0; g < args->num_games; g++)
    {
        // pick the solution for the next game
        std::string game_solution;
        if (g < args->solution_list.size())
        {
            // from the command line arg list
            game_solution = args->solution_list[g];
        }
        else
        {
            // pick a word at random from the word_list
            game_solution = word_list[Random::GetRandomInt(0, static_cast<int>(word_list.size() - 1))];
        }

        // create a new game
        Game game = Game(game_solution, MAX_NUM_GUESSES, word_list);

        // create a new player agent instance
        auto start_time = timer.GetCurrentTimeMs();
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
                // ask the agent to provide the next guess
                game.ProcessGuess(agent->GetNextGuess());
            }
            catch (std::exception e)
            {
                std::cout << "### ERROR ### " << e.what() << std::endl;
                return -5;
            }
            PrintGuessResultAndLetters(game.GetGameTable().back(), game.GetGameLetters());
        }

        // print the game footer stats
        std::cout << " =========" << std::endl;
        std::cout << std::endl;
        if (game.IsGameSolved())
        {
            std::cout << "Solved with " << game.GetNumGuessesUsed() << " guesses in " << game.GetGameTimeMs() << " ms" << std::endl;
        }
        else
        {
            std::cout << "Not solved after " << game.GetNumGuessesUsed() << " guesses and " << game.GetGameTimeMs() << " ms [" << game_solution << "]" << std::endl;
        }
        std::cout << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << std::endl;

        // add this game to the completed list
        game_list.push_back(game);
    }

    // calculate the states
    int overall_count = 0;
    int overall_guesses = 0;
    double overall_ms = 0.0;
    for (const auto& game : game_list)
    {
        if (game.IsGameSolved())
        {
            overall_count++;
            overall_guesses += game.GetNumGuessesUsed();
            overall_ms += game.GetGameTimeMs();
        }
    }

    // print the overall stats
    std::cout << "Overall games solved:             " << overall_count << " of " << game_list.size() << std::endl;
    std::cout << "Overall guesses for solved games: " << overall_guesses << std::endl;
    std::cout << "Overall time for solved games:    " << overall_ms << " ms" << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Summary: " << overall_count << "/" << game_list.size() << "|" << overall_guesses << "|" << overall_ms << " ms" << std::endl;
}

