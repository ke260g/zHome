/* double direction linked list */

#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include"dlist.h"

int dlist_init(DList *dlist, void (*destroy)(void *data)) {
    if(dlist->destroy == NULL) { /* non destroy func */
        fprintf(stderr, "%s : The input linked list doesn't exist.\n"
                        "Can't be initialized.\n\n", __func__);
        return -1;
    }
    dlist->size = 0;
    dlist->destroy = destroy;
    dlist->head = NULL;
    dlist->tail = NULL;
    return 0;
}

int dlist_ins_next(DList *dlist, DListElmt *element, const void *data) {
    if(dlist == NULL) { /* list doesn't exist */
        fprintf(stderr, "%s : The input list doesn't exist.\n\n", __func__);
        return -1;
    }

    if(element == NULL && dlist->size != 0) {
        fprintf(stderr, "%s : The input element is NULL while the list is not empty.\n"
                        "This is not allowed.\n\n", __func__);
    }

    DListElmt *new_element;
    if((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL) {
        fprintf(stderr, "%s : Can't allocate the necessary mem space for new element\n", __func__);
        return -1;
    } else
        new_element->data = data;

    if(dlist->size == 0) {  /* empty list */
        new_element->prev = NULL;
        new_element->next = NULL;
        dlist->head = new_element;
        dlist->tail = new_element;
    } else { /* not a empty list and the input element is valid*/
        new_element->next = element->next;
        new_element->prev = element;

        if(element->next == NULL) /* when the input element is the tail */
            dlist->tail = new_element;
        else
            element->next->prev = new_element;

        element->next = new_element;
    }

    dlist->size++; /* increment size */
    return 0;
}

int dlist_ins_prev(DList *dlist, DListElmt *element, const void *data) {
    if(dlist == NULL) { /* list doesn't exist */
        fprintf(stderr, "%s : The input list doesn't exist.\n\n", __func__);
        return -1;
    }

    if(element == NULL && dlist->size != 0) {
        fprintf(stderr, "%s : The input element is NULL while the list is not empty.\n"
                        "This is not allowed.\n\n", __func__);
    }

    DListElmt *new_element;
    if((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL) {
        fprintf(stderr, "%s : Can't allocate the necessary mem space for new element\n", __func__);
        return -1;
    } else
        new_element->data = data;

    if(dlist->size == 0) {  /* empty list */
        new_element->prev = NULL;
        new_element->next = NULL;
        dlist->head = new_element;
        dlist->tail = new_element;
    } else { /* not a empty list and the input element is valid*/
        new_element->next = element;
        new_element->prev = element->prev;

        if(element->prev == NULL) /* when the input element is the head */
            dlist->head = new_element;
        else
            element->prev->next = new_element;

        element->prev = new_element;
    }

    dlist->size++; /* increment size */
    return 0;
}

int dlist_rem(DList *dlist, DListElmt *element, void **data) {
    if(dlist == NULL) { /* list doesn't exist */
        fprintf(stderr, "%s : The input list doesn't exist.\n\n", __func__);
        return -1;
    }

    if(dlist->size == 0) {
        fprintf(stderr, "%s : The input list is an empty one.\n\n", __func__);
        return 0;
    }

    if(element == NULL) {
        fprintf(stderr, "%s : Can't remove a NULL element from the list.\n\n", __func__);
        return -1;
    }

    if(dlist->size == 1) { /* the last element in the list */
        dlist->tail = NULL;
        dlist->head = NULL;
    }

    *data = element->data;  /* to store the data in removed element */

    if(element->prev == NULL) { /* the input element is  the head */
        dlist->head = element->next;
        element->next->prev = NULL;

    } else if (element->next == NULL ) { /* the input element is  the tail */
        dlist->tail = element->prev;
        element->prev->next = NULL;

    } else {
        element->prev->next = element->next;
        element->next->prev = element->prev;

    }

    free(element);
    dlist->size--;
    return 0; /* successful remove */
}

int dlist_destroy(DList *dlist) {
    if(dlist == NULL) { /* list doesn't exist */
        fprintf(stderr, "%s : The input list doesn't exist.\n\n", __func__);
        return -1;
    }

    if(dlist->destroy == NULL) {
        fprintf(stderr, "%s : The input list doesn't has a specific destroy function.\n\n", __func__);
        return -1;
    }

    if(dlist->size == 0) {
        fprintf(stderr, "%s : The input list is an empty one.\n"
                        "Nothing need to do.\n\n", __func__);
        return 0;
    }

    void *data;
    while(dlist->size != 0) {
        dlist_rem(dlist, dlist->head, &data);
        dlist->destroy(data);
    }
    memset(dlist, 0, sizeof(DList)); /* reset the list */
    return 0; /* successfully destroy */

}
