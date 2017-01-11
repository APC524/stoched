/**
 *  @file    rng.h
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *
 *  @brief Based upon public domain xorshift implementations by David Blackman 
 *   and Sebastiano Vigna (vigna@acm.org) 
 *
 */

#ifndef RNG_H_
#define RNG_H_
#include <stdint.h>
#include <math.h>
#include <stdexcept>

inline double to_double(uint64_t x);

/**
 *  @brief Class rng implements random number generator, based upon public domain 
 *         xorshift implementations by David Blackman and Sebastiano Vigna (vigna@acm.org) 
 */
class rng {
 public:

  /// Destructor of rng object
  virtual ~rng() {};
  
  /// get a new random int64
  virtual uint64_t next() = 0;

  /// get a new random uniform(0, 1) RV
  virtual double runif() = 0;

  /// get a new random exponential(lambda) RV
  double rexp(double mean);

  /// get a new random poisson(mean) RV
  long rpois(double mean);
  
  /// quick 2^64 calls to next (for parallelism)
  virtual void jump() = 0;
  

  /** log factorial function modified from public domain C# implementation by
   * John D. Cook (http://www.johndcook.com/blog/csharp_log_factorial/)
   * and PTRS algorithm by Wolfgang Hoermann (1993)
   */
  double log_factorial(int k);

 private:
  long poisson_knuth(double mean); ///< random poisson
  long poisson_ptrs(double mean);  ///< random poisson
};

#endif
