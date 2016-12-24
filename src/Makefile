# -----------------------------------------------------------------------------
# Kevin Griffin, Caleb Peckham, Julienne LaChance, Dylan Morris
# 11/29/16, APC 524, Final Project
# Makefile
# -----------------------------------------------------------------------------
CXX = g++-6
MPICXX = mpicc
CXXFLAGS = -g -Wall -lm -O3
OMPCXXFLAGS = -g -Wall -lm -O3 -fopenmp
RM = rm -f
LIBS = ../lib/eigen
OBJECTS = fparser/fparser.o event.o model.o testparser.o lex.yy.o parser.tab.o
CLASSES = model.o event.o xoroshiro128plus.o realization.o paramset.o

#all: testparser.exe fparser/fparser.exe testevent.exe testmodel.exe
all: testparser.exe testevent.exe testmodel.exe testsimulate.exe


#simulate

simulate.exe: simulate.o
	$(CXX) -o $@ $^ -I $(LIBS) $(CXXFLAGS)

testparser.exe: $(OBJECTS)
	$(CXX) $(OBJECTS) -ll -o $@

testevent.exe: event.o testevent.o fparser/fparser.o
	$(CXX) $^ -o $@  

testmodel.exe: model.o event.o testmodel.o fparser/fparser.o
	$(CXX) $^ -o $@

testmodel: model.o event.o testmodel.o fparser/fparser.o
	$(CXX) $^ -o $@

#testsimulate: testsimulate.o $(CLASSES) fparser/fparser.o
#	$(CXX) $^ -o $@

testsimulate.exe: testsimulate.o $(CLASSES) fparser/fparser.o
	$(CXX) $^ -o $@

#fparser/fparser.exe: fparser/example2.o fparser/fparser.o
#	$(CXX) $^ -o $@  

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

#realization.o: realization.cc model.o event.o
#	$(CXX) -c $^ -o $@

%.o: %.cc
	g++-6 -c $< 
#	g++ -std=c++11 $<
	
%.o: %.c
	g++-6 -c $<

# clean up object code and executables
clean:
	$(RM) *.exe
	$(RM) *.o

# clean up emacs temp files
clobber: clean
	$(RM) *~ \#*\#
