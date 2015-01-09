	.file	"8.c"
	.globl	o1
	.data
	.align 32
	.type	o1, @object
	.size	o1, 400
o1:
	.long	1
	.long	2
	.long	3
	.zero	388
	.globl	o2
	.align 32
	.type	o2, @object
	.size	o2, 400
o2:
	.long	1
	.long	2
	.long	3
	.zero	388
	.comm	o3,400,32
	.text
	.globl	add_obj
	.type	add_obj, @function
add_obj:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$416, %esp
	movl	$0, -404(%ebp)
	jmp	.L2
.L3:
	movl	-404(%ebp), %eax
	movl	8(%ebp,%eax,4), %edx
	movl	-404(%ebp), %eax
	movl	408(%ebp,%eax,4), %eax
	addl	%eax, %edx
	movl	-404(%ebp), %eax
	movl	%edx, -400(%ebp,%eax,4)
	movl	-404(%ebp), %eax
	movl	-400(%ebp,%eax,4), %ecx
	movl	808(%ebp), %eax
	movl	-404(%ebp), %edx
	movl	%ecx, (%eax,%edx,4)
	addl	$1, -404(%ebp)
.L2:
	movl	-404(%ebp), %eax
	cmpl	$99, %eax
	jbe	.L3
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	add_obj, .-add_obj
	.section	.rodata
.LC0:
	.string	"%d %d %d\n"
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
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	andl	$-16, %esp
	subl	$816, %esp
	.cfi_offset 7, -12
	.cfi_offset 6, -16
	.cfi_offset 3, -20
	movl	$o3, 800(%esp)
	leal	400(%esp), %edx
	movl	$o2, %ebx
	movl	$100, %eax
	movl	%edx, %edi
	movl	%ebx, %esi
	movl	%eax, %ecx
	rep movsl
	movl	%esp, %edx
	movl	$o1, %ebx
	movl	$100, %eax
	movl	%edx, %edi
	movl	%ebx, %esi
	movl	%eax, %ecx
	rep movsl
	call	add_obj
	movl	o3+8, %ecx
	movl	o3+4, %edx
	movl	o3, %eax
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	leal	-12(%ebp), %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
