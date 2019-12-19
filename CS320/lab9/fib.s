	.globl	Main_main
Main_main:
	pushl	%ebp
	movl	%esp,%ebp
	subl	$16,%esp
	movl	$0,%eax
	movl	%eax,-4(%ebp)
	movl	$1,%eax
	movl	%eax,-8(%ebp)
	movl	$0,%eax
	movl	%eax,-12(%ebp)
	jmp	l1
l0:
	movl	-4(%ebp),%eax
	pushl	%eax
	call	print
	addl	$4,%esp
	movl	$0,%eax
	movl	-12(%ebp),%ebx
	cmpl	%eax,%ebx
	jz	l2
	movl	-8(%ebp),%eax
	movl	%eax,-4(%ebp)
	jmp	l3
l2:
l3:
	movl	-4(%ebp),%eax
	movl	%eax,-16(%ebp)
	movl	-8(%ebp),%eax
	movl	%eax,-4(%ebp)
	movl	-8(%ebp),%eax
	movl	-16(%ebp),%ebx
	addl	%ebx,%eax
	movl	%eax,-8(%ebp)
	movl	$1,%eax
	movl	-12(%ebp),%ebx
	addl	%ebx,%eax
	movl	%eax,-12(%ebp)
l1:
	movl	$10,%eax
	movl	-12(%ebp),%ebx
	cmpl	%eax,%ebx
	jl	l0
	movl	%ebp,%esp
	popl	%ebp
	ret
