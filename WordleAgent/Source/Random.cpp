
#include "WordleAgent/Random.h"
#include "WordleAgent/Timer.h"
#include <time.h>
#include <iostream>


namespace
{
    // seed the random number generator with a current time value
    int SeedRandomness()
    {
        srand(static_cast<unsigned int>(Timer().GetCurrentTimeMs() * 10000));
        return 0;
    }
}


double Random::GetRandom(double low, double high)
{
    SeedRandomness();
    return low + ((((double)rand()) / (double)RAND_MAX) * (high - low));
}


int Random::GetRandomInt(int low, int high)
{
    return static_cast<int>(low + (GetRandom() * (high - low + 0.9999999)));
}
