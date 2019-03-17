#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

#include"sort.h"

int radix_sort(int *data,
        int size,
        int p,      /* number of bit */
        int k) {    /* max_element + 1 */
    int *counts,    /* 'counts'_array */
        *swap_temp;

    int index,
        pval,       /* position_value */
        i,
        j,
        n;          /* counter for significant_position */

    /* allocate storage for the 'counts'array */
    if((counts = (int *)malloc(k * sizeof(int))) == NULL)
        return -1;

    /* allocate storage for the sorted elements */
    if((swap_temp = (int *)malloc(size * sizeof(int))) == NULL) {
        free(counts);
        return -1;
    }

    /* Sort from the least significant position to the most significant */
    for(n = 0; n < p; n++) {

        /* initialize the counts */
        for(i = 0; i < k; i++)
            counts[i] = 0;

        /* calculate the 'position' value */
        pval = (int)pow((double)k, (double)n);

        /* count the occurrences of each digit value */
        for(j = 0; j < size; j++) {
            index = (int)(data[j] / pval) % k;
            counts[index]++;
        }

        /* adjust each count to reflect the counts before it */
        for(i = 1; i < k; i++)
            counts[i] += counts[i - 1];

        /* use the counts to position each element where it belongs */
        for(j = 0; j < size; j++) {
            index = (int)(data[j] / pval) % k;
            swap_temp[counts[index] - 1] = data[j];
            counts[index]--;
        }

        /* prepare to pass back the data as sorted thus far */
        memcpy(data, swap_temp, size * sizeof(int));
    }

    free(counts);
    free(swap_temp);

    return 0;
}
