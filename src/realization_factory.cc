#include "realization_factory.h"

Realization* RealizationFactory::NewRealization(Model *the_model,
						const Paramset & the_paramset,
						rng *the_rng,
						int n_vars,
						int n_events){
  int method = the_paramset.method;
  
  if(method == 0){
    return new FirstReaction(the_model, the_paramset, the_rng,
			     n_vars, n_events);
  };
  
  if(method == 1){
    return new NextReaction(the_model, the_paramset, the_rng,
			    n_vars, n_events);
  };

  if(method == 2) {
    return new EulerLeap(the_model, the_paramset, the_rng,
                         n_vars, n_events);
  };
  
  return NULL;

}
