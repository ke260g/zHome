# return the maximum number in the data_items	
# %edi save the position for the table
# %ebx save current maximum in the table
# %eax save the member who is being tested

	.section .data
data_items:							# an var, you can redefine the name 
	.long 	3, 67, 34, 222, 45, 75, 54, 34, 44, 33, 22, 11, 66, 0

 	.section .text
	.globl _start
_start:
	movl $0, %edi
	movl data_items(,%edi,4), %eax 	# load the first item
	movl %eax, %ebx 				# since %eax is the first and 
									# only item, it's biggest

loop:							# a function name, you can define another name	
									# the method to implement "loop" is more like recursion

	cmpl $14, %edi			
	je exit
	incl %edi
	movl data_items(,%edi,4), %eax
	cmpl %ebx, %eax
	jle loop

	movl %eax, %ebx

	jmp loop

exit:	
	movl $1, %eax
	int $0x80

