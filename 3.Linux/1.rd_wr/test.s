	.file	"test.c"
	.section	.rodata
.LC0:
	.string	"./test.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	movl	$2, 4(%esp)
	movl	$.LC0, (%esp)
	call	open
	movl	%eax, 28(%esp)
	leave
	ret
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
