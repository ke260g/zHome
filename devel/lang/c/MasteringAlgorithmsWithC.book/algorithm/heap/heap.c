#include<stdlib.h>
#include<string.h>

#include"heap.h"

/* private macros used by the heap implementation */
/* 'npos' means 'node position' */
#define heap_parent(npos) ((int)(((npos) - 1) / 2))
#define heap_left(npos) (((npos) * 2) + 1)
#define heap_right(npos) (((npos) * 2) + 2)

/* initialize heap */
void heap_init(Heap *heap,
        int (*cmpare)(const void *key1, const void *key2),
        void (*destroy)(void *data)) {
    /* Initialize the heap */
    heap->size = 0;
    heap->cmpare = cmpare;
    heap->destroy = destroy;
    heap->tree = NULL;
}

/* destroy heap */
void heap_destroy(Heap *heap) {
    int i;

    /* remove all the node */
    if(heap->destroy != NULL) {
        for(i = 0; i < heap->size; i++) {
            /* call a user-defined function to free dynamically allocated data. */
            heap->destroy(heap->tree[i]);
        }
    }

    /* Free the storage allocated for the heap */
    free(heap->tree);

    memset(heap, 0, sizeof(Heap));
}

/* insert heap */
int heap_insert(Heap *heap,
        const void *data) {
    void *temp;
    int ipos, /* inserted position */
        ppos; /* pushed position */

    /* allocate storage for the node */
    if((temp = (void **)realloc(heap->tree, (heap->size + 1) * sizeof(void *))) == NULL)
        return -1; /* can't allocate memory space */
    else
        heap->tree = temp; /* allocate successfully */

    /* Insert the node after the last node */
    heap->tree[heap->size] = (void *)data;

    /* Heapify the tree by pushing the contents of the new node upward */
    ipos = heap->size;
    ppos = heap_parent(ipos);

    while (ipos > 0 &&
            heap->cmpare(heap->tree[ppos], heap->tree[ipos]) < 0) {
        /* swap the contents of the current node and its parent */
        temp = heap->tree[ppos];
        heap->tree[ppos] = heap->tree[ipos];
        heap->tree[ipos] = temp;

        /* move up one level in the tree to continue heapifying */
        ipos = ppos;
        ppos = heap_parent(ipos);
    }

    /* Adjust the size of the heap to account for the inserted one */
    heap->size++;
    return 0;
}

/* extract heap */
int heap_extract(Heap *heap,
        void **data) {
    void *save,
    *temp;

    int ipos,
        lpos,
        rpos,
        mpos;

    /* do not allow extraction from an empty heap */
    if(heap->size == 0)
        return -1;

    /* extract the node at the top of the heap */
    *data = heap->tree[0];

    /* adjust the storage used by the heap */
    save = heap->tree[heap->size - 1];

    if(heap->size - 1 > 0) {
        if((temp = (void **)realloc(heap->tree, (heap->size - 1)*sizeof(void *))) == NULL)
            return -1; /* can't allocate the memory space */
        else
            heap->tree = temp;

        heap->size--;
    }

    else {
        /* Manage the heap when extracting the last node */
        free(heap->tree);
        heap->tree = NULL;
        heap->size = 0;
        return 0;
    }

    /* copy the last node to the top */
    heap->tree[0] = save;

    /* heapify the tree by pushing the contents of the new top downward */
    ipos = 0;
    lpos = heap_left(ipos);
    rpos = heap_right(ipos);

    while(1) {
        /* Select the child to swap with the current node */
        lpos = heap_left(ipos);
        rpos = heap_right(ipos);

        if(lpos < heap->size &&
                heap->cmpare(heap->tree[lpos], heap->tree[ipos]) > 0)
            mpos = lpos;
        else
            mpos = ipos;

        if(rpos < heap->size &&
                heap->cmpare(heap->tree[rpos], heap->tree[mpos]) > 0)
            mpos = rpos;

        /* when mpos is ipos, the heap property has been restored */
        if(mpos == ipos)
            break;
        else{
            /* swap the contents of the current node and the selected child */
            temp = heap->tree[mpos];
            heap->tree[mpos] = heap->tree[ipos];
            heap->tree[ipos] = temp;

            /* move down one level in the tree continue heapifying */
            ipos = mpos;
        }
    }

    return 0;
}

