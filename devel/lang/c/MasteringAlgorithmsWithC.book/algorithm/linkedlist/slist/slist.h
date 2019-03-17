#ifndef SLIST_H
#define SLIST_H

#include<stdlib.h>
#include<stdio.h>

/* linked list element */
typedef struct SListElmt{
    void *data;
    struct SListElmt *next;
} SListElmt;

/* singly linked list */
typedef struct SList{
    int size; /* amount of element */
    void (*destroy)(void *data); /* destroy element func */
    int (*match)(const void *key1, const void *key2); /* match element func */
    SListElmt *head;
    SListElmt *tail;
} SList;

/* Public Interface */
void slist_init(SList *list, void (*destroy)(void *data));
void slist_destroy(SList *list);
int slist_ins_next(SList *list, SListElmt *element,
        const void *data);
int slist_rem(SList *list, SListElmt **element, void **data);
SListElmt *slist_find_elmt(SList *slist, int *iter, int (*find_elmt_func)(void *data, void const *key), void *key);

int slist_rem_next(SList *slist, SListElmt *element, void **data);
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)
#endif
