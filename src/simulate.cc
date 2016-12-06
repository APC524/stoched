#include <stdio.h>
#include "model.h"
#include "paramset.h"
#include "realization.h"


int main(int argc, char* argv[]){
  printf("Hello, World!\n");
  
  int u_len = 4;
  VectorXd u(u_len);
  for (int i = 0; i < u_len; i++){
    u(i) = i*4.3;
  }
  for  (int i = 0; i < u_len; i++){
    printf("%f\n",u(i));
  }

  
  
  
}
