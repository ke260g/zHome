#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"clist.h"

int clist_init(CList *clist, void(*destroy)(void *data)) {
    if(clist->destroy == NULL) { /* non destroy func */
        fprintf(stderr, "%s : The input linked list doesn't exist.\n"
                        "Can't be initialized.\n\n", __func__);
        return -1;
    }
    clist->size = 0;
    clist->destroy = destroy;
    clist->head = NULL;
    return 0;
}

int clist_destroy(CList *clist) {
    if(clist == NULL) { /* list doesn't exist */
        fprintf(stderr, "%s : The input list doesn't exist.\n\n", __func__);
        return -1;
    }

    if(clist->destroy == NULL) {
        fprintf(stderr, "%s : The input list doesn't has a specific destroy function.\n\n", __func__);
        return -1;
    }

    if(clist->size == 0) {
        fprintf(stderr, "%s : The input list is an empty one.\n"
                        "Nothing need to do.\n\n", __func__);
        return 0;
    }

    void *data;
    while(clist->size != 0) {
        clist_rem_next(clist, clist->head, &data);
        clist->destroy(data);
    }
    memset(clist, 0, sizeof(CList)); /* reset the list */
    return 0; /* successfully destroy */

}

int clist_ins_next(CList *clist, CListElmt *element, const void *data) {
    if(clist == NULL) { /* list doesn't exist */
        fprintf(stderr, "%s : The input list doesn't exist.\n\n", __func__);
        return -1;
    }

    if(element == NULL && clist->size != 0) {
        fprintf(stderr, "%s : The input element is NULL while the list is not empty.\n"
                        "This is not allowed.\n\n", __func__);
    }

    CListElmt *new_element = (CListElmt *)malloc(sizeof(CListElmt));
    if(new_element == NULL) {
        fprintf(stderr, "%s : Can't allocate the necessary mem space for new element\n", __func__);
        return -1;
    } else
        new_element->data = (void *)data;

    if(clist->size == 0) {  /* empty list */
        new_element->next = new_element;
        clist->head = new_element;
    } else { /* not a empty list and the input element is valid*/
        new_element->next = element->next;
        element->next = new_element;
    }

    clist->size++; /* increment size */
    return 0;
}

int clist_rem_next(CList *clist, CListElmt *element, void **data) {
    if(clist == NULL) { /* list doesn't exist */
        fprintf(stderr, "%s : The input list doesn't exist.\n\n", __func__);
        return -1;
    }

    if(clist->size == 0) {
        fprintf(stderr, "%s : The input list is an empty one.\n\n", __func__);
        return -1;
    }

    CListElmt *old_element;

    if(element->next == element) { /* the last element */
        old_element = element;
        clist->head = NULL;
    } else {
        old_element = element->next;
        element->next = element->next->next;

        if(old_element == clist->head)
            clist->head = old_element->next;
    }

    *data = old_element->data;

    free(old_element);
    clist->size--;
    return 0;
}
