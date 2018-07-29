/*
    Author: David Toro
*/

#ifndef RANDOM64_H
#define RANDOM64_H

#include <cstdint>

class Random64
{
private:
    uint64_t seed;
    uint64_t a;
    uint64_t c;
public:
    Random64();
    ~Random64();
private:
    bool checkHullDobelConditions(uint64_t a, uint64_t c);
    bool isEven(uint64_t x);
    bool isDivisibleByFour(uint64_t x);
public:
    bool checkInternalParameters();
    void setSeed(uint64_t seed);
    bool changeLCG(uint64_t a, uint64_t c);
    uint64_t nextRandom();
};

#endif //RANDOM64_H