#pragma once
#include "WordleAgent/framework.h"


class Timer
{
public:
    // constructor
	Timer();

    // get the current time in milliseconds
    double GetCurrentTimeMs() const;

private:

    double m_timer_freq;
};