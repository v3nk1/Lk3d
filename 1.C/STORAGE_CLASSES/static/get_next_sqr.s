	.file	"get_next_sqr.c"
	.text
	.globl	get_next_sqr
	.type	get_next_sqr, @function
get_next_sqr:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	cmpl	$0, 8(%ebp)
	jle	.L2
	movl	8(%ebp), %eax
	movl	%eax, pre_val.1686
	movl	8(%ebp), %eax
	imull	8(%ebp), %eax
	jmp	.L3
.L2:
	movl	pre_val.1686, %eax
	addl	$1, %eax
	movl	%eax, pre_val.1686
	movl	pre_val.1686, %edx
	movl	pre_val.1686, %eax
	imull	%edx, %eax
.L3:
	popl	%ebp
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE0:
	.size	get_next_sqr, .-get_next_sqr
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$16, %esp
	movl	$3, (%esp)
	call	get_next_sqr
	movl	$.LC0, %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	printf
	movl	$0, (%esp)
	call	get_next_sqr
	movl	$.LC0, %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	printf
	movl	$10, (%esp)
	call	get_next_sqr
	movl	$.LC0, %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	printf
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.local	pre_val.1686
	.comm	pre_val.1686,4,4
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
