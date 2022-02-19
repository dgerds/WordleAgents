#pragma once
#include "WordleAgent/framework.h"
#include "WordleAgent/Game.h"

class OutputHelper
{
public:
    static void Print(const GuessResult& p);
    static void Print(const GameLetters& p);
};
