#ifndef FIRSTREACTION_H_
#define FIRSTREACTION_H_

#include "realization.h"

class FirstReaction : public Realization {
 public:
  FirstReaction(Model *the_model, const Paramset & the_paramset,
               rng *the_rng, int n_vars, int n_events);
  ~FirstReaction();
  int step();
 private:
  double *waiting_times;
};

#endif
