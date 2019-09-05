.section .bss
	.lcomm	G,4
	.lcomm	C,4
	.lcomm	X,4
	.lcomm	Z,4
	.lcomm	D,4
	.lcomm	E,4
	.lcomm	N,4
	.lcomm	DN,4
	.lcomm	MONTH,4
	.lcomm	DAY,4
	.lcomm	YEAR,4

.section .text
.globl  _start
_start:
	xorl    %esi,%esi
	leal    YEAR(%esi),%eax
	pushl   %eax
	call    read_dec
	popl    %ebx
	movl    %eax,(%ebx)
	xorl    %esi,%esi
	leal    G(%esi),%eax
	pushl   %eax
	xorl    %esi,%esi
	leal    YEAR(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $19
	xorl    %esi,%esi
	leal    YEAR(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $19
	popl    %ebx
	test    %ebx,%ebx
	jz      divide0
	popl    %eax
	cltd
	idivl   %ebx
	pushl   %eax
	popl    %ebx
	popl    %eax
	imull   %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %ebx
	popl    %eax
	subl    %ebx,%eax
	jo      overflow
	pushl   %eax
	pushl   $1
	popl    %ebx
	popl    %eax
	addl    %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	xorl    %esi,%esi
	leal    C(%esi),%eax
	pushl   %eax
	xorl    %esi,%esi
	leal    YEAR(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $100
	popl    %ebx
	test    %ebx,%ebx
	jz      divide0
	popl    %eax
	cltd
	idivl   %ebx
	pushl   %eax
	pushl   $1
	popl    %ebx
	popl    %eax
	addl    %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	xorl    %esi,%esi
	leal    X(%esi),%eax
	pushl   %eax
	pushl   $3
	xorl    %esi,%esi
	leal    C(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	popl    %ebx
	popl    %eax
	imull   %ebx,%eax
	jo      overflow
	pushl   %eax
	pushl   $4
	popl    %ebx
	test    %ebx,%ebx
	jz      divide0
	popl    %eax
	cltd
	idivl   %ebx
	pushl   %eax
	pushl   $12
	popl    %ebx
	popl    %eax
	subl    %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	xorl    %esi,%esi
	leal    Z(%esi),%eax
	pushl   %eax
	pushl   $8
	xorl    %esi,%esi
	leal    C(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	popl    %ebx
	popl    %eax
	imull   %ebx,%eax
	jo      overflow
	pushl   %eax
	pushl   $5
	popl    %ebx
	popl    %eax
	addl    %ebx,%eax
	jo      overflow
	pushl   %eax
	pushl   $25
	popl    %ebx
	test    %ebx,%ebx
	jz      divide0
	popl    %eax
	cltd
	idivl   %ebx
	pushl   %eax
	pushl   $5
	popl    %ebx
	popl    %eax
	subl    %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	xorl    %esi,%esi
	leal    D(%esi),%eax
	pushl   %eax
	pushl   $5
	xorl    %esi,%esi
	leal    YEAR(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	popl    %ebx
	popl    %eax
	imull   %ebx,%eax
	jo      overflow
	pushl   %eax
	pushl   $4
	popl    %ebx
	test    %ebx,%ebx
	jz      divide0
	popl    %eax
	cltd
	idivl   %ebx
	pushl   %eax
	xorl    %esi,%esi
	leal    X(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	popl    %ebx
	popl    %eax
	subl    %ebx,%eax
	jo      overflow
	pushl   %eax
	pushl   $10
	popl    %ebx
	popl    %eax
	subl    %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	xorl    %esi,%esi
	leal    E(%esi),%eax
	pushl   %eax
	pushl   $11
	xorl    %esi,%esi
	leal    G(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	popl    %ebx
	popl    %eax
	imull   %ebx,%eax
	jo      overflow
	pushl   %eax
	pushl   $20
	popl    %ebx
	popl    %eax
	addl    %ebx,%eax
	jo      overflow
	pushl   %eax
	xorl    %esi,%esi
	leal    Z(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	popl    %ebx
	popl    %eax
	addl    %ebx,%eax
	jo      overflow
	pushl   %eax
	xorl    %esi,%esi
	leal    X(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	popl    %ebx
	popl    %eax
	subl    %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	xorl    %esi,%esi
	leal    E(%esi),%eax
	pushl   %eax
	xorl    %esi,%esi
	leal    E(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $30
	xorl    %esi,%esi
	leal    E(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $30
	popl    %ebx
	test    %ebx,%ebx
	jz      divide0
	popl    %eax
	cltd
	idivl   %ebx
	pushl   %eax
	popl    %ebx
	popl    %eax
	imull   %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %ebx
	popl    %eax
	subl    %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	xorl    %esi,%esi
	leal    E(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $25
	popl    %ebx
	popl    %eax
	xorl    %ecx,%ecx
	cmpl    %ebx,%eax
	jne     1f
	incl    %ecx
1:	pushl   %ecx
	movl    (%esp),%eax
	testl   %eax,%eax
	jz      label4
	popl    %eax
	xorl    %esi,%esi
	leal    G(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $11
	popl    %ebx
	popl    %eax
	xorl    %ecx,%ecx
	cmpl    %ebx,%eax
	jng     1f
	incl    %ecx
1:	pushl   %ecx
label4:
	movl    (%esp),%eax
	testl   %eax,%eax
	jnz     label3
	popl    %eax
	xorl    %esi,%esi
	leal    E(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $24
	popl    %ebx
	popl    %eax
	xorl    %ecx,%ecx
	cmpl    %ebx,%eax
	jne     1f
	incl    %ecx
1:	pushl   %ecx
label3:
	popl    %eax
	test    %eax,%eax
	jz      label1
	xorl    %esi,%esi
	leal    E(%esi),%eax
	pushl   %eax
	xorl    %esi,%esi
	leal    E(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $1
	popl    %ebx
	popl    %eax
	addl    %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	jmp     label2
label1:
label2:
	xorl    %esi,%esi
	leal    N(%esi),%eax
	pushl   %eax
	pushl   $44
	xorl    %esi,%esi
	leal    E(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	popl    %ebx
	popl    %eax
	subl    %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	xorl    %esi,%esi
	leal    N(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $21
	popl    %ebx
	popl    %eax
	xorl    %ecx,%ecx
	cmpl    %ebx,%eax
	jnl     1f
	incl    %ecx
1:	pushl   %ecx
	popl    %eax
	test    %eax,%eax
	jz      label5
	xorl    %esi,%esi
	leal    N(%esi),%eax
	pushl   %eax
	xorl    %esi,%esi
	leal    N(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $30
	popl    %ebx
	popl    %eax
	addl    %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	jmp     label6
label5:
label6:
	xorl    %esi,%esi
	leal    DN(%esi),%eax
	pushl   %eax
	xorl    %esi,%esi
	leal    D(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	xorl    %esi,%esi
	leal    N(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	popl    %ebx
	popl    %eax
	addl    %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	xorl    %esi,%esi
	leal    DN(%esi),%eax
	pushl   %eax
	xorl    %esi,%esi
	leal    DN(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $7
	xorl    %esi,%esi
	leal    DN(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $7
	popl    %ebx
	test    %ebx,%ebx
	jz      divide0
	popl    %eax
	cltd
	idivl   %ebx
	pushl   %eax
	popl    %ebx
	popl    %eax
	imull   %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %ebx
	popl    %eax
	subl    %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	xorl    %esi,%esi
	leal    N(%esi),%eax
	pushl   %eax
	xorl    %esi,%esi
	leal    N(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $7
	popl    %ebx
	popl    %eax
	addl    %ebx,%eax
	jo      overflow
	pushl   %eax
	xorl    %esi,%esi
	leal    DN(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	popl    %ebx
	popl    %eax
	subl    %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	xorl    %esi,%esi
	leal    N(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $31
	popl    %ebx
	popl    %eax
	xorl    %ecx,%ecx
	cmpl    %ebx,%eax
	jng     1f
	incl    %ecx
1:	pushl   %ecx
	popl    %eax
	test    %eax,%eax
	jz      label7
	xorl    %esi,%esi
	leal    MONTH(%esi),%eax
	pushl   %eax
	pushl   $4
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	xorl    %esi,%esi
	leal    DAY(%esi),%eax
	pushl   %eax
	xorl    %esi,%esi
	leal    N(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	pushl   $31
	popl    %ebx
	popl    %eax
	subl    %ebx,%eax
	jo      overflow
	pushl   %eax
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	jmp     label8
label7:
	xorl    %esi,%esi
	leal    MONTH(%esi),%eax
	pushl   %eax
	pushl   $3
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
	xorl    %esi,%esi
	leal    DAY(%esi),%eax
	pushl   %eax
	xorl    %esi,%esi
	leal    N(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	popl    %eax
	popl    %ebx
	movl    %eax,(%ebx)
label8:
	xorl    %esi,%esi
	leal    DAY(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	popl    %eax
	call    print_dec
	xorl    %esi,%esi
	leal    MONTH(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	popl    %eax
	call    print_dec
	xorl    %esi,%esi
	leal    YEAR(%esi),%eax
	pushl   %eax
	popl    %eax
	pushl   (%eax)
	popl    %eax
	call    print_dec
	call    print_newline

	xorl    %ebx,%ebx
	movl    $1,%eax
	int     $0x80
