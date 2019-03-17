#include<stdlib.h>
#include<string.h>
#include<stdarg.h>

#include"slist.h"

void slist_init(SList *slist, void (*destroy)(void *data)) {
    /* initialize the linked list */
    slist->size = 0;
    slist->destroy = destroy;
    slist->head = NULL;
    slist->tail = NULL;
}

void slist_destroy(SList *slist) {
    if(slist->destroy == NULL) { /* non destroy func */
        fprintf(stderr, "Can't destroy the linked list\n"
                        "You don't define the destroy function\n");
        return;
    }

    if(slist == NULL) { /* list doesn't exist */
        fprintf(stderr, "The input list doesn't exist.");
        return;
    }

    void *data;
    /* 'data' is used to store the data in the removing element */

    while(slist->size > 0 && slist_rem(slist, NULL, &data))
            slist->destroy(data);
    memset(slist, 0, sizeof(SList)); /* reset the list */
}

int slist_ins_next(SList *slist, SListElmt *element, const void *data){
    if(slist == NULL) { /* list doesn't exist */
        fprintf(stderr, "The input list doesn't exist.");
        return -1;
    }

    SListElmt *new_element;

    /* allocate storage for the element. */
    if((new_element = (SListElmt *)malloc(sizeof(SListElmt))) == NULL)
        return -1; /* fail to allocate memory space */

    /* insert the element into the list */
    new_element->data = (void *)data;
    if(element == NULL) {
        /* handle insertion at the head of the list */
        new_element->next = slist->head;
        slist->head = new_element;
    } else {
        new_element->next = element->next;
        element->next = new_element;
    }

    if(new_element->next == NULL)
        slist->tail = new_element;

    slist->size++;

    return 0; /* successfully insert the element. */
}

int slist_rem(SList *slist, SListElmt **element, void **data) {
    /*
     * data_parameter is used store the data in its removed element
     * and it's a output parameter
     *
     * remove the input_element in the list,
     * if the input_element is NULL, then remove the head_element.
     */

    if(slist == NULL) { /* list doesn't exist */
        fprintf(stderr, "The input list doesn't exist.");
        return -1; /* failed to remove */
    }

    if(slist->size == 0) {/* empty list */
        fprintf(stderr, "The input list is empty.");
        return -1; /* failed to remove */
    }

    SListElmt *old_element;

    if (*element == NULL) {  /* remove the head element */
        old_element = slist->head;
        slist->head = slist->head->next;
    } else {
        old_element = *element;
        *element = (*element)->next;
    }

    *data = old_element->data;
    free(old_element);

    slist->size--;
    if(slist->size == 0) {
        slist->tail = NULL;
        slist->head = NULL;
    }

    return 0;   /* successfully remove element */
}

int slist_rem_next(SList *slist, SListElmt *element, void **data) {
    /*
     * data_parameter is used store the data in its removed element
     * and it's a output parameter
     *
     * remove the input_element->next in the list,
     * if the input_element is NULL, then remove the head_element.
     */

    if(slist == NULL) { /* list doesn't exist */
        fprintf(stderr, "The input list doesn't exist.");
        return -1; /* failed to remove */
    }

    if(slist->size == 0) {/* empty list */
        fprintf(stderr, "The input list is empty.");
        return -1; /* failed to remove */
    }

    SListElmt *old_element;

    if (element == NULL) {  /* remove the head element */
        old_element = slist->head;
        slist->head = slist->head->next;
    } else {
        old_element = element->next;
        element->next = element->next->next;
    }

    *data = old_element->data;
    free(old_element);

    slist->size--;
    if(slist->size == 0) {
        slist->tail = NULL;
        slist->head = NULL;
    }

    return 0;   /* successfully remove element */
}

SListElmt *slist_find_elmt(SList *slist, int *iter,
        int (*find_elmt_func)(void *data, void const *key), void *key) {
    if(slist->size == 0) {
        fprintf(stderr, "Empty list\n");
        return NULL;
    }

    if(*iter > slist->size || *iter < 1) {
        return NULL;
        fprintf(stderr, "The iter number is invalid. Can't find the element in the list\n");
    }

    if(slist == NULL) { /* list doesn't exist */
        fprintf(stderr, "The input list doesn't exist.");
        return NULL; /* failed to find */
    }

    SListElmt *TransElmt = slist->head;
    int counter = *iter;
    for (; counter > 1 ; counter-- )
        TransElmt = TransElmt->next;

    for( ; *iter <= slist->size ; (*iter)++) {
        if(find_elmt_func(TransElmt->data, key) == 0) {
            return TransElmt;
        }
        TransElmt = TransElmt->next;
    }

    *iter = 1;
    return TransElmt;
}
