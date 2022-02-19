
#include "WordleAgent/Timer.h"
#include <stdexcept>
#include <profileapi.h>


// constructor
Timer::Timer()
{
	LARGE_INTEGER temp_freq;
	if (QueryPerformanceFrequency(&temp_freq))
	{
		m_timer_freq = static_cast<double>(temp_freq.QuadPart);
	}	
	else
	{
		throw std::runtime_error("Platform does not support QueryPerformanceFrequency");
	}
}


// get the current time in seconds
double Timer::GetCurrentTime() const
{
	LARGE_INTEGER temp_count;
	QueryPerformanceCounter(&temp_count);
	return (temp_count.QuadPart / m_timer_freq);
}

