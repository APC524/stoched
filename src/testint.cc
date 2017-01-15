#include <stdio.h>
#include <stdint.h>

#ifndef INT64_C
#define INT64_C(c) (int64_t) c
#define UINT64_C(c) (uint64_t) c

int main(){
  printf("not defined");
  //uint64_t test = UINT64_C(0x3FF);
  // printf("%llu \n", test);
  printf("%llu \n", (uint64_t) (0x3FF));

  return 0;
}

#else

int main(){
  printf("defined");
  //uint64_t test = UINT64_C(0x3FF);
  // printf("%llu \n", test);
  printf("%llu \n", (uint64_t) (0x3FF));

  return 0;
}

#endif
