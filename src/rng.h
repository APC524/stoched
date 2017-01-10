#ifndef RNG_H_
#define RNG_H_
#include <stdint.h>
#include <math.h>
#include <stdexcept>


/*  Based upon public domain xorshift implementations by David Blackman 
    and Sebastiano Vigna (vigna@acm.org) */

inline double to_double(uint64_t x);

class rng {
 public:
  virtual ~rng() {};
  
  // get a new random int64
  virtual uint64_t next() = 0;

  // get a new random uniform(0, 1) RV
  virtual double runif() = 0;

  // get a new random exponential(lambda) RV
  double rexp(double mean);

  // get a new random poisson(mean) RV
  long rpois(double mean);
  
  // quick 2^64 calls to next (for parallelism)
  virtual void jump() = 0;
  double log_factorial(int k);

 private:
  long poisson_knuth(double mean);
  long poisson_ptrs(double mean);
};

#endif
