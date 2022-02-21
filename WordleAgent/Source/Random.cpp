
#include "WordleAgent/Random.h"
#include "WordleAgent/Timer.h"
#include <time.h>
#include <iostream>


namespace
{
    // automatically seed with a random time value at startup
    int AutoSeedRandomness()
    {
        auto t = Timer();
        Random::SeedRandomness(static_cast<unsigned int>(t.GetCurrentTime() * 1000000));
        return 0;
    }
    int discard = AutoSeedRandomness();
}


void Random::SeedRandomness(unsigned int value)
{
    srand(value);
}


double Random::GetRandom(double low, double high)
{
    return low + ((((double)rand()) / (double)RAND_MAX) * (high - low));
}


int Random::GetRandomInt(int low, int high)
{
    return static_cast<int>(low + (GetRandom() * (high - low + 0.9999999)));
}
