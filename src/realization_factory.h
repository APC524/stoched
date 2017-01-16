/** 
 *  @file    realization_factory.h
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief Class RealizationFactory generates required instance of Realization 
 *         (FirstReaction, NextReaction, EulerLeap) based on input
 *  
 */


#ifndef REALIZATION_FACTORY_H_
#define REALIZATION_FACTORY_H_
#include "realization.h"
#include "nextreaction.h"
#include "firstreaction.h"
#include "eulerleap.h"
#include "midpointleap.h"

/**  
 *  @brief Class RealizationFactory generates required instance of Realization 
 *         (FirstReaction, NextReaction, EulerLeap, MidpointLeap) 
 *         based on input
 *  
 */
class RealizationFactory {
 public:
  
  // Default constructor for RealizationFactory
  RealizationFactory(){};

  // Destructor of RealizationFactory
  ~RealizationFactory(){};

  // Create new realization
  static Realization* NewRealization(Model *the_model,
				     const Paramset & the_paramset,
				     rng *the_rng,
				     int n_vars,
				     int n_events);
};

#endif
