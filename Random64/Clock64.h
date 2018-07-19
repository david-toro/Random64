/*
    Author: David Toro
*/

#ifndef CLOCK64_H
#define CLOCK64_H

#include <cstdint>

#ifdef __linux__

class Clock64
{
private:
    uint64_t startTime;
public:
    Clock64();
    ~Clock64();
    void startClock();
    uint64_t getTime();
    uint64_t getCounter();
};

#elif _WIN32

class Clock64
{
private:
    long double PCFreq;
    uint64_t CounterStart;
public:
    Clock64();
    ~Clock64();
    void startClock();
    uint64_t getTime();
    uint64_t getCounter();
};

#else
   //for others operating systems
#endif

#endif //CLOCK64_H