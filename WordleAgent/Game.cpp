
#include "WordleAgent/Game.h"
#include <stdexcept>


namespace
{
	GuessResult GetGuessResult(const std::string& guess, const std::string& solution)
	{
		GuessResult gr;
		gr.guess = guess;
		gr.result.resize(guess.size());
		for (size_t i = 0; i < guess.size(); i++)
		{
			// up to here - TODO
			gr.result[i] = Colour::GREEN;
		}
		return gr;
	}
}


double Game::GetGameTime() const
{
	return 1.0;
}


std::string Game::GetSolution() const
{
	return m_solution;
}


// progress an agents guess.
// returns true if the guess is correct, otherwise false
bool Game::ProcessGuess(const std::string& guess)
{
	// sanity check game is not over
	if (IsGameOver())
	{
		throw std::runtime_error("Game is already over");
	}

	// if this is the first guess, start the game
	if (!m_game_started)
	{
		m_game_started = true;
		// TODO - start timer
	}

	// add the guess to the list
	m_game_table.push_back(GetGuessResult(guess, m_solution));

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
	//todo
}

