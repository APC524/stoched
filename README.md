# stoched
Application for modeling stochastic systems and simulating realizations from them

#### Compiling the code
cd src
make

#### Sample Execution
cd examples
../src/stoched.exe chem.parser.in init_file init_file.txt

For additional information, please see the user guide

#### License information
The main ``stoched`` source code is released under the permissive ``MIT License``. But be aware that some libraries (``Google Test``) and other bits of source code (e.g. parts of the ``xoroshiro128plus`` random number generator) are open source code distributed under other licenses. These are provided -- typically inline in the code -- where relevant. Reuse of those parts of the ``stoched`` source code must reflect the terms of those licenses.
