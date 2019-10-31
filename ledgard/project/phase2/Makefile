CPPFLAGS = -Wall

phase2-driver: main.o parser.o precompiled/lexer.o
	g++ -no-pie -o phase2-driver main.o parser.o precompiled/lexer.o

parser.o:	lexer.h parser.h
main.o:		lexer.h parser.h
test:		phase2-driver test1.led test2.led test3.led test4.led	\
		test5.led test6.led test7.led
	@for i in test*.led;						\
	do 								\
	    ./phase2-driver < $$i 2>&1 | diff - `basename $$i .led`.out	\
	    	&& echo "Simple Test '$$i' Passed";			\
	done
