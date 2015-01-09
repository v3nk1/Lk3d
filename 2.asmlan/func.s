	.file	"func.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	sum
	.type	sum, @function
sum:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp
	#subl	$24, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	addl	%edx, %eax
	#movl 	$10,%eax
	pushl	%eax
	#movl	%eax, 4(%esp)
	#movl	$.LC0, (%esp)
	call	printf
	leave
	ret
.LFE0:
	.size	sum, .-sum
	.globl	main
	.type	main, @function
main:
.LFB1:
	pushl	%ebp
	movl	%esp, %ebp
	#subl	$32, %esp
	movl	$1, 20(%esp)
	movl	$2, 24(%esp)
	#movl	24(%esp), %eax
	#movl	%eax, 4(%esp)
	pushl 	24(%esp)
	#movl	20(%esp), %eax
	#movl	%eax, (%esp)
	pushl	20(%esp)
	call	sum
	movl	%eax, 28(%esp)
	leave
	ret
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
