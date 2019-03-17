#include "com_func.h"

void bubble_sort(int *const target, int const head_suffix, int const tail_suffix) {
    signed current_test = head_suffix;
    signed src_index = head_suffix;
    for (; src_index <= tail_suffix; src_index++) {
        for (current_test = src_index+1; current_test <= tail_suffix; current_test++) {
            if (target[src_index] > target[current_test]) {
                swap_two(&target[current_test], &target[src_index]);
#if VERBOSE
                display_array(target, num_memb);
#endif
            }
        }
    }
}

void insert_sort(int *const target, int const head_suffix, int const tail_suffix) {
    signed current_test = head_suffix + 1;
    signed position = 0;
    signed key_index = 0;

    for(; current_test <= tail_suffix; current_test++) {
        position = current_test;
        key_index = current_test - 1;
        for(; key_index >= 0; key_index--)
            if ( target[key_index] > target[position] ) {
                swap_two(&target[key_index], &target[position]);
                position = key_index;
            }
    }
}

void select_sort(int *const target, int const head_suffix, int const tail_suffix) {
    signed current_test = head_suffix;
    signed src_index = head_suffix;
    signed position = src_index;
    for (; src_index <= tail_suffix; src_index++) {
        position = src_index;
        for (current_test = src_index+1; current_test <= tail_suffix; current_test++)
            if (target[position] >= target[current_test])
                position = current_test;
        swap_two(&target[position], &target[src_index]);
#if VERBOSE
        display_array(target, num_memb);
#endif

    }
}

void quick_sort(int *const target,
        int const head_suffix,
        int const tail_suffix) {

    if(tail_suffix <= head_suffix)
        return;

    int suffix_low = head_suffix;
    int suffix_high = tail_suffix;
    int pivot = target[suffix_low];

    while(suffix_low < suffix_high) {
        while((pivot <= target[suffix_high]) && (suffix_low < suffix_high))
            suffix_high--;

        target[suffix_low] = target[suffix_high];

        while((pivot >= target[suffix_low]) && (suffix_low < suffix_high))
            suffix_low++;
        target[suffix_high] = target[suffix_low];
        target[suffix_low] = pivot;
    }

    quick_sort(target, head_suffix, suffix_low - 1);
    quick_sort(target, suffix_high + 1, tail_suffix);
}

void merge_sort(int *const target, int const head_suffix, int const tail_suffix){
    static int merge_sort_tmp_arr[999999999]; /* use for merge_sort */
    if(head_suffix == tail_suffix)
        return;
    if((tail_suffix - head_suffix) == 1) {
        if(target[head_suffix] > target[tail_suffix])
            swap_two(&target[head_suffix], &target[tail_suffix]);
        return;
    }

    int index_mid = (tail_suffix + head_suffix)/2;         /* middle index of input array */
    merge_sort(target, head_suffix, index_mid);
    merge_sort(target, index_mid+1, tail_suffix);

    int index_pre = head_suffix;
    int index_nex = index_mid+1;
    int index_new = 0;          /* new array index */

    for(; (index_pre <= index_mid) && (index_nex <= tail_suffix); index_new++) {
        if(target[index_pre] < target[index_nex]) {
            merge_sort_tmp_arr[index_new] = target[index_pre];
            index_pre++;
        }
        else{
            merge_sort_tmp_arr[index_new] = target[index_nex];
            index_nex++;
        }
    }

    for(; index_pre <= index_mid; index_new++, index_pre++)
        merge_sort_tmp_arr[index_new] = target[index_pre];
    for(; index_nex <= tail_suffix; index_new++, index_nex++)
        merge_sort_tmp_arr[index_new] = target[index_nex];
    for(index_pre = head_suffix, index_new = 0; index_pre <= tail_suffix; index_pre++, index_new++)
        target[index_pre] = merge_sort_tmp_arr[index_new];
}

static void heap_sort_adjust(int *const target, int const head_suffix, int const tail_suffix) {
    /*
     * in the head, or bin-tree,
     * if first is 0 (in C, array suffix usually is),
     * left_child == father*2 + 1,
     * right_child == father*2 +2,
     * father == (child-1)/2
     * father == left_child/2
     * next_father ==  right_child/2
     */
    int child = tail_suffix;
    if(head_suffix == tail_suffix)
        return;

    for(; child > head_suffix; child--) /* bottom-to-top loop */
        if(target[(child-1) / 2] < target[child]) /* father < child */
            swap_two(&target[(child-1) / 2], &target[child]);

    int father = head_suffix;
    child = father*2 + 1;
    for(; child <= tail_suffix; child++) {
        if(target[father] < target[child]) /* father < child */
            swap_two(&target[father], &target[child]);
        father = child/2;
    }
}

void heap_sort(int *const target, int const head_suffix, int const tail_suffix) {
    heap_sort_adjust(target, head_suffix, tail_suffix);
    int bottom = tail_suffix;
    for(; bottom > head_suffix; ) {
        swap_two(&target[head_suffix], &target[bottom]);
        bottom--;
        heap_sort_adjust(target, head_suffix, bottom);
    }
}
