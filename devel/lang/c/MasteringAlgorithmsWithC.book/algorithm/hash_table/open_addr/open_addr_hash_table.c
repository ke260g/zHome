/*
 * open address hash table,
 * ohtbl,
 *
 * implementation file.
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
#include<stdio.h>
#include<string.h>

#include"open_addr_hash_table.h"

const static char vacated; /* the vacate member */

int ohtbl_init(OHTBL *htbl,
        int positions,
        int  (*h1)(const void *key),
        int  (*h2)(const void *key),
        int (*match)(const void *key1, const void *key2),
        int (*destroy)(void *data)) {
    if(htbl == NULL) {
        fprintf(stderr, "%s : The input hash table doesn't exist\n", __func__);
        return -1;
    }

    if((htbl->table = (void **)malloc(positions * sizeof(void *))) == NULL) {
        fprintf(stderr, "%s : Can't allocate necessary memory space for the new hash table.\n", __func__);
        return -1;
    }

    htbl->positions = positions; /* initialize the position */
    int i ; /* counter */
    for ( i = 0; i < htbl->positions; i++ ) {
        htbl->table[i] = NULL;
    }

    htbl->h1 = h1;
    htbl->h2 = h2;
    htbl->match = match;
    htbl->destroy = destroy;

    htbl->vacated = (char *)&vacated;

    htbl->size = 0;
    return 0;
}

int ohtbl_destroy(OHTBL *htbl) {
    if(htbl == NULL) {
        fprintf(stderr, "%s : The input hash table doesn't exist\n", __func__);
        return -1;
    }

    if(htbl->destroy == NULL) {
        fprintf(stderr, "%s : The input hash table doesn't specify a destror_function.\n", __func__);
        return -1;
    }

    int i; /* counter */
    for ( i = 0; i < htbl->positions; i++ ) {
        if(htbl->table[i] != NULL && htbl->table[i] != htbl->vacated)
            htbl->destroy(htbl->table[i]);
    }
    free(htbl->table);
    memset(htbl, 0, sizeof(OHTBL)); /* reset the hash table */
    return 0;
}

int ohtbl_insert(OHTBL *htbl, const void *data) {
    if(htbl == NULL) {
        fprintf(stderr, "%s : The input hash table doesn't exist\n", __func__);
        return -1;
    }

    if(htbl->size == htbl->positions) {
        fprintf(stderr, "%s : Can't exceed the number of positions in the table.\n", __func__);
        return -1;
    }

    if(ohtbl_lookup(htbl, (void *)data) == 0) {
        fprintf(stderr, "%s : The input 'data' is already in the table.\n", __func__);
        return -1;
    }

    int position;
    int i; /* counter */
    for ( i = 0; i < htbl->positions; i++ ) {
        position = ( htbl->h1(data) + htbl->h2(data) * i ) % htbl->positions;
        if(htbl->table[position] == NULL || htbl->table[position] == htbl->vacated) {
            htbl->table[position] = (void *)data;
            htbl->size++;
            return 0;
        }

    }

    fprintf(stderr, "%s : Can't find the appropriate position for the data in the hash table.\n", __func__);
    return -1;
}

int ohtbl_remove(OHTBL *htbl, void **data) {
    if(htbl == NULL) {
        fprintf(stderr, "%s : The input hash table doesn't exist\n", __func__);
        return -1;
    }

    if(*data == NULL) {
        fprintf(stderr, "%s : You specify the valid memory space to store the removed data.\n", __func__);
        return -1;
    }

    int i, /* counter */
        position;

    for ( i = 0; i < htbl->positions; i++ ) {
        position = (htbl->h1(*data) + htbl->h2(*data) * i) % htbl->positions;

        if(htbl->table[position] == NULL) {
            fprintf(stderr, "%s : The input data is not found.\n", __func__);
            return -1;
        } else if (htbl->table[position] == htbl->vacated) {
            continue;
        } else if(htbl->match(htbl->table[position], *data)) {
            /* pass back the data from the table */
            *data = htbl->table[position];
            htbl->table[position] = htbl->vacated;
            htbl->size--;
            return 0;
        }
    }

    fprintf(stderr, "%s : The input data is not found.\n", __func__);
    return -1;
}

int ohtbl_lookup(const OHTBL *htbl, void **data) {
    int i, /* counter */
        position;

    for ( i = 0; i < htbl->positions; i++ ) {
        position = (htbl->h1(*data) + i * htbl->h2(*data)) % htbl->positions;

        if(htbl->table[position] == NULL) {
            fprintf(stderr, "%s : The input data is not found.\n", __func__);
            return -1;
        } else if(htbl->match(htbl->table[position], *data)) {
            /* pass back the data from the table */
            *data = htbl->table[position];
            return 0;
        }
    }

    fprintf(stderr, "%s : The input data is not found.\n", __func__);
    return -1;
}
