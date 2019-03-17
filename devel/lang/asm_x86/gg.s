	.section .data
	
	.section .text
	.global _start
_start:
	movl $1, %ebx
	movl $1, %ebx
	movl $1, %ebx
	movl $1, %ebx
	movl $1, %ebx
	movl $1, %ebx
	movl $1, %ebx
	movl $1, %ebx
	movl $1, %ebx
	movl $1, %eax  # UNIX sys call
	movl $1, %ebx  # %ebx is the value returned to sys

	int $0x80
