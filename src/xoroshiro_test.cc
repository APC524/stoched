/**
 *  @file    xoroshirotests.cc
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    1/12/17  
 *  @version 1.0 
 *  
 *  @brief Example xoroshiro code
 *
 */

#include "xoroshiro128plus.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  xoroshiro128plus test_generator(5);

  for(int i = 250; i < 260; i++){
    printf("log(%d!) = %15.15f \n", i, test_generator.log_factorial(i));
  }

  for(int i = 0; i < 3; i++){
    printf("%llu \n", test_generator.next());
  }

  int count = 0;
  int n_sim = 10000;
  double deviate;
  for(int i = 0; i < n_sim; i++){
    deviate = test_generator.runif();
    //printf("%15.8f \n", deviate);
    if(deviate < 0.99){count++;}
  };
  
  printf("%15.8f were less than 0.99 \n", count/float(n_sim));

  for(int k = 0; k < 20; k++){
    printf("Exponential: %15.8f \n", test_generator.rexp(2));
  }

  for(int k = 0; k < 20; k++){
    printf("Poisson: %d \n", (int) test_generator.rpois(30000));
  }

  return 0;
}
