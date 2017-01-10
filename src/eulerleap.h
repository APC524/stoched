#ifndef EULERLEAP_H_
#define EULERLEAP_H_
#include "realization.h"
#include <stdexcept>  

/**  
 *  @brief Class EulerLeap implements Realization step() function 
 *         using Euler Leap method
 */  

class EulerLeap : public Realization {
 public:
  EulerLeap(Model *the_model, const Paramset & the_paramset,
               rng *the_rng, int n_vars, int n_events);
  ~EulerLeap();
  int step();
  int set_to_initial_state();
};

#endif 
