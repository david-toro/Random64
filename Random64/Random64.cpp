/*
    Author: David Toro
*/

#include "stdafx.h"
#include "Random64.h"
#include <cmath>

/*
    This code use a linear congruential generator (LCG) with m= 2^64

    x(i+1) = ( a*x(i) + c ) mod m
    0 < m         modulus
    0 < a < m     multiplier
    0 <= c < m    increment
    0 <= X0 < m   seed (start value)

    selected values for a and c:
   
    a = 2^63 + 1
    c= a / 9;
*/

Random64::Random64()
{
    seed = 0;
    a = 9223372036854775809ULL;
    c = 1024819115206086201ULL;
}

Random64::~Random64()
{

}

/**
Conditions to have a full period:

Hull-Dobell Theorem:
----------------------------------------------------------------------------------------------------------
Provided that the offset c is nonzero, the LCG will have a full period for all seed values if and only if:

1. c and m are relatively prime
2. a-1 is divisible by all prime factors of m
3. a-1 is a multiple of 4 if m is a multiple of 4
----------------------------------------------------------------------------------------------------------
*/
bool Random64::checkHullDobelConditions(uint64_t a, uint64_t c)
{
	// 2 is the unique prime factor of m= 2^64
	// c must be an odd number so it is not divisible by 2, so the greater common divisor of c and m is 1
	bool result = !isEven(c);

	//a-1 is divisible by 2 and 4 according to conditions 2 and 3
	return result && isEven(a - 1) && isDivisibleByFour(a - 1);
}

bool Random64::isEven(uint64_t x)
{
	return x % 2 == 0;
}

bool Random64::isDivisibleByFour(uint64_t x)
{
	return x % 4 == 0;
}

/**
   @return true if the internal parameters meet the conditions of Hull-Dobel for a full period in a LCG
*/
bool Random64::checkInternalParameters()
{
	return checkHullDobelConditions(this->a, this->c);
}

void Random64::setSeed(uint64_t seed)
{
    this->seed = seed;
}

bool Random64::changeLCG(uint64_t a, uint64_t c)
{
	if (checkHullDobelConditions(a, c))
	{
		std::cout << "New parameters for the LCG are right\n" << std::endl;
		this->a = a;
		this->c = c;
		return true;
	}
	else
	{
		std::cout << "New parameters for the LCG are wrong: preserving the old values\n" << std::endl;
		return false;
	}
}

uint64_t Random64::nextRandom()
{
    seed = a * seed + c; //the module 2^n of a binary number are the n least significant bits 
    return seed;
}
