#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

struct point {
	int row, col, predecessor;
} queue[512];					// predecessor is for write down the order number
int head = 0, tail = 0;

static void enqueue(struct point tmp) {
	queue[tail++] = tmp;
};

static struct point dequeue(void) {
	/* return the head of the queue */
	/* then the head point to the next */
	return queue[head++];
};

int is_queue_empty(void) {
	return head == tail;
};

int maze[MAX_ROW][MAX_COL] = {
	{0, 1, 0, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0},
	{0, 0, 0, 1, 0},
};

void print_maze(void) {
	for(int i = 0; i < MAX_ROW; i++) {
		for(int j = 0; j < MAX_COL; j++)
			printf("%d ", maze[i][j]);
		putchar('\n');
	}
	printf("***************\n");
};

void visit_maze(int row, int col) {
	struct point visit_point =
		{ row, col, head - 1 };
	maze[row][col] = 2;
	enqueue(visit_point);
}

int main(void) {
#if 1							/* start configure */
	struct point position = { 0, 0, -1 };
	maze[position.row][position.col] = 2;
	enqueue(position);
#endif

#if 1							/* move up down right down */
	while(!is_queue_empty()) {
		position = dequeue();
		if(position.row == MAX_ROW - 1
			&& position.col == MAX_COL - 1
			/* whether reach the goal */ )
			break;
		if(position.col + 1 < MAX_ROW && maze[position.row][position.col + 1] == 0)	/* move right */
			visit_maze(position.row,
				position.col + 1);
		if(position.col - 1 >= 0 && maze[position.row][position.col - 1] == 0)	/* move left */
			visit_maze(position.row,
				position.col - 1);
		if(position.row + 1 < MAX_ROW && maze[position.row + 1][position.col] == 0)	/* move down */
			visit_maze(position.row + 1,
				position.col);
		if(position.row - 1 >= 0 && maze[position.row - 1][position.col] == 0)	/* move up */
			visit_maze(position.row - 1,
				position.col);
		print_maze();
	}
#endif

#if 0							/* print history path  1 */
	if(position.row == MAX_ROW - 1 && position.col == MAX_COL - 1) {	/* reach the goal */
		printf("(%d, %d)\n", position.row,
			position.col);
		while(position.predecessor != -1) {
			position =
				queue[position.predecessor];
			printf("(%d, %d)\n", position.row,
				position.col);
		}
	} else
		printf("NO PATH!\n");
#endif
#if 1							/* print history path 2 */
	int track = 0;
	struct point tmpposition[MAX_ROW * MAX_COL];
	if(position.row == MAX_ROW - 1 && position.col == MAX_COL - 1)	/* reach the goal */
		tmpposition[track] = position;
	while(position.predecessor != -1) {
		position = queue[position.predecessor];
		track++;
		tmpposition[track] = position;
	}
	for(; track >= 0; track--)
		printf("(%d, %d)\n",
			tmpposition[track].row,
			tmpposition[track].col);
#endif
	return 0;
}
