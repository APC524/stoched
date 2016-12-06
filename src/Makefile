CXXFLAGS = -g -Wall
MPICC = mpic++
targets = xorshiro_test

parser: lex.yy.c parser.tab.c parser.tab.h
	g++ parser.tab.c lex.yy.c -ll -o parser

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: parser.l parser.tab.h
	flex parser.l

xoroshiro_test: xoroshiro_test.o xoroshiro128plus.o
	$(CXX) -o $@ $^

clean:
	$(RM) *.o
	$(RM) .depend
	$(RM) $(targets)
