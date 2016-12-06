# -----------------------------------------------------------------------------
# Kevin Griffin, Caleb Peckham, Julienne LaChance, Dylan Morris
# 11/29/16, APC 524, Final Project
# Makefile
# -----------------------------------------------------------------------------
CXX = g++
MPICXX = mpicc
CXXFLAGS = -g -Wall -lm -O3
OMPCXXFLAGS = -g -Wall -lm -O3 -fopenmp
RM = rm
LIBS = ../lib/eigen

all: testparser
#simulate

simulate: simulate.o
	$(CXX) -o $@ $^ -I $(LIBS) $(CXXFLAGS)

simulate.o: simulate.cc
	$(CXX) $^ -c $(CXXFLAGS)

#testparser: testparser.o parser.o
#	$(CXX) -o $@ $^ -I $(LIBS) $(CXXFLAGS)

#testparser.o: testparser.cc
#	$(CXX) $^ -c $(CXXFLAGS)

#parser.o: parser.cc parser.h
#	$(CXX) $^ -c $(CXXFLAGS)

# use flex and bison to generate parser source code
testparser: testparser.cc lex.yy.c parser.tab.c parser.tab.h
	g++ testparser.cc lex.yy.c parser.tab.c -ll -o testparser

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: parser.l parser.tab.h
	flex parser.l

# clean up object code and executables
clean:
	$(RM) simulate
	$(RM) *.o

# clean up emacs temp files
clobber: clean
	rm -f *~ \#*\#
