#include <stdio.h>
#define MAX_ROW 5
#define MAX_COL 5

struct point {
	int row, col;
} stack[512];					//struct point stack[512];
int top = 0;

void push(struct point tmp) {
	stack[top++] = tmp;
}

struct point pop(void) {
	return stack[--top];
}

int is_top_empty(void) {
	return top == 0;
}

int maze[MAX_ROW][MAX_COL] = {
/* initalize the maze, then thier value will be rewrited */
	{0, 1, 0, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0},
	{0, 0, 0, 1, 0},
};

void print_maze(void) {
	int i, j;
	for(i = 0; i < MAX_ROW; i++) {
		for(j = 0; j < MAX_ROW; j++)
			printf("%d", maze[i][j]);
		putchar('\n');
	}
	printf("*******************\n");
}

struct point predecessor[MAX_ROW][MAX_COL] = {	/* { predecessor[row][col].row, predecessor[row][col].col} */
	{{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1,
			-1}},
	{{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1,
			-1}},
	{{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1,
			-1}},
	{{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1,
			-1}},
	{{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1,
			-1}},
};

void visit(int row, int col,
	struct point tmp_predecessor) {
	maze[row][col] = 2;
	predecessor[row][col] = tmp_predecessor;
	struct point visit_point = { row, col };
	push(visit_point);
}

int main(void) {
#if 1							/* initilaize the start */
	struct point position = { 0, 0 };	//positon.row == 0,  position.rol == 0
	maze[position.row][position.col] = 2;
	push(position);
#endif

#if 1							/* move up, down, left, right */
	while(!is_top_empty()) {
		position = pop();
		if(position.row == MAX_ROW - 1	/* end maze[MAX_ROW - 1][MAX_COL - 1] */
			&& position.col == MAX_COL - 1)
			break;
		if(position.col + 1 < MAX_COL	/* right */
			&& maze[position.row][position.col +
				1] == 0)
			visit(position.row, position.col + 1,
				position);
		if(position.row + 1 < MAX_ROW	/* down */
			&& maze[position.row +
				1][position.col] == 0)
			visit(position.row + 1, position.col,
				position);
		if(position.col - 1 >= 0	/* left */
			&& maze[position.row][position.col -
				1] == 0)
			visit(position.row, position.col - 1,
				position);
		if(position.row - 1 >= 0	/* up   */
			&& maze[position.row -
				1][position.col] == 0)
			visit(position.row - 1, position.col,
				position);
		print_maze();
	}
#endif

#if 0
	/* print the history path with predecessor end to start */
	if(position.row == MAX_ROW - 1
		&& position.col == MAX_COL - 1) {
		printf("(%d, %d)\n", position.row,
			position.col);
		while(predecessor[position.row][position.
				col].col != -1) {
			position = predecessor[position.row]
				[position.col];
			printf("(%d, %d)\n", position.row,
				position.col);
		}
	} else
		printf("No Path\n");
#endif

#if 1
	/* printf the history path with predecessor start to end */
	int track = 0;
	struct point hisarray[MAX_ROW * MAX_COL];
	if(position.row == MAX_ROW - 1
		&& position.col == MAX_COL - 1)
		hisarray[track] = position;
	while(predecessor[position.row][position.col].
		col != -1) {
		position =
			predecessor[position.row][position.
			col];
		track++;
		hisarray[track] = position;
	}
	for(; track >= 0; track--)
		printf("(%d, %d)\n", hisarray[track].row,
			hisarray[track].col);

#endif
	return 0;
}

#if 0							/* maze output */
21000 21010 00000 01110 00010 *******************
	21000 21010 20000 01110 00010
	*******************
	21000 21010 22000 21110 00010
	*******************
	21000 21010 22000 21110 20010
	*******************
	21000 21010 22000 21110 22010
	*******************
	21000 21010 22000 21110 22210
	*******************
	21000 21010 22000 21110 22210
	*******************
	21000 21010 22200 21110 22210
	*******************
	21000 21210 22220 21110 22210
	*******************
	21200 21210 22220 21110 22210
	*******************
	21220 21210 22220 21110 22210
	*******************
	21222 21210 22220 21110 22210
	*******************
	21222 21212 22220 21110 22210
	*******************
	21222 21212 22222 21110 22210
	*******************
	21222 21212 22222 21112 22210
	*******************
	21222 21212 22222 21112 22212
	******************* (4, 4)
	(3, 4)
	(2, 4)
	(1, 4)
	(0, 4)
	(0, 3)
	(0, 2)
	(1, 2)
	(2, 2)
	(2, 1)
	(2, 0)
	(1, 0)
	(0, 0)
#endif
