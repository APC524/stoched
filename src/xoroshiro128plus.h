#ifndef XOROSHIRO128_H_
#define XOROSHIRO128_H_
#include <stdint.h>
#include "rng.h"

/*  Based on xorshift128+ implementation by David Blackman and Sebastiano Vigna (vigna@acm.org) */

/* This is the successor to xorshift128+. It is the fastest full-period
   generator passing BigCrush without systematic failures, but due to the
   relatively short period it is acceptable only for applications with a
   mild amount of parallelism; otherwise, use a xorshift1024* generator.

   Beside passing BigCrush, this generator passes the PractRand test suite
   up to (and included) 16TB, with the exception of binary rank tests,
   which fail due to the lowest bit being an LFSR; all other bits pass all
   tests. We suggest to use a sign test to extract a random Boolean value.
   
   Note that the generator uses a simulated rotate operation, which most C
   compilers will turn into a single instruction. In Java, you can use
   Long.rotateLeft(). In languages that do not make low-level rotation
   instructions accessible xorshift128+ could be faster.

   The state must be seeded so that it is not everywhere zero. If you have
   a 64-bit seed, we suggest to seed a splitmix64 generator and use its
   output to fill s. */

class xoroshiro128plus : public rng {
 public:
  xoroshiro128plus(int seed);
  ~xoroshiro128plus();
  
  // get a new random int64
  uint64_t next();

  // get a new random uniform(0, 1) RV
  double runif();

  // quick 2^64 calls to next (for parallelism)
  void jump();

 private:
  // state of the generator
  uint64_t s[2];

  // simulated rotate
  inline uint64_t rotl(const uint64_t x, int k);

  // splitmix64 implementation transforming seed
  uint64_t splitmixstate;
  uint64_t splitmix64();

};

#endif
