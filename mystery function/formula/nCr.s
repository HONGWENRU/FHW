.globl	nCr
nCr:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	movl	$0, -12(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	Factorial
	movl	%eax, %ebx
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	Factorial
	movl	%eax, %esi
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, (%esp)
	call	Factorial
	imull	%eax, %esi
	movl	%esi, %ecx
	movl	%ebx, %eax
	cltd
	idivl	%ecx
	jo	overflow1
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
overflow1:
	movl	$0, %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret

        
.globl	Factorial
Factorial:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$1, -4(%ebp)
	movl	$1, -8(%ebp)
	jmp	loop
overflow:
	movl	$0, %eax
	movl	-8(%ebp), %eax
	movl	-4(%ebp), %eax
	leave
	ret
multiplication:
	movl	-4(%ebp), %eax
	imull	-8(%ebp), %eax
	jo 	overflow
	movl	%eax, -4(%ebp)
	addl	$1, -8(%ebp)


loop:
	movl	-8(%ebp), %eax
	cmpl	8(%ebp), %eax
	jle	multiplication
	movl	-4(%ebp), %eax
	leave
	ret
