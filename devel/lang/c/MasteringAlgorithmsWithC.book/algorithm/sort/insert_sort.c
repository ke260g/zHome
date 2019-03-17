#include<stdlib.h>
#include<string.h>

#include"sort.h"

/* insert_method sort */
int insert_sort(void *data,
        int size, /* amount of element */
        int esize, /* element size */
        int (*cmpare)(const void *key1, const void *key2)) {
    char *a = data;
    void *key;
    int i,
        j;

    /* Allocate storage for the key element */
    if((key = (char *)malloc(esize)) == NULL)
        return -1; /* process error */

    /* Repeatedly insert a key element among the sorted elements */
    for(j = 1; j < size; j++) {
        memcpy(key, &a[j * esize], esize);
        i = j - 1;

        /* determine the position at which to insert the key element */
        while(i >= 0 && cmpare(&a[i * esize], key) > 0) {
            memcpy(&a[(i + 1) * esize], &a[i * esize], esize);
            i--;
        }
        memcpy(&a[(i + 1) * esize], key, esize);
    }

    free(key);

    return 0;
}
