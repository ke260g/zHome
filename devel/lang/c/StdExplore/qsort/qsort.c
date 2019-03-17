#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define N_INT_ARRAY 9

enum {CMP_INT_ORDER_BIG, CMP_INT_ORDER_LITTLE};

static int cmp_int(const void *left, const void *right, void *order) {
    if(order  == (void *)CMP_INT_ORDER_LITTLE)
        return (*(int *)left - *(int *)right);
    else /* CMP_INT_ORDER_BIG, from big to little */
        return -(*(int *)left - *(int *)right);
}

int main(int argc, char **argv){
    int a[N_INT_ARRAY], i;

    srand((unsigned)time(NULL));
    for ( i = 0; i < N_INT_ARRAY; i++ ) {
        a[i] = rand()/999999;
    }

    qsort_r(a, N_INT_ARRAY, sizeof(int), cmp_int, CMP_INT_ORDER_LITTLE);
    printf("===============================================\n");
    for ( i = 0; i < N_INT_ARRAY; i++ ) {
        printf("%d\t", a[i]);
        if((i + 1) % 10 == 0)
            putchar('\n');
    }

    putchar('\n');
    return EXIT_SUCCESS;
}
