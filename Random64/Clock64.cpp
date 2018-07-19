/*
    Author: David Toro
    
    this class definition depends on the operating system
*/

#include "stdafx.h"
#include "Clock64.h"

#ifdef __linux__

Clock64::Clock64()
{
    startTime= 0;
}

Clock64::~Clock64()
{
}

void Clock64::startClock()
{
    startTime= getTime();
}

//get system time in nanoseconds
uint64_t Clock64::getTime()
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (uint64_t) now.tv_sec*1000000000ULL + now.tv_nsec;
}

//get nanoseconds since clock's start
uint64_t Clock64::getCounter()
{
    return getTime() - startTime;
}

#elif _WIN32

#include "Windows.h"

Clock64::Clock64()
{
    PCFreq = 0.0;
    CounterStart = 0;
}

Clock64::~Clock64()
{
}

void Clock64::startClock()
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        std::cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = li.QuadPart / 1000000000.0;   //get nanoseconds

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

//get system time in nanoseconds
uint64_t Clock64::getTime()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return uint64_t(li.QuadPart / PCFreq);
}

//get nanoseconds since clock's start
uint64_t Clock64::getCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return uint64_t((li.QuadPart - CounterStart) / PCFreq);
}

#else
   //for others operating systems
#endif
