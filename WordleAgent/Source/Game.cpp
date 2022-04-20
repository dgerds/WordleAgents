
#include "WordleAgent/Game.h"
#include <stdexcept>
#include <string>
#include <algorithm>


namespace
{
	// update the given game letters based on the given guess result
	void UpdateGameLetters(GameLetters& game_letters, const std::string& guess, const std::vector<Colour>& result)
	{
		for (size_t i = 0; i < guess.size(); i++)
		{
			auto iter = game_letters.find(guess[i]);
			if (iter != game_letters.end())
			{
				// if (the result for this letter is "better" than the current game_letters result) then
				if (result[i] < iter->second)
				{
					// update the game_letters result
					iter->second = result[i];
				}
			}
		}
	}
}


// constructor
GuessResult::GuessResult(const std::string& guess, const std::string& solution, const GameLetters& game_letters)
	: guess(guess),
	  letters(game_letters)
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
		// if (the guess character is in the exact correct position) then
		if (guess[i] == solution[i])
		{
			result[i] = Colour::GREEN;
		}
		// if (the guess character is located in the word somewhere else) then
		else if (solution.find(guess[i]) != std::string::npos)
		{
			// we need to check if all instances of the character in the solution have been guessed correctly
			bool all_correct = true;
			for (size_t j = 0; j < solution.size(); j++)
			{
				// if (this is an instance of the character in the solution)
				if (solution[j] == guess[i])
				{
					// if (the guess was not correct for this character)
					if (guess[j] != solution[j])
					{
						all_correct = false;
						break;
					}
				}
			}
			// if (all instances have been found) then BLACK, else YELLOW
			result[i] = all_correct ? Colour::BLACK : Colour::YELLOW;
		}
		// else (the guess character is not in the word at all)
		else
		{
			result[i] = Colour::BLACK;
		}
	}

	// update the game letters based on guess and result calculated above
	UpdateGameLetters(letters, guess, result);
}


// constructor
Game::Game(const std::string& solution,
		   int num_guesses,
		   const WordList& word_list)
  : m_game_solved(false),
	m_solution(ToUpperCopy(solution)),
	m_num_guesses(num_guesses),
	m_game_start_time_ms(0.0),
	m_game_end_time_ms(0.0),
	m_word_list(word_list),
	m_word_set(word_list.begin(), word_list.end()),
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

	// sanity check the word is valid (ie: the correct length and contained in the word list)
	if ((guess.length() != m_word_list[0].length()) ||
		(m_word_set.find(guess) == m_word_set.end()))
	{
		// invalid word - this counts as a guess, but can't be useful as a guess
		// otherwise players could cheat by using words like "aeiou".
		// replace the guess with something useless of the correct length.
		guess = std::string(m_word_list[0].length(), '*');
	}

	// add the guess to the list
	m_game_table.push_back(GuessResult(guess, m_solution, m_game_letters));

	// update the game letters based on the guess result
	m_game_letters = m_game_table.back().letters;

	// if the guess is correct
	if (guess == m_solution)
	{
		m_game_solved = true;
		EndGame();

	}
	// else if, the agent has used all their guesses
	else if (GetNumGuessesUsed() >= GetNumGuesses())
	{
		EndGame();
	}

	// return true if the guess was correct
	return m_game_solved;
}


// transform the given string to uppercase
void Game::ToUpper(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::toupper(c); });
}


// return a copy of the given string transformed to uppercase
std::string Game::ToUpperCopy(const std::string& str)
{
	std::string temp(str);
	ToUpper(temp);
	return temp;
}


// end the game.
// stops the game time at the current time.
void Game::EndGame()
{
	if (!IsGameOver())
	{
		m_game_end_time_ms = GetGameTimeMs();
	}
}
