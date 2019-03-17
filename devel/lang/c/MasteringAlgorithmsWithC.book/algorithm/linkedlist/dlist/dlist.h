/* double direction linked list */
#ifndef dlist_h
#define dlist_h

#include<stdlib.h>

typedef struct _DListElmt {
    void *data;
    struct _DListElmt *prev;
    struct _DListElmt *next;
} DListElmt;

typedef struct _DList {
    int size;
    void (*destroy)(void *data); /* destroy func */
    DListElmt *head;
    DListElmt *tail;
} DList;

int dlist_init(DList *dlist, void (*destroy)(void *data));
int dlist_destroy(DList *dlist);

int dlist_ins_next(DList *dlist, DListElmt *element, const void *data);
int dlist_ins_prev(DList *dlist, DListElmt *element, const void *data);
int dlist_rem(DList *dlist, DListElmt *element, void **data);

#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)

#endif
