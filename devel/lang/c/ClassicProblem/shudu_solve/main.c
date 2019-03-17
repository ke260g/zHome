#include "shudu.h"

int src_maze[9][9];
/* used for record the source version of the maze */

int main(void){
	if((type != Std_Type) \
	   && (type != X_Type) \
	   && (type != Color_Type) \
	   && (type != Hyper_Type) \
	   && (type != Percent)) {
		fprintf(stderr, "Wrong tpye numder of shudu\n"
		        "Check out the maze.c\n");
		exit(EXIT_FAILURE);
	}
	memcpy(src_maze, maze, 9*9*sizeof(int));
	printf("%d\n", is_pos_val(5, 6, 7));
	printf("The source one is follow.\n"
	       "You have to ensure it is correct\n");
	display_maze();
	sol_maze(0,0);
	return 0;
}
