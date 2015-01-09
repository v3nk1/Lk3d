	.file	"arr.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%ebx
	subl	$48, %esp
	leal	-48(%ebp), %ebx
	movl	$0, %eax
	movl	$10, %edx
	movl	%ebx, %edi
	movl	%edx, %ecx
	rep stosl
	movl	$1, -48(%ebp)
	movl	$3, -44(%ebp)
	movl	$4, -40(%ebp)
	movl	$5, -36(%ebp)
	movl	$6, -32(%ebp)
	movl	$0, %eax
	addl	$48, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
