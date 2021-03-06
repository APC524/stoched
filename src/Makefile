# -----------------------------------------------------------------------------
# Kevin Griffin, Caleb Peckham, Julienne LaChance, Dylan Morris
# 11/29/16, APC 524, Final Project
# Makefile
# -----------------------------------------------------------------------------
CXX = g++
MPICXX = mpicc
CXXFLAGS = -g -Wall -lm -O3
OMPCXXFLAGS = -g -Wall -lm -O3 # -fopenmp
RM = rm -f

OBJECTS = fparser/fparser.o event.o model.o lex.yy.o parser.bison.o tauleapavail.o

BASIC_CLASSES = model.o event.o realization.o paramset.o realization_factory.o
REALIZATIONS = nextreaction.o firstreaction.o eulerleap.o midpointleap.o
RANDOM = rng.o xoroshiro128plus.o

CLASSES = $(BASIC_CLASSES) $(REALIZATIONS) $(RANDOM)

# default to building no mpi and no google tests
default: stoched.exe testparser.exe testevent.exe testmodel.exe testsimulate.exe xoroshiro_test.exe

# if parallel, then always compile stoched_parallel.cc with MPICXX, then
# check the stoched_parallel.exe
parallel: 
	$(MPICXX) -std=c++0x -c stoched_parallel.cc
	make stoched_parallel.exe

googletests: eventtests.exe modeltests.exe parsertests.exe xoroshiro_test.exe

testparser.exe: testparser.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ 

testevent.exe: event.o testevent.o fparser/fparser.o
	$(CXX) $(CXXFLAGS) $^ -o $@  

testmodel.exe: model.o event.o testmodel.o fparser/fparser.o
	$(CXX) $(CXXFLAGS) $^ -o $@

testmodel: model.o event.o testmodel.o fparser/fparser.o
	$(CXX) $(CXXFLAGS) $^ -o $@

testsimulate.exe: testsimulate.o $(CLASSES) fparser/fparser.o
	$(CXX) $(CXXFLAGS) $^ -o $@

eventtests.exe: gtest/include eventtests.o $(CLASSES) fparser/fparser.o gtest/libgtest.a 
	$(CXX) $(OMPCXXFLAGS) -I $^ -lpthread -o $@

modeltests.exe: gtest/include modeltests.o $(CLASSES) fparser/fparser.o gtest/libgtest.a 
	$(CXX) $(OMPCXXFLAGS) -I $^ -lpthread -o $@

parsertests.exe: gtest/include parsertests.o $(OBJECTS) gtest/libgtest.a 
	$(CXX) $(OMPCXXFLAGS) -I $^ -lpthread -o $@

stoched.exe: stoched.o $(OBJECTS) $(CLASSES)
	$(CXX) $(CXXFLAGS) $^ -o  $@

stoched_parallel.exe: stoched_parallel.o $(OBJECTS) $(CLASSES)
	$(MPICXX) $(CXXFLAGS) $^ -o $@

fparser/fparser.exe: fparser/example2.o fparser/fparser.o
	$(CXX) $^ -o $@

xoroshiro_test.exe: xoroshiro_test.o $(RANDOM)
	$(CXX) $^ -o $@

# use flex and bison to generate parser source code
parser.bison.cc parser.bison.hh: parser.y
	bison -d -o parser.bison.cc parser.y

lex.yy.cc: parser.l parser.bison.hh
	flex -o lex.yy.cc parser.l

# dependency rules
fparser/fparser.o: fparser/fparser.cc
	$(CXX) -c $^ -o $@

#fparser/example2.o: fparser/example2.cc fparser/fparser.o
#	$(CXX) $^ -o $@

%.o: %.cc
	$(CXX) -std=c++0x -c $<

#%.o: %.c
#	$(CXX) -std=c++0x -c $<

# clean up object code and executables
clean:
	$(RM) *.exe
	$(RM) *.o
	$(RM) fparser/*.o
	$(RM) -r *.dSYM
	$(RM) *output*.txt

# clean up emacs temp files
clobber: clean
	$(RM) *~ \#*\#
