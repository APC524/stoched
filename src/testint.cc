#include <stdio.h>
#include <stdint.h>

#ifndef INT64_C
#define INT64_C(c) (int64_t) c
#define UINT64_C(c) (uint64_t) c

int main(){
  #if __cplusplus < 201103L
  printf("OLD COMPILER\n");
  #endif

#if __cplusplus < 199711L
  printf ("REALLY old compiler\n");
#endif
                    
  printf("not defined\n");
  uint64_t test = UINT64_C(0x3FF);
  printf("%llu \n", test);
  printf("%llu \n", (uint64_t) (0x3FF));

  return 0;
}

#else

int main(){
    #if __cplusplus < 199711L
  #warning "stoched should ideally be compiled by a compiler that supports C++11 or later. Support for earlier C++ standards is experimental"
  printf("OLD COMPILER\n");
  #endif

#if __cplusplus < 199711L
  printf ("REALLY old compiler\n");
#endif

    #if __cplusplus < 201103L
  printf("OLD COMPILER\n");
  #endif
  printf("defined");
  //uint64_t test = UINT64_C(0x3FF);
  // printf("%llu \n", test);
  printf("%llu \n", (uint64_t) (0x3FF));

  return 0;
}

#endif
