# calculate 2**3+5**2 with a function method
	.section .data

	.section .text

	.globl _start

_start:
############### first call power function #######################
	pushl $3					# argument_2
	pushl $2					# argument_1

	call power
	addl $8, %esp				# stack pointer move back
	pushl %eax					# store the first result
##################################################################


############### second call power function #######################
	pushl $2					# argument_2
	pushl $5					# argument_1 
	
	call power		
	addl $8, %esp

	popl %ebx					# pop the first result as it exists in %ebx
##################################################################

	addl %eax, %ebx				# ebx = ebx + eax
	movl $1, %eax				# sys call, exit
	int $0x80

.type power, @function
power:
	pushl %ebp					# store the base pointer( power() address)
	movl %esp, %ebp				# base pointer = stack pointer
	subl $4, %esp				# give space for local var 

	movl 8(%ebp), %eax			# ebx = argument_1 底数
	movl 12(%ebp), %ecx 		# ecx = argument_2 指数

	movl %ebx, -4(%ebp)			# store current result
	
power_loop_start:
	cmpl $1, %eax
	je end_power
	movl -4(%ebp), %ebx			# store current result to %eax
	imull %ebx, %eax			# multiplication current result and 底数
	movl %eax, -4(%ebp)			# store current result

	decl %ecx					# 指数递减
	jmp power_loop_start		# 递减后继续运算
	
end_power:
	movl -4(%ebp), %eax			# %eax = return value
	movl %ebp, %esp				# reload the stack pointer
	popl %ebp					# reload the base pointer
	ret
