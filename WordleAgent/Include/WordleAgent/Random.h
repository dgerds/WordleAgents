#pragma once
#include "WordleAgent/framework.h"


class Random
{
public:

    static double GetRandom(double low = 0.0, double high = 1.0);    
    static int GetRandomInt(int low = 0, int high = 100);
};
