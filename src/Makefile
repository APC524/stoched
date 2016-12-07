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

all: testparser.exe fparser/fparser.exe testevent.exe testmodel.exe
#simulate

simulate.exe: simulate.o
	$(CXX) -o $@ $^ -I $(LIBS) $(CXXFLAGS)

testparser.exe: $(OBJECTS)
	$(CXX) $(OBJECTS) -ll -o $@ $(CXXFLAGS)

testevent.exe: event.o testevent.o fparser/fparser.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

testmodel.exe: model.o event.o testmodel.o fparser/fparser.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

fparser/fparser.exe: fparser/example2.o fparser/fparser.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

# use flex and bison to generate parser source code
parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: parser.l parser.tab.h
	flex parser.l

# dependency rules
fparser/fparser.o: fparser/fparser.cc
	$(CXX) $^ -c -o fparser/fparser.o $(CXXFLAGS)

#fparser/example2.o: fparser/example2.cc
#	$(CXX) $^ -c -o fparser/fparser.o

%.o: %.cc
	$(CXX) -c $< $(CXXFLAGS)
%.o: %.c
	$(CXX) -c $< $(CXXFLAGS)

# clean up object code and executables
clean:
	$(RM) *.exe
	$(RM) *.o

# clean up emacs temp files
clobber: clean
	$(RM) *~ \#*\#
