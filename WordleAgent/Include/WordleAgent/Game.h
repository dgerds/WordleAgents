#pragma once
#include "WordleAgent/framework.h"
#include "WordleAgent/Timer.h"


enum class Colour
{
    GREEN = 0, // the solution includes this letter in this location
    YELLOW,    // the solution includes this letter in a different location
    BLACK,     // the solution does not contain this letter
    GREY,      // this letter has not been selected in one of your guesses yet
    NONE       // not a valid colour
};


struct GuessResult
{
    // constructor
    GuessResult(const std::string& guess, const std::string& solution);

    std::string guess;
    std::vector<Colour> result;
};


typedef std::vector<GuessResult> GameTable;


typedef std::map<char, Colour> GameLetters;


typedef std::vector<std::string> WordList;


class Game
{
public:
    // constructor
    Game(const std::string& solution,
         int num_guesses,
         double agent_initialisation_timelimit_ms,
         double agent_guess_timelimit_ms,
         const WordList& word_list);

    bool IsGameStated() const
    {
        return m_game_start_time_ms > 0.0;
    }

    bool IsGameSolved() const
    {
        return m_game_solved;
    }

    bool IsGameOver() const
    {
        return m_game_end_time_ms > 0.0;
    }    

    const std::string& GetGameOverMessage() const
    {
        return m_game_over_message;
    }    

    double GetAgentInitialisationTimelimitMs() const
    {
        return m_agent_initialisation_timelimit_ms;
    }

    double GetAgentGuessTimelimitMs() const
    {
        return m_agent_guess_timelimit_ms;
    }

    // get the game time in milliseconds
    double GetGameTimeMs() const;

    int GetNumGuesses() const
    {
        return m_num_guesses;
    }

    int GetNumGuessesUsed() const
    {
        return static_cast<int>(m_game_table.size());
    }

    std::string GetSolution() const;

    const WordList& GetWordList() const
    {
        return m_word_list;
    }

    const GameTable& GetGameTable() const
    {
        return m_game_table;
    }

    const GameLetters& GetGameLetters() const
    {
        return m_game_letters;
    }

    // progress an agents guess.
    // returns true if the guess is correct, otherwise false
    bool ProcessGuess(std::string guess);

    // end the game.
    // stops the game time at the current time and sets the game over message.
    // required to be public to handle corner cases like disqualification for taking too long.
    void EndGame(const std::string& game_over_message);

private:

    bool m_game_solved;
    std::string m_game_over_message;
    std::string m_solution;
    int m_num_guesses;
    double m_agent_initialisation_timelimit_ms;
    double m_agent_guess_timelimit_ms;
    double m_game_start_time_ms;
    double m_game_end_time_ms;
    const WordList& m_word_list;
    GameTable m_game_table;
    GameLetters m_game_letters;
    Timer m_timer;
};
