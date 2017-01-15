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



/* Legacy C++ standard double conversion based upon open-source code by
 * Artur Grabowski, which appears with the following license:
 *
 * Copyright (c) 2015 Artur Grabowski <art@blahonga.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


#include "xoroshiro128plus.h"
#include "rng.h"

// support for C++ stds <= C++11
#ifndef INT64_C
#define INT64_C(c) (int64_t) c
#define UINT64_C(c) (uint64_t) c
#endif

#if __cplusplus < 199711L
#warning "stoched should ideally be compiled by a compiler that supports C++11 or later. Support for earlier C++ standards is experimental"
#include "math.h"
#include "string.h"
/// convert uint64_t to double in (0, 1)
inline double to_double(uint64_t x){
	uint64_t x52 = x & ((1ULL << 53) - 1);
        int e = ffsll(x52);
	uint64_t m;
	if (e > 52 || e == 0)
		return 0.0;
	/* Shift out the bit we don't want set. */
	m = (x52 >> e) << (e - 1);
	return ldexp(0x1p52 + m, -52 - e);
}

#else 
/// convert uint64_t to double in (0, 1)
inline double to_double(uint64_t x) {
       const union { uint64_t i; double d; } u = { .i = UINT64_C(0x3FF) << 52 | x >> 12 };
       return u.d - 1.0;
}

#endif

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
