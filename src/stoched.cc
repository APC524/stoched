#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <chrono>
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
  //string param_path = argv[2];

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

  // default parameters
  int method = 0;
  int n_realizations = 1;
  double max_iter = 100000000;
  double timestep_size = -1.0;
  int seed = 502;
  int nthreads = -1;

  int n_vars = model_ptr->getVarsCount();
  int n_events = model_ptr->getEventsCount();

  double t_initial, t_final;

  /* create array to hold user-specified initial values
     SOMEONE PLEASE IMPLEMENT THIS */
  double inits[n_vars];
  for(int k = 0; k < n_vars; k++){inits[k] = 0;};

  // Set non-default params from inputs 
  if(argc>3){
    for(int j = 3; j < argc; j++){

        // CONVERT TYPES 

        if (string(argv[j]) == "method") {
          // We know the next argument *should* be the filename:
          method = atoi(argv[j + 1]);
        } else if (string(argv[j]) == "t_initial") {
          t_initial = atof(argv[j + 1]);
        } else if (string(argv[j]) == "t_final") {
          t_final = atof(argv[j + 1]);
        } else if (string(argv[j]) == "timestep_size") {
          timestep_size = atof(argv[j + 1]);
        } else if (string(argv[j]) == "n_realizations") {
          n_realizations = atoi(argv[j + 1]);
        } else if (string(argv[j]) == "max_iter") {
          max_iter = atof(argv[j + 1]);
        } else if (string(argv[j]) == "seed") {
          seed = atoi(argv[j + 1]);
        } else if (string(argv[j]) == "nthreads") {
          nthreads = atoi(argv[j + 1]);
        }
    }
  }

  // Fix method parameters 
  Paramset paramset(method, n_vars, inits, t_initial,
                    t_final, timestep_size, n_realizations,
                    max_iter, seed);

  // instantiate rng
  xoroshiro128plus* rng_ptr = new xoroshiro128plus(seed);

  // instantiate RealizationFactory
  RealizationFactory factory; 

  // Instantiate timer 
  high_resolution_clock::time_point t1 = high_resolution_clock::now();

  // Loop over instantiations of realizations for same model: 

  for(int i = 0; i < n_realizations; i++){
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
  printf("Test ran in %15.8f seconds \n", duration_first * 1.0e-6);

  return 0;
}
