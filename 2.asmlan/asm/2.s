# In this scenario we allocate packed stack contain enough local variables, and trying to access
# all variables w/o overwrite.
# In this whenever u want to print, dynamically we are allocating using pushl,
# after completion we are deallocating using popl or subl instructions.

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
	subl	$12, %esp
	movl	$10, -12(%ebp)
	movl	$20, -8(%ebp)
	movl	-12(%ebp), %eax
	movl	-8(%ebp), %edx
	addl	%edx, %eax

	# Printing c value
	movl	%eax, -4(%ebp)
#	movl	-4(%ebp), %eax
	pushl	%eax		# automatically pushes to the top of the stack and 
				# increments stack ptr(esp) by 4bytes.
	pushl	$.LC0
	call	printf

	# Subtracting additionally incremented stack
	subl 	$8,(%esp)	# or popl 2 times

	# Printing a value
	movl	-12(%ebp),%eax
	pushl	%eax
	pushl	$.LC0
	call	printf
	# Subtracting additionally incremented stack
	subl 	$8,(%esp)	# or popl 2 times

	# Printing b value
	movl	-8(%ebp),%eax
	pushl	%eax
	pushl	$.LC0
	call	printf
	# Subtracting additionally incremented stack
	subl 	$8,(%esp)	# or popl 2 times

	
	leave
	ret
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
