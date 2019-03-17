#include "shudu.h"

int is_pos_val(const int y, const int x, int value) {
#if VERBOSE
    display_maze();
    /* to check the process, recomplie with macro define VERBOSE */
#endif
    int tmp = 0;

    for(; tmp < 9; tmp++) {
        /* check whether in the same vertical line */
        if(maze[y][tmp] == value)
            return 0;
    }

    for(tmp = 0; tmp < 9; tmp++)
        /* check whether in the same horisontal line */
        if(maze[tmp][x] == value)
            return 0;

    int i_x = 0;
    int i_y = 0;

    for(; i_x < 3; i_x++)
        for(i_y = 0; i_y < 3; i_y++)
            if(maze[3*(y/3) + i_y][3*(x/3) + i_x] == value)
                return 0;
    /* check whether in the small maze is valid */

    if(type == X_Type)
        /* a special shudu */
        if((x+y) == 8) {
            for(i_y = 0, i_x = 8; i_y < 9; i_y++, i_x--)
                if(maze[i_y][i_x] == value)
                    return 0;
        } else if(x == y) {
            for(i_x = 0; i_x < 9; i_x++)
                if(maze[i_x][i_x] == value)
                    return 0;
        }

    if(type == Color_Type)
        /* a special kind of shudu */
        for(i_x = 0; i_x < 7; i_x = i_x + 3)
            for(i_y = 0; i_y < 7; i_y = i_y + 3)
                if(maze[y%3 + i_y][x%3 + i_x] == value)
                    return 0;


    if(type == Hyper_Type)
        /* a special kind of shudu */
        /* 4 hyper small maze have been embeded in */
        if((x != 0) && (x != 4) && (x != 8) \
                && (y != 0) && (y != 4) && (y != 8))
            if(((x - 1)/3 == 0) || ((x + 1)/3 == 2) \
                    || ((y - 1)/3 == 0) || ((y + 1)/3 == 2))
                for(i_y = 1; i_y < 4; i_y++)
                    for(i_x = 1; i_x < 4; i_x++)
                        if(maze[(y/4)*4+i_y][(x/4)*4+i_x] == value)
                            return 0;
    if(type == Percent)
        /*a special kind of shudu */
        /*half hyper and half X == Percent */
        if((x+y) == 8) {
            for(i_y = 0, i_x = 8; i_y < 9; i_y++, i_x--)
                if(maze[i_y][i_x] == value)
                    return 0;
        } else if((x != 0) && (x != 4) && (x != 8) \
                && (y != 0) && (y != 4) && (y != 8))
            if((((x - 1)/3 == 0) && ((y - 1)/3 == 0)) \
                    || (((x + 1)/3 == 2) && ((y + 1)/3 == 2)))
                for(i_y = 1; i_y < 4; i_y++)
                    for(i_x = 1; i_x < 4; i_x++)
                        if(maze[(y/4)*4+i_y][(x/4)*4+i_x] == value)
                            return 0;



    return 1;
}

void sol_maze(const int y, const int x) {
    if(src_maze[y][x] != 0) {
        /* the position  is non-zero at the beginning*/
        if(x != 8)
            sol_maze(y, x+1);
        else if(y != 8)
            sol_maze(y+1, 0);
        else{
            /* x == 8, y == 8, reach the end,
             * the answer is solved out, exit */
            display_maze();
            printf("problem has been solved out\n");
            exit(EXIT_SUCCESS);
        }
    }
    else{
        int test_value = 1;
        for(; test_value < 10; test_value++) {
            if(is_pos_val(y, x, test_value)) {
                maze[y][x] = test_value; /* give the value to the maze */
                if((x == 8) && (y == 8)) {
                    /* when answer is solved out, exit */
                    display_maze();
                    printf("problem has been solved out\n");
                    exit(EXIT_SUCCESS);
                }
                if(x != 8)
                    sol_maze(y, x+1);
                else if(y != 8)
                    sol_maze(y+1, 0);
            }
        }
        maze[y][x] = 0; /* can't reach the answer, return to zero */
    }
}

void display_maze(void) {
    /*
       printf("+-------+-------+-------+\n")
       | 1 2 3 | 4 5 6 | 7 8 9 |\n"
       printf("+-------+-------+-------+\n")
     */

    int x = 0;
    int y = 0;

    for(; y < 9; y++) {
        x = 0;
        if((y == 0) || (y == 3) || (y == 6))
            printf("+-------+-------+-------+\n");
        for(; x < 9; x++) {
            if((x == 0) || (x == 3) || (x == 6))
                printf("| ");
            printf("%d ", maze[y][x]);
        }
        printf("|\n");
    }
    printf("+-------+-------+-------+\n");
    printf("*************************\n\n");
}
