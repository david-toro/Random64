# Random64

64-bit pseudorandom number generator using a linear congruential generator.

## How it works

Here is a simple example to generate a pseudorandom number.

```cpp
   Clock64 clock;
   clock.startClock();
   
   Random64 lcg;
   lcg.setSeed(clock.getTime());
   uint64_t result= lcg.nextRandom();
```

This LCG can generate a full period of pseudorandom numbers with the right selection of parameters, you can set new parameters for the LCG using the member function changeLCG(), but you must supply valid values for every parameter to meet conditions in Hull-Dobell theorem.

## License

This project is licensed under the BSD 2-Clause License - see the [LICENSE](LICENSE) file for details
