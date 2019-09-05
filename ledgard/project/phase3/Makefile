CPPFLAGS = -Wall
phase3-driver: main.o parser.o unimplemented.o precompiled/lexer.o
	g++ -o phase3-driver main.o parser.o unimplemented.o precompiled/lexer.o

parser.o:		lexer.h parser.h parse-tree.h
unimplemented.o:	parse-tree.h
main.o:			lexer.h parser.h parse-tree.h

test:			phase3-driver test.led
	@./phase3-driver < test.led 2>&1 | diff - test.out	\
		&& echo "Simple Test 'test.led' Passed"
