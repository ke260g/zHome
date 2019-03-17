#ifndef HEAP_H
#define HEAP_H

/* Define a structure for heaps */
typedef struct Heap_ {
    int size;
    int (*cmpare)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    void **tree;
} Heap;

/* Public interface */
void heap_init(Heap *heap,
        int (*cmpare)(const void *key1, const void *key2),
        void (*destroy)(void *data));
/*
 * for a max-heap,
 * the comparison function must return an integer less than, equal to, or greater than zero
 * if the first argument is considered to be respectively less than, equal to, or greater than the second one.
 */

void heap_destroy(Heap *heap);

int heap_insert(Heap *heap, const void *data);
int heap_extract(Heap *heap, void **data);

#endif /* HEAP_H */
