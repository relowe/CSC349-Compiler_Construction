CPPFLAGS = -Wall
phase4-driver: main.o symtab.o unimplemented.o precompiled/lexer.o	\
					       precompiled/parser.o
	g++ -o phase4-driver main.o symtab.o unimplemented.o		\
		precompiled/lexer.o precompiled/parser.o

symtab.o unimplemented.o:	parse-tree.h
main.o:		lexer.h parser.h parse-tree.h

test:		phase4-driver test.led
	@./phase4-driver < test.led 2>&1 | diff - test.out		\
		&& echo "Simple Test 'test.led' Passed"
