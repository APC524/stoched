#include "xoroshiro128plus.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  xoroshiro128plus test_generator(5);

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
  return 0;
}
