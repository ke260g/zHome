#ifndef SHUDU_H
#define SHUDU_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Std_Type 0
#define X_Type 1
#define Color_Type 2
#define Hyper_Type 3
#define Percent 4

extern int src_maze[9][9];
extern int maze[9][9];
extern const int type;
int is_pos_val(const int y, const int x, int value);
void sol_maze(const int y, const int x);
void display_maze(void);
#endif
