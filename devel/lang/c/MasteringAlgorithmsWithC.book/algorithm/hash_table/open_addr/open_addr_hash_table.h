#ifndef OPEN_ADDR_HASH_TABLE_H
#define OPEN_ADDR_HASH_TABLE_H
/*
 * open address hash table,
 * ohtbl,
 * header file.
 *
 * h(key) = ( h1(key) + h2(key) * i ) Mod m
 *
 * m : the amount of slots;
 * i :
 * h1, h2 two hash_func;
 *
 * h1(key) = key Mod m
 * h2(key) = ( key Mod m' ) + 1
 */

#include<stdlib.h>

typedef struct OHTBL{
    int positions;  /* amount of the slots */
    void *vacated;  /* to store the removed slot */

    int  (*h1)(const void *key);
    int  (*h2)(const void *key);

    int (*match)(const void *key1, const void *key2); /* user implement function */
    int (*destroy)(void *data); /* user implement function */

    int size;  /* amount of elements in the hash table */

    void **table;
} OHTBL;

int ohtbl_init(OHTBL *htbl,
        int positions,
    int  (*h1)(const void *key),
    int  (*h2)(const void *key),
    int (*match)(const void *key1, const void *key2),
    int (*destroy)(void *data));

int ohtbl_destroy(OHTBL *htbl);
int ohtbl_insert(OHTBL *htbl, const void *data);
int ohtbl_remove(OHTBL *htbl, void **data);
int ohtbl_lookup(const OHTBL *htbl, void **data);
#endif
