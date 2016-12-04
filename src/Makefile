parser: lex.yy.c parser.tab.c parser.tab.h
	g++ parser.tab.c lex.yy.c -ll -o parser

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: parser.l parser.tab.h
	flex parser.l
