#include "xoroshiro128plus.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  xoroshiro128plus test_generator(5);

  for(int i = 0; i < 3; i++){
    printf("%llu \n", test_generator.next());
  }
  
  return 0;
}
