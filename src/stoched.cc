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


using namespace std;

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
  string out_path = "stoched_output.txt";
  
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
  int n_vars = 2;
  int n_events = 4;
  double inits[2] = {0.0, 0.0};
  double t_initial = 0;
  double t_final = 5000;
  double timestep_size = 0.5;
  double n_realizations = 1;
  double max_iter = 100000000;
  int seed = 502;
  Paramset paramset(method, n_vars, inits, t_initial,
                    t_final, timestep_size, n_realizations,
                    max_iter, seed);

  xoroshiro128plus* rng_ptr = new xoroshiro128plus(seed);
  // Open file
  ofstream myfile;
  myfile.open(out_path);

  // Write the header line corresponding to model
  myfile << left << setw(15) << "time";
  int vars_count = model.getVarsCount(); 
  for(int i = 0; i < n_vars; i++){
    string test = model.getIthVar(i);
    myfile << left << setw(15) <<  test;
  }
  myfile << "\n";

  
  /* instantiate realization class
     corresponding to the user-specified
     method (TO DO! Factory Pattern!) */
  FirstReaction realization(model_ptr, paramset,
                              rng_ptr, n_vars, n_events);

  // simulate and clean up
  realization.simulate(myfile);

  return 0;
}
