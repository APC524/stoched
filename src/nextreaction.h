#ifndef NEXTREACTION_H_
#define NEXTREACTION_H
#include "realization.h"
#include <float.h>

class NextReaction : public Realization {
 public:
  NextReaction(Model *the_model, const Paramset & the_paramset,
               rng *the_rng, int n_vars, int n_events);
  ~NextReaction();
  int step();
  int set_to_initial_state();
 private:
  double *waiting_times;
};

#endif 
