CPPFLAGS = -Wall
phase5-driver: main.o typecheck.o unimplemented.o		\
		precompiled/lexer.o precompiled/parser.o precompiled/symtab.o
	g++ -o phase5-driver main.o typecheck.o unimplemented.o	\
		precompiled/lexer.o precompiled/parser.o precompiled/symtab.o

typecheck.o unimplemented.o:	parse-tree.h
main.o:		lexer.h parser.h parse-tree.h

test:		phase5-driver test.led
	@./phase5-driver < test.led 2>&1 | diff - test.out	\
		&& echo "Simple Test 'test.led' Passed"
