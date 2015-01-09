	.file	"mat_mul.c"
	.section	.rodata
.LC0:
	.string	"%d\t"
	.text
	.globl	print_mat
	.type	print_mat, @function
print_mat:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -56(%rbp)
	movl	%esi, -60(%rbp)
	movl	%edx, -64(%rbp)
	movl	-64(%rbp), %ebx
	movslq	%ebx, %rax
	subq	$1, %rax
	movq	%rax, -32(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -24(%rbp)
	movl	$0, -40(%rbp)
	jmp	.L2
.L5:
	movl	$0, -36(%rbp)
	jmp	.L3
.L4:
	movl	-40(%rbp), %eax
	movslq	%eax, %rdx
	movslq	%ebx, %rax
	imulq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movl	-36(%rbp), %eax
	cltq
	movl	(%rdx,%rax,4), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -36(%rbp)
.L3:
	movl	-36(%rbp), %eax
	cmpl	-64(%rbp), %eax
	jl	.L4
	movl	$10, %edi
	call	putchar
	addl	$1, -40(%rbp)
.L2:
	movl	-40(%rbp), %eax
	cmpl	-60(%rbp), %eax
	jl	.L5
	movl	$10, %edi
	call	putchar
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	print_mat, .-print_mat
	.section	.rodata
.LC1:
	.string	"enter d %drow ele's:\n"
.LC2:
	.string	" %d"
	.text
	.globl	read_mat
	.type	read_mat, @function
read_mat:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -56(%rbp)
	movl	%esi, -60(%rbp)
	movl	%edx, -64(%rbp)
	movl	-64(%rbp), %ebx
	movslq	%ebx, %rax
	subq	$1, %rax
	movq	%rax, -32(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, -24(%rbp)
	movl	$0, -40(%rbp)
	jmp	.L7
.L10:
	movl	-40(%rbp), %eax
	addl	$1, %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$0, -36(%rbp)
	jmp	.L8
.L9:
	movl	-40(%rbp), %eax
	movslq	%eax, %rdx
	movslq	%ebx, %rax
	imulq	%rdx, %rax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movl	-36(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	%rdx, %rax
	movq	%rax, %rsi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	addl	$1, -36(%rbp)
.L8:
	movl	-36(%rbp), %eax
	cmpl	-64(%rbp), %eax
	jl	.L9
	addl	$1, -40(%rbp)
.L7:
	movl	-40(%rbp), %eax
	cmpl	-60(%rbp), %eax
	jl	.L10
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	read_mat, .-read_mat
	.globl	mat_mul
	.type	mat_mul, @function
mat_mul:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movl	%edx, -84(%rbp)
	movl	%ecx, -88(%rbp)
	movl	%r8d, -92(%rbp)
	movl	%r9d, -96(%rbp)
	movl	-88(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -48(%rbp)
	movq	-72(%rbp), %rdx
	movq	%rdx, -40(%rbp)
	movl	-96(%rbp), %edx
	movslq	%edx, %rcx
	subq	$1, %rcx
	movq	%rcx, -32(%rbp)
	movq	-80(%rbp), %rcx
	movq	%rcx, -24(%rbp)
	movl	-96(%rbp), %ecx
	movslq	%ecx, %rsi
	subq	$1, %rsi
	movq	%rsi, -16(%rbp)
	movl	$0, -64(%rbp)
	jmp	.L12
.L17:
	movl	$0, -60(%rbp)
	jmp	.L13
.L16:
	movl	$0, -52(%rbp)
	movl	$0, -56(%rbp)
	jmp	.L14
.L15:
	movl	-64(%rbp), %esi
	movslq	%esi, %rdi
	movslq	%eax, %rsi
	imulq	%rdi, %rsi
	leaq	0(,%rsi,4), %rdi
	movq	-40(%rbp), %rsi
	addq	%rsi, %rdi
	movl	-56(%rbp), %esi
	movslq	%esi, %rsi
	movl	(%rdi,%rsi,4), %edi
	movl	-56(%rbp), %esi
	movslq	%esi, %r8
	movslq	%edx, %rsi
	imulq	%r8, %rsi
	leaq	0(,%rsi,4), %r8
	movq	-24(%rbp), %rsi
	addq	%rsi, %r8
	movl	-60(%rbp), %esi
	movslq	%esi, %rsi
	movl	(%r8,%rsi,4), %esi
	imull	%edi, %esi
	addl	%esi, -52(%rbp)
	addl	$1, -56(%rbp)
.L14:
	movl	-56(%rbp), %esi
	cmpl	-88(%rbp), %esi
	jl	.L15
	movl	-64(%rbp), %esi
	movslq	%esi, %rdi
	movslq	%ecx, %rsi
	imulq	%rdi, %rsi
	leaq	0(,%rsi,4), %rdi
	movq	-8(%rbp), %rsi
	leaq	(%rdi,%rsi), %r8
	movl	-60(%rbp), %esi
	movslq	%esi, %rsi
	movl	-52(%rbp), %edi
	movl	%edi, (%r8,%rsi,4)
	addl	$1, -60(%rbp)
.L13:
	movl	-60(%rbp), %esi
	cmpl	-96(%rbp), %esi
	jl	.L16
	addl	$1, -64(%rbp)
.L12:
	movl	-64(%rbp), %esi
	cmpl	-84(%rbp), %esi
	jl	.L17
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	mat_mul, .-mat_mul
	.section	.rodata
.LC3:
	.string	"invalid sizes"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$-128, %rsp
	movl	$3, -120(%rbp)
	movl	$3, -116(%rbp)
	movl	$3, -112(%rbp)
	movl	$3, -108(%rbp)
	movl	-116(%rbp), %eax
	cmpl	-112(%rbp), %eax
	jne	.L20
	movl	$1, -96(%rbp)
	movl	$0, -92(%rbp)
	movl	$0, -88(%rbp)
	movl	$0, -84(%rbp)
	movl	$1, -80(%rbp)
	movl	$0, -76(%rbp)
	movl	$0, -72(%rbp)
	movl	$0, -68(%rbp)
	movl	$1, -64(%rbp)
	movl	$1, -48(%rbp)
	movl	$2, -44(%rbp)
	movl	$3, -40(%rbp)
	movl	$4, -36(%rbp)
	movl	$5, -32(%rbp)
	movl	$6, -28(%rbp)
	movl	$7, -24(%rbp)
	movl	$8, -20(%rbp)
	movl	$9, -16(%rbp)
	movl	-108(%rbp), %r8d
	movl	-112(%rbp), %edi
	movl	-116(%rbp), %ecx
	movl	-120(%rbp), %edx
	leaq	-48(%rbp), %rsi
	leaq	-96(%rbp), %rax
	movl	%r8d, %r9d
	movl	%edi, %r8d
	movq	%rax, %rdi
	call	mat_mul
	movq	%rax, -104(%rbp)
	movl	-108(%rbp), %edx
	movl	-120(%rbp), %ecx
	movq	-104(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	print_mat
	jmp	.L22
.L20:
	movl	$.LC3, %edi
	call	puts
.L22:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
