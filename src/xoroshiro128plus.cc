/** 
 *  @file    xoroshiro128plus.cc
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief Class xoroshorio128plus implements a random number 
 *         generator of Class rng
 *  
 */

#include "xoroshiro128plus.h"
#include "rng.h"

/// convert uint64_t to double in (0, 1)
inline double to_double(uint64_t x) {
       const union { uint64_t i; double d; } u = { .i = UINT64_C(0x3FF) << 52 | x >> 12 };
       return u.d - 1.0;
}

/// splitmix64 next function, for initializing generator
uint64_t xoroshiro128plus::splitmix64() {
	uint64_t z = (splitmixstate += UINT64_C(0x9E3779B97F4A7C15));
	z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
	z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
	return z ^ (z >> 31);
}

/** initialize state with splitmix64 random ints
 *  from seed int (prevents similar seeds from generating
 *  correlated states) 
 */
xoroshiro128plus::xoroshiro128plus(int seed) : rng::rng() {

  splitmixstate = seed;
  s[0] = splitmix64();
  s[1] = splitmix64();
}

/// Default Destructor for Xoroshiro128plus
xoroshiro128plus::~xoroshiro128plus(){}

/// simulated rotate
inline uint64_t xoroshiro128plus::rotl(const uint64_t x, int k) {
  return (x << k) | (x >> (64 - k));
}

/// get random int and update state
uint64_t xoroshiro128plus::next() {
  const uint64_t s0 = s[0];
  uint64_t s1 = s[1];
  const uint64_t result = s0 + s1;

  s1 ^= s0;
  s[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14); // a, b
  s[1] = rotl(s1, 36); // c

  return result;
}


/// get random uniform(0, 1) double and update state
double xoroshiro128plus::runif() {
  return to_double(next());
}

/** This is the jump function for the generator. It is equivalent
 *  to 2^64 calls to next(); it can be used to generate 2^64
 *  non-overlapping subsequences for parallel computations. */
void xoroshiro128plus::jump() {
  static const uint64_t JUMP[] = { 0xbeac0467eba5facb, 0xd86b048b86aa9922 };

  uint64_t s0 = 0;
  uint64_t s1 = 0;
  for(uint64_t i = 0; i < sizeof JUMP / sizeof *JUMP; i++)
    for(int b = 0; b < 64; b++) {
      if (JUMP[i] & 1ULL << b) {
        s0 ^= s[0];
        s1 ^= s[1];
      }
      next();
    }
  
  s[0] = s0;
  s[1] = s1;
}
