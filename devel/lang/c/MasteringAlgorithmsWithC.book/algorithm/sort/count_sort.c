#include<stdlib.h>
#include<string.h>

#include"sort.h"

int count_sort(int *data, int size, int k) {
    int *counts,
        *temp;

    int i,
        j;

    /* allocate storage for the counts */
    if((counts = (int *)malloc(k * sizeof(int))) == NULL)
        return -1;

    /* allocate storage for the sorted elements */
    if((temp = (int *)malloc(size * sizeof(int))) == NULL)
        return -1;

    /* initialize the 'counts'_array */
    for(i = 0; i < k; i++)
        counts[i] = 0;

    /* count the occurrences of each elements */
    for(j = 0; j < size; j++)
        counts[data[j]]++;

    /* adjust each count to reflect the 'counts'_array before it */
    for(i = 1; i < k; i++)
        counts[i] += counts[i - 1];

    /* use the 'counts'_array to position each elements where it belongs */
    for(j = 0; j < size; j++) {
        temp[counts[data[j]] - 1] = data[j];
        counts[data[j]]--;
    }

    /* prepare to pass back the sorted data */
    memcpy(data, temp, size * sizeof(int));

    /* free the storage alloacated for storing */
    free(counts);
    free(temp);

    return 0;
}
