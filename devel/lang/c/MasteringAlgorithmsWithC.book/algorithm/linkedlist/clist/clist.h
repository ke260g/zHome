#ifndef CLIST_H
#define CLIST_H

#include<stdlib.h>

typedef struct  _CListElmt {
    void *data;
    struct _CListElmt *next;
} CListElmt;

typedef struct _CList {
    int size;
    void (*destroy)(void *data);
    CListElmt *head;
} CList;

int clist_init(CList *clist, void(*destroy)(void *data));
int clist_destroy(CList *list);
int clist_ins_next(CList *clist, CListElmt *element, const void *data);
int clist_rem_next(CList *clist, CListElmt *element, void **data);
#endif
