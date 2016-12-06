# -----------------------------------------------------------------------------
# Kevin Griffin, Caleb Peckham, Julienne LaChance, Dylan Morris
# 11/29/16, APC 524, Final Project
# Makefile
# -----------------------------------------------------------------------------
CXX = g++
MPICXX = mpicc
CXXFLAGS = -g -Wall -lm -O3
OMPCXXFLAGS = -g -Wall -lm -O3 -fopenmp
RM = rm -f
LIBS = ../lib/eigen
OBJECTS = fparser/fparser.o event.o model.o testparser.o lex.yy.o parser.tab.o

all: testparser
#simulate

simulate.exe: simulate.o
	$(CXX) -o $@ $^ -I $(LIBS) $(CXXFLAGS)

testparser: $(OBJECTS)
	g++ $(OBJECTS) -ll -o $@

# use flex and bison to generate parser source code
parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: parser.l parser.tab.h
	flex parser.l

# dependency rules
%.o: %.cc
	g++ -c $< 
%.o: %.c
	g++ -c $<

# clean up object code and executables
clean:
	$(RM) *.exe
	$(RM) *.o

# clean up emacs temp files
clobber: clean
	$(RM) *~ \#*\#
