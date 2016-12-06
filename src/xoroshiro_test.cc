#include "xoroshiro128plus.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  xoroshiro128plus test_generator(4);

  for(int i = 0; i < 3; i++){
    printf("%llu \n", test_generator.next());
  }

  int count = 0;
  int n_sim = 100000;
  double deviate;
  for(int i = 0; i < n_sim; i++){
    deviate = test_generator.runif();
    //printf("%15.8f \n", deviate);
    if(deviate < 0.99){count++;}
  };
  
  printf("%15.8f were less than 0.99 \n", count/float(n_sim));

  return 0;
}
