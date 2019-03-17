#include "com_func.h"
#include <time.h>

void display_array(const int array[], const int amount) {
/* input the pointer to the head-address of an array
 * and the amount of members in such array,
 * then display the value of each member.
 */
	int counter = 0;
	for(; counter < amount; counter++) {
		printf("%d\t", array[counter]);
		if( ((counter+1) % 10) != 0) ;
		else
			putchar('\n');
	}
	putchar('\n');
	printf("******************************\n");
}

void init_array(int *const array, const int amount) {
/* input the pointer to the head-address of an array
 * and the amount of members in such array,
 * initial each member's value by positive random integer
 */
	int counter = 0;
	srand((unsigned)time(NULL));
	for(; counter < amount; counter++) {
		array[counter] = rand()/1000000;
	}
}

void swap_two(int *const left, int *const right) {
	int temp = *left;
	*left = *right;
	*right = temp;
}
