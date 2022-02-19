
#include "WordleAgent/Agent.h"
#include "WordleAgent/Game.h"
#include "WordleAgent/OutputHelper.h"
#include <iostream>

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

    std::cout << "=======" << std::endl;

    game.ProcessGuess("AGENT");
    PrintGuessResultAndLetters(game.GetGameTable().back(), game.GetGameLetters());

    game.ProcessGuess("DEBUG");
    PrintGuessResultAndLetters(game.GetGameTable().back(), game.GetGameLetters());

    game.ProcessGuess("DREAM");
    PrintGuessResultAndLetters(game.GetGameTable().back(), game.GetGameLetters());

    game.ProcessGuess("PUPIL");
    PrintGuessResultAndLetters(game.GetGameTable().back(), game.GetGameLetters());

    game.ProcessGuess("DRILL");
    PrintGuessResultAndLetters(game.GetGameTable().back(), game.GetGameLetters());

    game.ProcessGuess("PILOT");
    PrintGuessResultAndLetters(game.GetGameTable().back(), game.GetGameLetters());

    std::cout << "=======" << std::endl;
    std::cout << std::endl;

    std::cout << "Game result: " << game.GetGameOverMessage() << std::endl;
    std::cout << "Game time: " << game.GetGameTime() << std::endl;
}

