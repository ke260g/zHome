/* quick_sort */
#include<stdlib.h>
#include<string.h>

#include"sort.h"

/* compare init */
static int compare_int(const void *int1, const void *int2) {
    /* compare 2 integers (used during median-of-three partitioning) */
    return (*(const int *)int1 - *(const int *)int2);
}

static int partition(void *data, int esize,
        int i, int k, /* head_index 'i', tail_index 'k' */
        int (*compare)(const void *key1, const void *key2)) {
    char *a = data;

    void *pval,     /* partition value */
         *swap_temp;

    int r[3];

    /* allocate storage for the partition value and swapping */
    if((pval = malloc(esize)) == NULL)
        return -1;

    if((swap_temp = malloc(esize)) == NULL) {
        free(pval);
        return -1;
    }

    /* Use the median-of-three method to find the partition value */
    r[0] = (rand() % (k - i + 1)) + i;
    r[1] = (rand() % (k - i + 1)) + i;
    r[2] = (rand() % (k - i + 1)) + i;

    insert_sort(r, 3, sizeof(int), compare_int);
    memcpy(pval, &a[r[1] * esize], esize);

    /* create 2 partitions around the partition value */
    while(1) {
        /* move left until an element is found in the wrong partition */
        while((compare(&a[k * esize], pval) > 0) && (i < k))
            k--;

        /* move right until an element is found i the wrong partition */
        while((compare(&a[i * esize], pval) < 0) && (i < k))
            i++;

        if(i >= k) /* stop partitioning when the left and right counters cross */
            break;

        else { /* swap the elements now under the left and right counters */
            memcpy(swap_temp, &a[i * esize], esize);
            memcpy(&a[i * esize], &a[k * esize], esize);
            memcpy(&a[k * esize], swap_temp, esize);
        }
    }

    /* free  the storage allocated for partitioning */
    free(pval);
    free(swap_temp);

    /* return the position dividing the 2 partition */
    return k;
}

/* quick_sort */
int quick_sort(void *data, int size, int esize,
        int i, int k, /* head_index, tail_index */
        int (*compare)(const void *key1, const void *key2)) {

    int j; /* the position dividing the 2 partition */

    /* stop the recursion when it is not possible to partition further */
    while(i < k) {
        /* determine where to partition the elements */
        if((j = partition(data, esize, i, k, compare)) < 0)
            return -1;  /* process error */

        /* recursively sort the left partition */
        if(quick_sort(data, size, esize, i, j, compare) < 0)
            return -1;  /* process error */

        /* iterate and sort the right partition */
        i = j + 1;
    }
    return 0;
}
