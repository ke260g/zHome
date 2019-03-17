#ifndef COM_FUNC_H
#define COM_FUNC_H
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
extern signed num_memb;
void display_array(const int array[], const int num);
void init_array(int *const array, const int num);
void swap_two(int *const left, int *const right);

/* sort method func */

void bubble_sort(int *const target, int const head_suffix, int const tail_suffix);
void select_sort(int *const target, int const head_suffix, int const tail_suffix);
void quick_sort(int *const target, int const head_suffix, int const tail_suffix);
void insert_sort(int *const target, int const head_suffix, int const tail_suffix);
void merge_sort(int *const target, int const head_suffix, int const tail_suffix);
void heap_sort(int *const target, int const head_suffix, int const tail_suffix);
#endif
