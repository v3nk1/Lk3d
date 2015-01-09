	.file	"2.c"
	.section	.rodata
.LC0:
	.string	"x= %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	movl	$10, 28(%esp)	#10
	addl	$1, 28(%esp)	#11
	movl	28(%esp), %eax	#11
	leal	1(%eax), %edx	#11
	movl	%edx, 28(%esp)	#11
	movl	28(%esp), %edx	#11
	addl	%edx, %eax	#22
	addl	$1, 28(%esp)	#12
	addl	%eax, 28(%esp)	#34
	movl	28(%esp), %eax	#34
	movl	%eax, 4(%esp)	#34
	movl	$.LC0, (%esp)
	call	printf
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.8.1-10ubuntu8) 4.8.1"
	.section	.note.GNU-stack,"",@progbits
