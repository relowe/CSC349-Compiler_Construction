# vi:ts=8:sw=8:wm=0:ai:noexpandtab
	.data
	.equ	BUFSIZE, 12
	.lcomm	buffer, BUFSIZE
	.equ	INBUFSIZE, 80
	.lcomm	inbuf, INBUFSIZE + 1
inbuf_ptr: .int	inbuf
true:	.ascii	"        true"
false:	.ascii	"       false"
nl:	.byte	'\n'
ov_msg:	.ascii	"Runtime Error:  Integer Overflow\n"
	.equ	OVM_LEN, . - ov_msg
d0_msg: .ascii	"Runtime Error:  Division by Zero\n"
	.equ	D0M_LEN, . - d0_msg
ix_msg: .ascii	"Runtime Error:  Array Index Out of Range\n"
	.equ	IXM_LEN, . - ix_msg
eof_msg: .ascii	"Runtime Error:  Unexpected End-of-file\n"
	.equ	EOFM_LEN, . - eof_msg
bc_msg: .ascii	"Runtime Error:  Invalid Character in Input\n"
	.equ	BCM_LEN, . - bc_msg

	.text
.globl	print_dec
#
# print decimal value in EAX (12 char field)
# all registers preserved
#
print_dec:
	pushal				# save all regs
	movl	$BUFSIZE, %ecx		# no. of chars in buffer
	movl	$10, %ebx		# constant for division
	xorl	%esi, %esi		# assume value is non-negative
	testl	%eax, %eax		# is assumption true
	jge	signok			#   yes --> all is okay
	not	%esi			#   no --> adjust sign flag
	neg	%eax			# 	and work with abs. value
signok:	
loop:	xorl	%edx, %edx		# need 64-bit divisor
	divl	%ebx			# divide by 10
	addb	$'0', %dl		# convert remainder to ASCII
	movb	%dl, buffer-1(%ecx)	#   and put it in buffer
	decl	%ecx			# count down chars
	testl	%eax, %eax		# is accumulator zero?
	jnz	loop			#   no --> process next digit
# put sign in buffer, if necessary
	testl	%esi, %esi		# was number negative?
	jz	padlp			#   no --> pad with spaces
	movb	$'-', buffer-1(%ecx)	#   yes --> put neg. sign in buffer
	decl	%ecx
# pad buffer with blanks
padlp:	movb	$' ', buffer-1(%ecx)	# put space in buffer
	loop	padlp			# again if necessary
do_bufprint:
	movl	$BUFSIZE, %edx		# no. of chars
	movl	$buffer, %ecx		# addr of stuff to print
do_print:
	movl	$1, %ebx		# stdout
	movl	$4, %eax		# "print"
	pushl	%edx			# push regs for BSD/MacOS compatibility
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	int	$0x80
	addl	$16,%esp		# remove BSD/MacOS args
	popal				# restore all regs
	ret	

.globl	print_newline
#
# print newline
# all registers preserved
#
print_newline:
	pushal				# save all regs
	movl	$1, %edx		# 1 char to print
	movl	$nl, %ecx		# nl holds newline
	jmp do_print

.globl	print_bool
#
# print boolean value in EAX (12 char field)
# all registers preserved
#
print_bool:
	pushal				# save all regs
	cld
	movl	$false, %esi		# assume false
	testl	%eax, %eax		# is acc. zero (false)?
	jz	boolok			#   yes --> we're okay
	movl	$true, %esi		#   no --> adjust assumption
boolok:	movl	$BUFSIZE, %ecx		# move appropriate string 		
	movl	$buffer, %edi		# to buffer
	rep movsb

	jmp do_bufprint

.globl	read_dec
#
# read decimal value into EAX
# saves all registers except EAX
#    (save current buffer pos in inbuf_ptr)
#
# use EBX for running result
# use ECX for sign (0 = '+', -1 = '-')
#
read_dec:
	pushl	%ebx
	pushl	%ecx
	pushl	%esi
	xorl	%eax, %eax		# clear EAX (3 hi-bytes in particular)
	xorl	%ebx, %ebx		# start with zero result
	xorl	%ecx, %ecx		# assume +
	movl	inbuf_ptr, %esi		# look at current pos in input buffer
	cld				# (string dir = forward)
	call	skip_blanks
# check for sign or initial digit
	cmpb	$'+', %al		# is first char a + sign
	je	first_digit		#   yes --> skip it & get first digit
	cmpb	$'-', %al		# is first char a - sign
	jne	check_digit		#   no --> check for digit
	notl	%ecx			# note that result is negative
first_digit:
	call	next_char		# get first digit
# make sure first char is a digit
check_digit:
	subb	$'0', %al		# is first char a digit?
	jl	bcerr			#   no --> bad char error
	cmpb	$9, %al			# is first char a digit?
	jg	bcerr			#   no --> bad char error
# current char is a digit
rd_loop:
	imull	$10, %ebx		# EBX := 10 * EBX
	jo	overflow
	addl	%eax, %ebx		#	      + input char
	jno	rd_no_ovf
	cmpl	$0x80000000,%ebx	# -2147483648 is not really
	jne	overflow		# overflow
	testl	%ecx,%ecx		# but +2147483648 is
	jz	overflow
rd_no_ovf:	
	call	next_char		# get next char
	subb	$'0', %al		# is first char a digit?
	jl	rd_done			#   no --> we're done
	cmpb	$9, %al			# is first char a digit?
	jng	rd_loop			#   yes --> process it
# we're done processing digits; return the value
rd_done:
	decl	%esi			# put non-digit back in input stream
	test	%ecx, %ecx		# negative number?
	jz	rd_pos			#   no --> just return it
	neg	%ebx			#   yes --> negate it
rd_pos:
	movl	%ebx, %eax		# get return value into EAX
	movl	%esi, inbuf_ptr		# save input buffer pointer
	popl	%esi
	popl	%ecx
	popl	%ebx
	ret

.globl	read_bool
#
# read boolean value into EAX
# saves all registers except EAX
#    (save current buffer pos in inbuf_ptr)
#
read_bool:
	pushl	%esi
	movl	inbuf_ptr, %esi		# look at current pos in input buffer
	cld
	call	skip_blanks
	orb	$'a'-'A', %al		# AL := tolower(AL)
	cmpb	$'t', %al		# looking at "t"?
	je	rb_true			#   yes --> look for "rue"
	cmpb	$'f', %al		# looking at "f"?
	jne	bcerr			#   no --> neither "true" or "false"!
# process "false"; look for "alse"
	call	next_lc_char
	cmpb	$'a', %al		# do we have an 'a'?
	jne	bcerr			#   no --> input isn't "false"!
	call	next_lc_char
	cmpb	$'l', %al		# do we have an 'l'?
	jne	bcerr			#   no --> input isn't "false"!
	call	next_lc_char
	cmpb	$'s', %al		# do we have an 's'?
	jne	bcerr			#   no --> input isn't "false"!
	call	next_lc_char
	cmpb	$'e', %al		# do we have an 'e'?
	jne	bcerr			#   no --> input isn't "false"!
	xorl	%eax, %eax		# "false" returns 0
	jmp	rb_done
# process "true"; look for "rue"
rb_true:
	call	next_lc_char
	cmpb	$'r', %al		# do we have an 'r'?
	jne	bcerr			#   no --> input isn't "true"!
	call	next_lc_char
	cmpb	$'u', %al		# do we have an 'u'?
	jne	bcerr			#   no --> input isn't "true"!
	call	next_lc_char
	cmpb	$'e', %al		# do we have an 'e'?
	jne	bcerr			#   no --> input isn't "true"!
	movl	$1, %eax		# "true" returns 1
rb_done:
	movl	%esi, inbuf_ptr		# save input buffer pointer
	popl	%esi
	ret

#
# skip blanks in input buffer (spaces, tabs & newlines)
# 
# expects ESI to point to next char
# returns first non-blank char in AL
#
skip_blanks:
	call	next_char		# get next char
	cmpb	$' ', %al		# space?
	jz	skip_blanks		#   yes --> try again
	cmpb	$'\t', %al		# tab?
	jz	skip_blanks		#   yes --> try again
	cmpb	$'\n', %al		# newline?
	jz	skip_blanks		#   yes --> try again
	ret				#   no --> return with non-blank in AL

#
# get next input character; full input buffer as necessary
# Error if EOF encountered
# 
# expects %ESI to point to current buffer position, dir=0
# returns next char in AL, updates ESI
next_char:
	lodsb				# get current char
	test	%al,%al			# end-of-buffer?
	jz	nc_fill_buff		#   no --> fill buffer & try again
# have valid char; return with it
	ret
# fill input buffer and try again; error if EOF
# mark end of data with zero char, but keep registers intact
nc_fill_buff:
	pusha
	movl	$3, %eax		# read
	xorl	%ebx, %ebx		# from stdin
	movl	$inbuf, %ecx		# into inbuf
	movl	$INBUFSIZE, %edx	# (at most INBUFSIZE chars)
	pushl	%edx			# push regs for BSD/MacOS compatibility
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	int	$0x80
	addl	$16,%esp		# remove BSD/MacOS args
	test	%eax,%eax		# end-of-file (0 chars read)?
	jz	eoferr			#   yes --> early EOF error
	movb	$0, inbuf(%eax)		# mark end of buffer with zero byte
	popa
	movl	$inbuf, %esi		# reset buffer pointer
	jmp next_char
#
# print error message on EOF
# and exit with error code
#
eoferr:
	movl	$EOFM_LEN, %edx		# no. of chars
	movl	$eof_msg, %ecx		# addr of stuff to print
	jmp	err_print

#
# get the next character and convert it to lowercase
#
next_lc_char:
	call	next_char		# get char into AL
	orb	$'a'-'A', %al		# AL := tolower(AL)
	ret

.globl	overflow
#
# print error message on integer overflow
# and exit with error code
#
overflow:
	movl	$OVM_LEN, %edx		# no. of chars
	movl	$ov_msg, %ecx		# addr of stuff to print
err_print:
	movl	$2, %ebx		# stderr
	movl	$4, %eax		# "print"
	pushl	%edx			# push regs for BSD/MacOS compatibility
	pushl	%ecx
	pushl	%ebx
	pushl	%eax
	int	$0x80
	addl	$16,%esp		# remove BSD/MacOS args
err_exit:
	movl    $1,%eax
	movl    %eax,%ebx
	pushl	%ebx
	pushl	%eax
	int	$0x80

.globl	divide0
#
# print error message on divide-by-zero
# and exit with error code
#
divide0:
	movl	$D0M_LEN, %edx		# no. of chars
	movl	$d0_msg, %ecx		# addr of stuff to print
	jmp	err_print

.globl	out_of_range
#
# print error message on index out-of-range
# and exit with error code
#
out_of_range:
	movl	$IXM_LEN, %edx		# no. of chars
	movl	$ix_msg, %ecx		# addr of stuff to print
	jmp	err_print

#
# print error message for bad character in input
# and exit with error code
#
bcerr:
	movl	$BCM_LEN, %edx		# no. of chars
	movl	$bc_msg, %ecx		# addr of stuff to print
	jmp	err_print
