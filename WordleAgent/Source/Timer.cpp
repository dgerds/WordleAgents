
#include "WordleAgent/Timer.h"
#include <stdexcept>
#ifdef _WIN32
#include <profileapi.h>
#elif __linux__



#include <stdint.h>

typedef uint8_t BYTE;
typedef uint32_t DWORD;
typedef int32_t LONG;
typedef int64_t LONGLONG;

typedef union _LARGE_INTEGER {
  struct {
    DWORD LowPart;
    LONG  HighPart;
  };
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

// for high resolution time stamps
bool QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency){
  *lpFrequency = {0,0};
  return true;
}
bool QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount){
  *lpPerformanceCount = {0,0};
  return true;
}


#endif


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


// get the current time in milliseconds
double Timer::GetCurrentTimeMs() const
{
	LARGE_INTEGER temp_count;
	QueryPerformanceCounter(&temp_count);
	return (temp_count.QuadPart / m_timer_freq) * 1000.0;
}

