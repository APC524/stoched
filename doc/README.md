User Guide                         {#usage}
============

###Installation

First go to the [download page](https://github.com/APC524/stoched) to get the latest distribution, if you have not downloaded __stoched__ already.

####Download
Download ZIP file at [__stoched__ Github](https://github.com/APC524/stoched)

    $ unzip stoched-master.zip
    $ cd stoched-master

####Clone Repository

    $ git clone https://github.com/APC524/stoched
    $ cd stoched

###Getting Started

####Step 1: Creating an input file

The parser uses a custom language that is designed to be accessible to non-programmers. It uses minimal syntax and allows for line comments and end of line comments, and whitespace like new lines between commands. It has been designed to reduce the likelihood of redundant and potentially incorrect information.

A simple input file:

    SETUP_VARS "a, b"
    EVENT RATE "3" "a+1" "b+0"
    EVENT RATE "a/3" "a-1" "b+0"

    end

The first line initializes the variables in the simulation with a comma separated variable list enclosed in quotes. Variable names contain the characters A-Z, a-z, and 0-9. The first character, however must be A-Z or a-z. Note that underscores and spaces are not allowed and that the variable list must not contain spaces.

The next line is an event line. An input file can contain as many event lines as needed. In an abstract sense an event consists of the likelihood of the event occuring and a definition of how it changes the system when it occurs. Practically, an event is a rate function followed by any number of equations that involve the variables in the variable list. The rate function and following event functions can contain nonlinear expressions, support the mathematical symbols + - * / ( ), and can contain white space between symbols. 

The last line is end. This indicates the end of the file

A more complicated input file with multiple, nonlinear events:

    SETUP_VARS “a,b,c”
    EVENT RATE “a” “a * (1 + c)” “b - 0.4” “0.56“
    EVENT RATE “a*b/d” “a” “b-c” “a*b*c”

    end

The number of variables and the number of events does not have to be the same. But the number of event functions per event must always equal the number of variables in the variable string. In this example there are three variables: a,b,c; therefore, there are always 4 equations in the EVENT. The first one is the rate function and the last three indicate how the three variables are modified. So the first event occurs at a rate equal to a, and when it occurs it sets a = a * (1 + c), it sets b = b - 0.4, and it sets c = 0.56.

Finer points:
Note the syntax “a+1” and “a    +     1” are both acceptable. Scientific notation is not yet supported

Lines can be commented by placing a # character. The parser ignores all text on a line after a # character. This means that it can be used to comment out a whole line if it is placed at the beginning of a line, or used to add a note at the end of a line

Comment Example:

    # This code is now well commented
    SETUP_VARS “a,b”
    # EVENT RATE “2” “a - 5” “b - 5”
    EVENT RATE “3” “a + 1” “b + 1”     #  I’ve added a comment here to explain why the rate is 3
    end

In the above example the first event will be ignored because the line begins with #. When the second line is parsed, only the text “I’ve added …” is removed. This input file is functionally equivalent to the first example input file, but it is more readable by human because it had comments.


####Step 2: Running stoched

##### Compiling Serial Code

    stoched-master$ cd src
    stoched-master/src$ make

##### Sample Execution of Serial Code
    
    stoched-master$ cd examples
    stoched-master/examples$ ../src/stoched.exe chem.parser.in init_file init_file.txt

##### Compiling Parallel Code

Assumes installation of OpenMPI

    stoched-master$ cd src
    stoched-master/src$ make parallel

##### Sample Execution of Parallel Code

For usage on Adroit.

    stoched-master$ cd examples    
    stoched-master/examples$ sbatch run_mpi.slurm


##### Compiling Test Code

Assumes installation of Google Test suite

    stoched-master$ cd src
    stoched-master/src$ make googletests

##### Sample Execution of Test Code
    
    stoched-master$ cd src
    stoched-master/src$ ./testmodel.exe


####Step 3: Parameters

To specify additional parameters, the user may include additional command line arguments, which are listed below. For example, to run the simulation 5 times, the command would look like this:

    stoched-master/src$ ./stoched.exe example.parser.in n_realizations 5

The command line arguments are as follows:

__init_file__: Required for specifying the initial states data for most model definitions. The exception is a model definition with two species which each start with zero population. This is the default initial state. 

__method__: specifies which algorithm is used to perform computations. Specifying 0 will run the exact Gillespie algorithm, while 1 will run the Euler tau-leap method, and 2 will run the midpoint tau-leap method. Default is 0. 

__t_initial__: allows user to modify the starting time of the simulation. Default is 0 .

__t_final__: allows user to modify the end time of the simulation. Default is 5000 . 

__timestep_size__: allows user to fix timestep size if desired. 

__n_realizations__: allows user to run the simulation multiple times with the same model and model conditions. Default value is 1. 

__max_iter__: allows user to specify maximum number of iterations. Default value is 100000000.

__seed__: allows user to fix a seed of the random number generator (which allows for verification of consistency between multiple runs, and with external software results). The default value is 502. 

__out_path__: Allows user to specify an alternative output file path name. The default value is stoched_output, which will write to a file named stoched_output.txt . The extension is not required when specifying pathname. 

__suppress_print__: Option specified as either a 0 or 1. If 1, the software prints only the final value of the simulation to each output file. If 0 (default value), the software runs as usual, printing the results at each timestep. Specifying 1 results in significant speedup of the code. 


####Step 4: Access Documentation

For further information, visit the Doxygen-generated documentation. The associated HTML documentation can be viewed by pointing a HTML browser to the index.html file in the doc/html directory

To see a PDF version of the documentation, open the refman.pdf file located the doc/latex directory
