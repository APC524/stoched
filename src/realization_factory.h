#ifndef REALIZATION_FACTORY_H_
#define REALIZATION_FACTORY_H_
#include "realization.h"

class RealizationFactory {
 public:
  RealizationFactory(){};
  ~RealizationFactory(){};
  static Realization* NewRealization(Model *the_model,
				     const Paramset & the_paramset,
				     rng *the_rng,
				     int n_vars,
				     int n_events);
};

#endif
