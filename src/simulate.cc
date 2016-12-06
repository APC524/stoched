#include <stdio.h>
#include "../lib/eigen/Eigen/Core"
#include "../lib/eigen/Eigen/LU"
#include "model.h"
#include "paramset.H"

using namespace Eigen;

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
