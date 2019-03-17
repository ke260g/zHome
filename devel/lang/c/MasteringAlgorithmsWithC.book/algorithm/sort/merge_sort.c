#include<stdlib.h>
#include<string.h>

#include"sort.h"

static int merge(void *data,
        int esize,
        int i, /* top_index */
        int j, /* middle_index */
        int k, /* bottom_index */
        int (* compare)(const void *key1, const void *key2)) {

    char *a = data, /* a , array */
         *m;        /* point to a temp array */

    /* initialize the counters used in merging */
    int ipos = i,       /* left_division */
        jpos = j + 1,   /* right_division */
        mpos = 0;

    /* allocate storage for the merged elements */

    if((m = (char *)malloc(esize * ((k - i) + 1))) == NULL)
        return -1;  /* failed to allocate neccessary mem_space */

    /* continue while either division has elements to merge */
    while(ipos <= j || jpos <= k) {
        if(ipos > j) {
            /* The left division has no more elements to merge */
            while(jpos <= k) {
                memcpy(&m[mpos * esize], &a[jpos * esize], esize);
                jpos++;
                mpos++;
            }
            continue;
        } else if (jpos > k) {
            /* The right division has no more elements to merge */
            while(ipos <= j) {
                memcpy(&m[mpos * esize], &a[ipos * esize], esize);
                ipos++;
                mpos++;
            }
            continue;
        }

        /* append the next ordered elements to the merged elements */
        if(compare(&a[ipos * esize], &a[jpos * esize]) < 0) {
            memcpy(&m[mpos * esize], &a[ipos * esize], esize);
            ipos++;
            mpos++;
        } else {
            memcpy(&m[mpos * esize], &a[jpos * esize], esize);
            jpos++;
            mpos++;
        }
    }

    /* prepare to pass back the merged data. */
    memcpy(&a[i * esize], m, esize * ((k - i) + 1));

    free(m);

    return 0;
}

int merge_sort(void *data,
        int size,
        int esize,
        int i, /* head index */
        int k, /* tail index */
        int (* compare)(const void *key1, const void *key2)) {
    int j; /* position of divition */

    /* stop the recursion when no divisions can be made */
    if(i < k) {
        /* determine where to divide the elements */
        j = (int)(((i + k - 1)) / 2);

        /* recursively sort the 2 divisions */
        if(merge_sort(data, size, esize, i, j, compare) < 0)
            return -1; /* process error */

        if(merge_sort(data, size, esize, j + 1, k, compare) < 0)
            return -1; /* process error */

        /* merge the two sorted divisions into a single sorted set */
        if(merge(data, esize, i, j, k, compare) < 0)
            return -1; /* process error */
    }

    return 0;
}
