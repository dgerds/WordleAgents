
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

    // define the command line arguments
    struct Args
    {
        Args(int num_picks)
            : num_picks(num_picks) {}

        int num_picks;
    };    

    void PrintUsage()
    {   
        std::cout << " =====================" << std::endl;
        std::cout << " | Pick Wordle Words |" << std::endl;
        std::cout << " =====================" << std::endl;
        std::cout << std::endl;
        std::cout << " Usage:    PickWords.exe num_picks" << std::endl;
        std::cout << std::endl;
        std::cout << " Example:  PickWords.exe 3" << std::endl;
        std::cout << std::endl;
    }

    std::unique_ptr<Args> ParseArgs(int argc, char** argv)
    {
        std::vector<std::string> arg_vec(argv + 1, argv + argc);
        if (arg_vec.size() != 1)
        {
            throw std::runtime_error("Incorrect number of command line arguments");
        }
        return std::make_unique<Args>(std::stoi(arg_vec[0]));
    }
}


int main(int argc, char** argv)
{
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
        for (const auto& item : csv_reader.GetContent())
        {
            word_list.push_back(Game::ToUpperCopy(item));
        }
    }
    catch (std::exception e)
    {
        std::cout << "### ERROR ### " << e.what() << std::endl;
        return -1;
    }
    
    // pick the unique random words
    std::set<std::string> picks;
    while (picks.size() < args->num_picks)
    {
        // pick a word at random
        const auto& pick = word_list[Random::GetRandomInt(0, static_cast<int>(word_list.size() - 1))];

        // if this word hasn't been selected yet then
        if (picks.find(pick) == picks.end())
        {
            picks.insert(pick);
        }
    }

    // print out the words
    for (const auto& pick : picks)
    {
        std::cout << pick << " ";
    }
    std::cout << std::endl;
}

