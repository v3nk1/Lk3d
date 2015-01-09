# Compile with cc -m32 2.s
# Here it will overwrite a,b bcoz of less stack allocated.

	.file	"test.c"
	.section	.rodata
.LC0:
	.string	"sum: %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp		# allocate extra 8 bytes for printf purpose. So 12+8=20
					# If u dont allocate separately the a,b locations will be
					# overwritten with, c, $.LC0
	movl	$10, -12(%ebp)
	movl	$20, -8(%ebp)
	movl	-12(%ebp), %eax
	movl	-8(%ebp), %edx
	addl	%edx, %eax

	# Printing c value
	movl	%eax, -4(%ebp)
#	movl	-4(%ebp), %eax
	movl	%eax, 4(%esp)	
	movl	$.LC0, (%esp)
	call	printf

	# Printing a value.	Here it will print junk values, bcoz while printing c values, we are 
	#			overriding the a,b locations. bcoz of less stack.
	movl	-12(%ebp),%eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	
	# Printing b value.	Here it will print junk values, bcoz while printing c values, we are 
	#			overriding the a,b locations. bcoz of less stack.
	movl	-8(%ebp),%eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	
	leave
	ret
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
