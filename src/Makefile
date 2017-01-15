# -----------------------------------------------------------------------------
# Kevin Griffin, Caleb Peckham, Julienne LaChance, Dylan Morris
# 11/29/16, APC 524, Final Project
# Makefile
# -----------------------------------------------------------------------------
CXX = g++-6
MPICXX = mpicc
CXXFLAGS = -g -Wall -lm -O3 -std=c++0x
OMPCXXFLAGS = -g -Wall -lm -O3 # -fopenmp
RM = rm -f

OBJECTS = fparser/fparser.o event.o model.o lex.yy.o parser.tab.o tauleapavail.o

BASIC_CLASSES = model.o event.o realization.o paramset.o realization_factory.o
REALIZATIONS = nextreaction.o firstreaction.o eulerleap.o
RANDOM = rng.o xoroshiro128plus.o

CLASSES = $(BASIC_CLASSES) $(REALIZATIONS) $(RANDOM)

all: stoched.exe testparser.exe testevent.exe testmodel.exe testsimulate.exe


simulate.exe: simulate.o
	$(CXX) $(OMPCXXFLAGS) -o $@ $^ -I $(CXXFLAGS)

testparser.exe: testparser.o $(OBJECTS)
	$(CXX) $(OMPCXXFLAGS) $^ -ll -o $@

testevent.exe: event.o testevent.o fparser/fparser.o
	$(CXX) $(OMPCXXFLAGS) $^ -o $@  

testmodel.exe: model.o event.o testmodel.o fparser/fparser.o
	$(CXX) $(OMPCXXFLAGS) $^ -o $@

testmodel: model.o event.o testmodel.o fparser/fparser.o
	$(CXX) $(OMPCXXFLAGS) $^ -o $@

testsimulate.exe: testsimulate.o $(CLASSES) fparser/fparser.o
	$(CXX) $(OMPCXXFLAGS) $^ -o $@

stoched.exe: stoched.o $(OBJECTS) $(CLASSES)
	$(CXX) $(OMPCXXFLAGS) $^ -ll -o $@

stoched_serial.exe: stoched.o $(OBJECTS) $(CLASSES)
	$(CXX) $(CXXFLAGS) $^ -ll -o $@

fparser/fparser.exe: fparser/example2.o fparser/fparser.o
	$(CXX) $^ -o $@

xoroshiro_test.exe: xoroshiro_test.o $(RANDOM)
	$(CXX) $^ -o $@

# use flex and bison to generate parser source code
parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: parser.l parser.tab.h
	flex parser.l

# dependency rules
fparser/fparser.o: fparser/fparser.cc
	$(CXX) -c $^ -o $@

#fparser/example2.o: fparser/example2.cc fparser/fparser.o
#	$(CXX) $^ -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $<

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
