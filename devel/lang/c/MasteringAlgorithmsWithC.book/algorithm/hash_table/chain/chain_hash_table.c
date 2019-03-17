/*
 * implementation of
 * chain hash table,
 * abbreviate : chtbl
 */

#include<stdlib.h>
#include<string.h>
#include"../slist/slist.h"
#include"chain_hash_table.h"

/* public interface */

int chtbl_init(CHTBL *htbl,
        int slots, /* the amount of the slots */
        int (*hash)(const void *key), /* hash function */
        int (*match)(const void *key1, const void *key2),
        void (*destroy)(void *data)) /* destroy function */ {
    if(htbl == NULL) {
        fprintf(stderr, "%s : The input hash table doesn't exist\n", __func__);
        return -1;
    }

    if((htbl->table = (SList **)malloc(slots * sizeof(SList *))) == NULL) {
        fprintf(stderr, "%s : Can't allocate necessary memory space for the new hash table.\n", __func__);
        return -1;
    }

    /* initialize the slots */
    htbl->slots = slots;
    int i = 0; /* counter */
    for(i = 0; i < htbl->slots; i++) {
        htbl->table[i] = (SList *)malloc(sizeof(SList));
        memset(htbl->table[i], 0, sizeof(SList));
        slist_init(htbl->table[i], destroy);
    }

    htbl->hash = hash; /* hash_function */
    htbl->match = match;
    htbl->destroy = destroy;

    htbl->size = 0;
}

int chtbl_destroy(CHTBL *htbl) {
    if(htbl == NULL) {
        fprintf(stderr, "%s : The input hash table doesn't exist\n", __func__);
        return -1;
    }

    int i; /* counter */
    for(i = 0; i < htbl->slots; i++)
        slist_destroy(htbl->table[i]);

    free(htbl->table);

    memset(htbl, 0, sizeof(CHTBL)); /* reset the hash table */
    return 0;
}

int chtbl_insert(CHTBL *htbl, const void *data) {
    if(htbl == NULL) {
        fprintf(stderr, "%s : The input hash table doesn't exist\n", __func__);
        return -1;
    }


    if(chtbl_lookup(htbl, (void *)data) == 0) {
        fprintf(stderr, "%s : the input key is already in the hash table.\n", __func__);
        return 0;
    }

    int slot =      /* the slot number */
        htbl->hash(data) % htbl->slots;
        /* hash the key */

    if(slist_ins_next(htbl->table[slot], NULL, data) == 0) {
        htbl->size++;       /* succeed to insert */
        return 0;
    } else
        return -1;          /* failed to insert */
}

int chtbl_remove(CHTBL *htbl, void **data) {
    /* 'data' needed to be managed by the user */
    SListElmt *element,
              *prev = NULL;

    int slot = htbl->hash(*data) % htbl->slots;

    for(element = (htbl->table[slot])->head;
            element != NULL; element = element->next) {
        if(htbl->match(*data, element->data)) {
            /* the key is in the slot */
            if(slist_rem_next(htbl->table[slot], prev, data) == 0) {
                /* succeed to remove */
                htbl->size--;
                return 0;
            } else /* fail to remove */
                return -1;
        }
        prev = element;
    }

    return -1;
}

int chtbl_lookup(const CHTBL *htbl, void **data) {
    SListElmt *element;

    /* hash the key */
    int slot = htbl->hash(*data) % htbl->slots;

    for(element = (htbl->table[slot])->head;
            element != NULL; element = element->next)
        if(htbl->match(*data, element->data)) {
            *data = element->data;
            return 0;
        }

    return -1; /* the key is not in the hash table */
}
