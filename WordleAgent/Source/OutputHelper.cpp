#include "WordleAgent/OutputHelper.h"
#include <iostream>

#ifdef _WIN32
#elif __linux__

// Console API Functions
const int STD_OUTPUT_HANDLE = 1;
int GetStdHandle(int handle) {
  return 0;
}
bool SetConsoleTextAttribute(int handle, int attributes) {
  return true;
}

#endif


namespace
{
	// cache handle to the standard output console
	auto CACHED_STD_OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);

	// get the windows console colour code for the given colour
	int GetConsoleColourCode(Colour c = Colour::NONE)
	{
		switch (c)
		{
		case Colour::GREEN: return 160;
		case Colour::YELLOW: return 224;
		case Colour::BLACK: return 128;
		case Colour::GREY: return 112;
		}
		return 7; // default console
	}
}


void OutputHelper::Print(const GuessResult& p)
{
	// for each letter in the guess, change to the matching colour and print the letter
	for (size_t i = 0; i < p.guess.length(); i++)
	{
		SetConsoleTextAttribute(CACHED_STD_OUTPUT_HANDLE, GetConsoleColourCode(p.result[i]));
		std::cout << p.guess[i];
	}

	// return to the default console colour before returning
	SetConsoleTextAttribute(CACHED_STD_OUTPUT_HANDLE, GetConsoleColourCode());
}


void OutputHelper::Print(const GameLetters& p)
{
	// for each letter in the map, change to the matching colour and print the letter
	for (auto iter = p.begin(); iter != p.end(); ++iter)
	{
		SetConsoleTextAttribute(CACHED_STD_OUTPUT_HANDLE, GetConsoleColourCode(iter->second));
		std::cout << iter->first;
	}

	// return to the default console colour before returning
	SetConsoleTextAttribute(CACHED_STD_OUTPUT_HANDLE, GetConsoleColourCode());
}
