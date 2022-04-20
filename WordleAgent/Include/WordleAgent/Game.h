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


typedef std::map<char, Colour> GameLetters;


struct GuessResult
{
    // constructor
    GuessResult(const std::string& guess, const std::string& solution, const GameLetters& game_letters);

    std::string guess;
    std::vector<Colour> result;
    GameLetters letters;
};


typedef std::vector<GuessResult> GameTable;


typedef std::vector<std::string> WordList;


typedef std::set<std::string> WordSet;


class Game
{
public:
    // constructor
    Game(const std::string& solution,
         int num_guesses,
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

    const WordList& GetWordList() const
    {
        return m_word_list;
    }

    const WordSet& GetWordSet() const
    {
        return m_word_set;
    }

    const GameTable& GetGameTable() const
    {
        return m_game_table;
    }

    const GameLetters& GetGameLetters() const
    {
        return m_game_letters;
    }

    const GuessResult* GetLastGuessResult() const
    {
        if (!m_game_table.empty())
        {
            return &m_game_table[m_game_table.size() - 1];
        }
        return nullptr;
    }

    // progress an agents guess.
    // returns true if the guess is correct, otherwise false
    bool ProcessGuess(std::string guess);

    // transform the given string to uppercase
    static void ToUpper(std::string& str);

    // return a copy of the given string transformed to uppercase
    static std::string ToUpperCopy(const std::string& str);

private:

    // end the game.
    // stops the game time at the current time.
    void EndGame();

    bool m_game_solved;
    std::string m_solution;
    int m_num_guesses;
    double m_game_start_time_ms;
    double m_game_end_time_ms;
    const WordList& m_word_list;
    WordSet m_word_set;
    GameTable m_game_table;
    GameLetters m_game_letters;
    Timer m_timer;
};
