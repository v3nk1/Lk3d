	.file	"test.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	$1, -4(%ebp)
	#pushl	-4(%ebp)    without dis statement the printing value is 0,becz its not in stack,because we are placing with respect to ebp.
			
	movl	$.LC0, (%esp)
	call	printf
	leave
	ret
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
