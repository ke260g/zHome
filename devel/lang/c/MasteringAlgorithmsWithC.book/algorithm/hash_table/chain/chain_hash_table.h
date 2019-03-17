#ifndef CHAIN_HASH_TABLE_H
#   define CHAIN_HASH_TABLE_H

/*
 * this is the header file for
 * chain hash table,
 * abbreviate : chtbl
 */

#include<stdlib.h>
#include"../slist/slist.h"

typedef struct CHTBL_ {
    int slots; /* the amount of the slots */
    int size; /* the whole table size */

    int (*hash)(const void *key); /* the hash_function */
    int (*match)(const void *key1, const void *key2);

    void (*destroy)(void *data); /* destroy function */

    SList **table; /* table is an array, consisting of singly linked_lists' pointers */
} CHTBL;  /* chain hash table */

/* public interface */

int chtbl_init(CHTBL *htbl, int slots, int (*hash)(const void *key),
        int (*match)(const void *key1, const void *key2),
        void (*destroy)(void *data));

int chtbl_destroy(CHTBL *htbl);
int chtbl_insert(CHTBL *htbl, const void *data);
int chtbl_remove(CHTBL *htbl, void **data);
int chtbl_lookup(const CHTBL *htbl, void **data);

#endif /* CHAIN_HASH_TABLE_H */
