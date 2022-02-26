
#include "WordleAgent/Game.h"
#include <stdexcept>
#include <string>
#include <algorithm>


namespace
{
	// transform the given string to uppercase
	void ToUpper(std::string& str)
	{
		std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::toupper(c); });
	}

	// get a copy of the given string transformed to uppercase
	std::string ToUpperCopy(std::string str)
	{
		ToUpper(str);
		return str;
	}

	// update the given game letters based on the given guess result
	void UpdateGameLetters(GameLetters& game_letters, const GuessResult& gr)
	{
		for (size_t i = 0; i < gr.guess.size(); i++)
		{
			auto iter = game_letters.find(gr.guess[i]);
			if (iter != game_letters.end())
			{
				// if (the result for this letter is "better" than the current game_letters result) then
				if (gr.result[i] < iter->second)
				{
					// update the game_letters result
					iter->second = gr.result[i];
				}
			}
		}
	}
}


// constructor
GuessResult::GuessResult(const std::string& guess, const std::string& solution)
	: guess(guess)
{
	// sanity check guess and solution are the same size
	if (guess.length() != solution.length())
	{
		throw std::runtime_error("Guess length does not match solution length");
	}

	// calculate the result for each character
	result.resize(guess.size());
	for (size_t i = 0; i < guess.size(); i++)
	{
		if (guess[i] == solution[i])
		{
			result[i] = Colour::GREEN;
		}
		else if (solution.find(guess[i]) != std::string::npos)
		{
			result[i] = Colour::YELLOW;
		}
		else
		{
			result[i] = Colour::BLACK;
		}
	}
}


// constructor
Game::Game(const std::string& solution,
		   int num_guesses,
		   double agent_initialisation_timelimit_ms,
		   double agent_guess_timelimit_ms,
		   const WordList& word_list)
  : m_game_solved(false),
	m_game_over_message(),
	m_solution(ToUpperCopy(solution)),
	m_num_guesses(num_guesses),
	m_agent_initialisation_timelimit_ms(agent_initialisation_timelimit_ms),
	m_agent_guess_timelimit_ms(agent_guess_timelimit_ms),
	m_game_start_time_ms(0.0),
	m_game_end_time_ms(0.0),
	m_word_list(word_list),
	m_timer()
{
	// initialise the game letters to 'not used'
	for (char c = 'A'; c <= 'Z'; c++)
	{
		m_game_letters[c] = Colour::GREY;
	}
}


// get the game time in milliseconds
double Game::GetGameTimeMs() const
{
	if (IsGameStated())
	{
		if (IsGameOver())
		{
			return m_game_end_time_ms;
		}
		else
		{
			return m_timer.GetCurrentTimeMs() - m_game_start_time_ms;
		}
	}
	else
	{
		return 0.0;
	}
}


std::string Game::GetSolution() const
{
	if (IsGameOver())
	{
		return m_solution;
	}
	throw std::runtime_error("Solution can only be revealed once the game is over");
}


// progress an agents guess.
// returns true if the guess is correct, otherwise false
bool Game::ProcessGuess(std::string guess)
{
	// ensure the guess is uppercase
	ToUpper(guess);

	// sanity check game is not over
	if (IsGameOver())
	{
		throw std::runtime_error("Game is already over");
	}

	// if the same has not started yet, then start the game
	if (!IsGameStated())
	{		
		m_game_start_time_ms = m_timer.GetCurrentTimeMs();
	}

	// sanity check the word is valid (ie: contained in the word list)
	//TODO - if its not in the word list, then the player agent has missed this turn?

	// add the guess to the list
	m_game_table.push_back(GuessResult(guess, m_solution));

	// update the game letters based on the guess result
	UpdateGameLetters(m_game_letters, m_game_table.back());

	// if the guess is correct
	if (guess == m_solution)
	{
		m_game_solved = true;
		EndGame("Solved");

	}
	// else if, the agent has used all their guesses
	else if (GetNumGuessesUsed() >= GetNumGuesses())
	{
		EndGame("Not solved and no guesses remaining.");
	}

	// return true if the guess was correct
	return m_game_solved;
}


// end the game.
// stops the game time at the current time and sets the game over message.
// required to be public to handle corner cases like disqualification for taking too long.
void Game::EndGame(const std::string& game_over_message)
{
	if (!IsGameOver())
	{		
		m_game_end_time_ms = GetGameTimeMs();
		m_game_over_message = game_over_message;
	}
}

