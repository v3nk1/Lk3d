	.file	"2.c"
	.section	.rodata
.LC0:
	.string	"sum:%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushl	%ebp    
	movl	%esp, %ebp
	subl	$12, %esp	#$32, %esp
	movl	$100,-12(%ebp) #20(%esp)
	movl	$200, -8(%ebp)#24(%esp)
	movl	-12(%esp), %eax
	movl	-8(%esp), %edx
	addl	%edx, %eax
	movl	%eax, -4(%ebp)
	#movl	28(%esp), %eax
	#movl	%eax, 4(%esp)
	pushl	%eax
	movl	$.LC0, (%esp)
	call	printf  #think in printf function 2 popl shud be there..
	leave
	ret
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
