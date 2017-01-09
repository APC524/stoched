#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <chrono>
#if defined(_OPENMP)
   #include <omp.h> 
#endif

#include "event.h"
#include "model.h"
#include "paramset.h"
#include "realization.h"
#include "xoroshiro128plus.h"
#include "realization_factory.h"


//using namespace std;
using namespace std::chrono;

//declare the parser method written by flex and bison
int parseFile(Model& model);

/* eventually parseFile will take a std::string
   argument giving the path to the model file
   that will be parsed (and possibly also a 
   pointer to a paramset to be populated, with
   a path to an input file of parameters */

// wrapper for argument validation
int validate_args(int argc, char *argv[]) {
  // do very basic argument validation for now
  if (argc < 3) {
    printf("\nExpected at least 2 arguments, got %i \n\n"
           "USAGE: %s <model file> <parameter file>\n\n"
           "<model file>: Path to a file "
           "specifying a stoched model\n"
           "<parameter file>: Path to a file "
           "giving parameters for the model realization\n\n",
           argc - 1, argv[0]);
    exit(1);
  }
  return 0;
}

int main(int argc, char *argv[]) {

  // do argument validation
  validate_args(argc, argv);
  
  // coerce arg variables to usable types 
  string model_path = argv[1];
  string param_path = argv[2];

  // allow user-specified output path, or default
  string out_path = "stoched_output";
  
  // declare model
  Model *model_ptr;
  Model model;
  model_ptr = & model;

  // populate model from parser
  int res = parseFile(model);
  if (res != 0) {
    fprintf(stderr, "Error: Parser returned %d", res);
  }

  // test that the Model was initialized by the parser properly
  // TO BE IMPLEMENTED 

  // manually specified parameters for now
  int method = 0;
  double inits[2] = {0.0, 0.0};
  double t_initial = 0;
  double t_final = 5000;
  double timestep_size = 0.5;
  int n_realizations = 1;
  double max_iter = 100000000;
  int seed = 502;

  /* save fixed number of variables, events
     from the now-assembled model */
  int n_vars = model_ptr->getVarsCount();
  int n_events = model_ptr->getEventsCount();

  Paramset paramset(method, n_vars, inits, t_initial,
                    t_final, timestep_size, n_realizations,
                    max_iter, seed);

  // instantiate rng
  xoroshiro128plus* rng_ptr = new xoroshiro128plus(seed);

  // instantiate RealizationFactory
  RealizationFactory factory; 

  // Instantiate timer 
  high_resolution_clock::time_point t1 = high_resolution_clock::now();

  #if defined(_OPENMP)
  // Set up OMP environment/variables 
  omp_set_dynamic(0);     // Explicitly disable dynamic teams
  int nthreads = omp_get_max_threads();
  omp_set_num_threads(nthreads);
  #endif

  // Loop over instantiations of realizations for same model: 
  int i=0;
  #if defined(_OPENMP)
  #pragma omp parallel for private(i)
  #endif

  for(i = 0; i < n_realizations; i++){
    // Open file
    ofstream myfile;
    string write_out_path = out_path + "_realization_" + to_string(i+1) + ".txt";

    myfile.open(write_out_path);
    // Write the header line corresponding to model
    myfile << left << setw(15) << "time";
    int vars_count = model.getVarsCount(); 
    for(int i = 0; i < n_vars; i++){
      string test = model.getIthVar(i);
      myfile << left << setw(15) <<  test;
    }
    myfile << "\n";

    // instantiate realization class
    Realization *realization = factory.NewRealization(model_ptr,
						      paramset,
						      rng_ptr,
						      n_vars,
						      n_events);

    
    // check that realization factory worked
    if(realization == NULL){
      fprintf(stderr,
	      "Error: unrecognized method id\n "
	      "(received id: %d) \n",
	      paramset.method);
      return 1;
    }
    
    // simulate and clean up
    realization->simulate(myfile);
    myfile.close();
  }
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  auto duration_first = duration_cast<microseconds>( t2 - t1 ).count();
  #if defined(_OPENMP)
  printf("Test ran with %d threads \n", nthreads);
  #endif
  printf("Test ran in %15.8f seconds \n", duration_first * 1.0e-6);

  return 0;
}
