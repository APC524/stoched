# -----------------------------------------------------------------------------
# Kevin Griffin, Caleb Peckham, Julienne LaChance, Dylan Morris
# 11/29/16, APC 524, Final Project
# Makefile
# -----------------------------------------------------------------------------
#burger:
#	g++ -Wall -I ./eigen923 burger.cpp -o burger
CXX = g++
MPICXX = mpicc
CXXFLAGS = -g -Wall -lm -O3
OMPCXXFLAGS = -g -Wall -lm -O3 -fopenmp
RM = rm
LIBS = ./eigen

all: simulate

simulate: simulate.o
	$(CXX) -o $@ $^ -I $(LIBS) $(CXXFLAGS)

simulate.o: src/simulate.cc
	$(CXX) $^ -c $(CXXFLAGS)

# clean up object code and executables
clean:
	$(RM) simulate
	$(RM) *.o

# clean up emacs temp files
clobber: clean
	rm -f *~ \#*\#
