CPPFLAGS = -Wall
phase6-driver: main.o codegen.o precompiled/lexer.o			\
		precompiled/parser.o precompiled/symtab.o		\
		precompiled/typecheck.o
	g++ -o phase6-driver main.o codegen.o precompiled/lexer.o	\
		precompiled/parser.o precompiled/symtab.o		\
		precompiled/typecheck.o

codegen.o:	parse-tree.h
main.o:		lexer.h parser.h parse-tree.h

ledgard-lib.o:	ledgard-lib.s
	as32 -o ledgard-lib.o ledgard-lib.s

test1:	test1.led phase6-driver ledgard-lib.o
	./phase6-driver < test1.led > test1.s
	as32 -o test1.o test1.s
	ld32 -o test1 test1.o ledgard-lib.o
test2:	test2.led phase6-driver ledgard-lib.o
	./phase6-driver < test2.led > test2.s
	as32 -o test2.o test2.s
	ld32 -o test2 test2.o ledgard-lib.o
test3:	test3.led phase6-driver ledgard-lib.o
	./phase6-driver < test3.led > test3.s
	as32 -o test3.o test3.s
	ld32 -o test3 test3.o ledgard-lib.o
test4:	test4.led phase6-driver ledgard-lib.o
	./phase6-driver < test4.led > test4.s
	sed -i '/lcomm.*B/s/lcomm.*/equ B,A/' test4.s
	as32 -o test4.o test4.s
	ld32 -o test4 test4.o ledgard-lib.o
easter:	easter.led phase6-driver ledgard-lib.o
	./phase6-driver < easter.led > easter.s
	as32 -o easter.o easter.s
	ld32 -o easter easter.o ledgard-lib.o

test:		test1 test2 test3 test4 easter
	@for i in test[1-4];					\
	do 							\
		./$$i 2>&1 | diff - $$i.out			\
			&& echo "Simple Test '$$i' Passed";	\
	done;							\
	for i in 2013 12345 1609 1734 7517 1954 1585 1583 1598;	\
	do							\
		echo $$i | ./easter;				\
	done | diff - easter.out && echo "Easter Test Passed"
