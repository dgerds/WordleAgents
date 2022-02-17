#pragma once
#include "WordleAgent/framework.h"


enum class Colour
{
    GREEN = 0,  // the solution includes this letter in this location
    YELLOW,     // the solution includes this letter in a different location
    BLACK,      // the solution does not contain this letter
    GREY        // this letter has not been selected in one of your guesses yet
};


struct GuessResult
{
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
         double agent_initialisation_timelimit, 
         double agent_guess_timelimit,
         const WordList& word_list)
    : m_game_started(false),      
      m_game_solved(false),
      m_game_over_message(),
      m_solution(solution),
      m_num_guesses(num_guesses),
      m_agent_initialisation_timelimit(agent_initialisation_timelimit),
      m_agent_guess_timelimit(agent_guess_timelimit),
      m_game_time(0.0),
      m_word_list(word_list) {}

    bool IsGameStated() const
    {
        return m_game_started;
    }

    bool IsGameSolved() const
    {
        return m_game_solved;
    }

    bool IsGameOver() const
    {
        return !m_game_over_message.empty();
    }    

    const std::string& GetGameOverMessage() const
    {
        return m_game_over_message;
    }    

    double GetAgentInitialisationTimelimit() const
    {
        return m_agent_initialisation_timelimit;
    }

    double GetAgentGuessTimelimit() const
    {
        return m_agent_guess_timelimit;
    }

    double GetGameTime() const;

    int GetNumGuesses() const
    {
        return m_num_guesses;
    }

    int GetNumGuessesUsed() const
    {
        return static_cast<int>(m_game_table.size());
    }

    std::string GetSolution() const;

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
    bool ProcessGuess(const std::string& guess);

    // end the game.
    // stops the game time at the current time and sets the game over message.
    // required to be public to handle corner cases like disqualification for taking too long.
    void EndGame(const std::string& game_over_message);

private:

    bool m_game_started;
    bool m_game_solved;
    std::string m_game_over_message;
    std::string m_solution;
    int m_num_guesses;
    double m_agent_initialisation_timelimit;
    double m_agent_guess_timelimit;
    double m_game_time;
    const WordList& m_word_list;
    GameTable m_game_table;
    GameLetters m_game_letters;
};
