#include <stdio.h>

#define Q 8

static int queen_result[Q];
static long amount;                             /* the amount of results */

void display_result(void);
int pos_is_valid(const int y_axis, const int x_axis);
void queen_loop(const int y_axis);

int main(void){
	queen_loop(0);
	printf("The amount of results is %ld\n", amount);
	return 0;
}

void display_result(void){
	int y_axis = 0;
	int x_axis = 0;
	for(; y_axis < Q; y_axis++) {
		for(x_axis = 0; x_axis < queen_result[y_axis]; x_axis++)
			printf("- ");
		printf("! ");
		for(x_axis++; x_axis < Q; x_axis++)
			printf("- ");
		putchar('\n');
	}
	printf("*********************************************************\n");
}

int pos_is_valid(const int y_axis, const int x_axis){
	int test_y = 0;
	for(; test_y < y_axis; test_y++)
		if((queen_result[test_y] == x_axis) || ((queen_result[test_y] - test_y) == (x_axis - y_axis)) || ((queen_result[test_y] + test_y) == (x_axis + y_axis)))
			return 0;
	return 1;
}

void queen_loop(const int y_axis){
	int test_x = 0;
	for(; test_x < Q; test_x++) {
#if A
		if(pos_is_valid(y_axis, test_x) != 1);
		else{
			queen_result[y_axis] = test_x;
			if(y_axis != (Q-1)) {/* not the final result */
				queen_loop(y_axis+1);
				queen_result[y_axis] = 0;
			}
			else{ /* reach the fianl result */
				amount++;
				display_result();
				queen_result[y_axis] = 0;
			}
		}
#endif

#if B
		if(pos_is_valid(y_axis, test_x)) {
			queen_result[y_axis] = test_x;
			if(y_axis == (Q-1)) {
				amount++;
				display_result();
				queen_result[y_axis] = 0;
				return;
			}
			queen_loop(y_axis+1);
			queen_result[y_axis] = 0;
		}
#endif

	}
}
