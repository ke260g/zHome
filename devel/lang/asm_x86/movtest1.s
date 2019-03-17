# movtest1.s -An example of moving data from memory to a register
.section .data
  value:
  	.int 1
.section .text
.globl _start
	_start:
		nop
		movl value, 		%ecx
		pushl $1
		movl 4(%esp),		%eax
		movl $0,			%ebx
		int $0x80
