int insert_sort(void *data,
        int size, /* amount of element */
        int esize, /* element size */
        int (*cmpare)(const void *key1, const void *key2));

int quick_sort(void *data, int size, int esize,
        int i, int k,   /* head_index, tail_index */
        int (*compare)(const void *key1, const void *key2));

int merge_sort(void *data,
        int size,
        int esize,
        int i,
        int k,
        int (* compare)(const void *key1, const void *key2));

int count_sort(int *data, int size, int k);

int radix_sort(int *data,
        int size,
        int p,
        int k);
