phase1-driver: main.o lexer.o
	g++ -o phase1-driver main.o lexer.o

lexer.o:	lexer.h
main.o:		lexer.h

test:		phase1-driver test.led
	@./phase1-driver < test.led 2>&1 | diff - test.out	\
		&& echo "Simple Test 'test.led' Passed"
