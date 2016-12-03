#include <stdio.h>
#include "../lib/eigen/Eigen/Core"
#include "../lib/eigen/Eigen/LU"
//#include model.h

using namespace Eigen;

// Example definition for ending simulation loop
// #define TFINAL_OR_MAXITER 0;

int main(int argc, char* argv[]){
  printf("Hello, World!\n");
  
  // Eigen test:
  int u_len = 4;
  VectorXd u(u_len);
  for (int i = 0; i < u_len; i++){
    u(i) = i*4.3;
  }
  for  (int i = 0; i < u_len; i++){
    printf("%f\n",u(i));
  }
  
  // Here: Get parameters from the parser
  
  
  // Parser people to create model realizations
  int max_stop = 0;
  int rate_stop = 0;
  int iter_count=1;
  int done = 0;
  while(done==0){
  
    // Parser dependent calls: 
    // call Realization->step_function();
    // update t from .t_final or iterations from .max_iterations
    
    // Here: write output to file
    
    
    // Stop iterating if t_final or max_ierations is reached 
    // Syntax depends on parser. Could choose one or the other
    // depending on user inputs 
    /*
    if(t>t_final || iter>max_ierations){
      max_stop==1;
    }
    */
    
    // Check rate vector every 500 iterations. If all zeroes we're not updating.
    if(iter_count%500==0){
      if(R.isZero(0)){    // R is the rate vector- also dependent on parser 
        rate_stop = 1;
      }
    }
    if(max_stop==1 || rate_stop==1){
      done = 1;
    }
    iter_count++;
  }
  
}
