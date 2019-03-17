#include<stdlib.h>
#include<string.h>


#include"slist/slist.h"
#include"set.h"

typedef SList Set;

int set_init(Set *set,
        int (*match_func)(const void *key1, const void *key2),
        void (*destroy)(void *data)) {
    /* initialize the set */
    if(set == NULL) {
        fprintf(stderr, "%s : the input set doesn't exist.\n", __func__);
        return -1;
    }

    slist_init(set, destroy);
    set->match = match_func;
    /*
     * match_func is used to distinguish two member whether equal,
     * equal returns 1, or returns 0.
     */
}

int set_insert(Set *set, const void *data) {
    /* insert a member into the set */
    if(set_is_member(set, data)) {
        fprintf(stderr, "%s : the data wanted to insert is alreary in the set\n", __func__);
        return -1;
    }

    return slist_ins_next(set, set->tail, data);
}

int set_remove(Set *set, void **data) {
    /* remove a member from the set */
    if(set == NULL) { /* set doesn't exist */
        fprintf(stderr, "The input set doesn't exist.");
        return -1; /* failed to remove */
    }

    if(set->size == 0) {/* empty set */
        fprintf(stderr, "The input set is empty.");
        return -1; /* failed to remove */
    }

    SListElmt *prev = NULL;
    SListElmt *member = set->head;
    for(; member != NULL; member = member->next) {
        if(set->match(*data, member->data))
            break;
        prev = member;
    }

    if(member == NULL) /* reach the tail */
        return -1;
    return slist_rem_next(set, prev, data);
}

int set_union(Set *setu, const Set *set1, const Set *set2) {
    /* combine two sets into a union one */
    if(set1->match == NULL) {
        fprintf(stderr, "%s : The input set doesn't have a legal match_function\n",
                __func__);
        return -1;
    }

    SListElmt *member;
    void *data;
    set_init(setu, set1->match, NULL); /* initialize for the union */

    for(member = set1->head; member != NULL; member = member->next) {
        data = member->data;
        if(slist_ins_next(setu, setu->tail, data) != 0) {
            fprintf(stderr, "%s : Can't insert the member into the new set\n"
                    "Something wrong occurs\n", __func__);
            set_destroy(setu);
            return -1;
        }
    } /* copy the set1 to the new set */

    for(member = set2->head; member != NULL; member = member->next) {
        if(set_is_member(set1, member->data))
            continue; /* don't insert the same member into the new set */
        else {
            data = member->data;
            if(slist_ins_next(setu, setu->tail, data) != 0) {
                fprintf(stderr, "%s : Can't insert the member into the new set\n"
                        "Something wrong occurs\n", __func__);
                set_destroy(setu);
                return -1;
            }
        }
    } /* look through set2 */
    return 0;
}

int set_intersection(Set *seti, const Set *set1, const Set *set2) {
    /* get the intersection between set1 and set2 */
    if(set1->match == NULL) {
        fprintf(stderr, "%s : The input set doesn't have a legal match_function\n",
                __func__);
        return -1;
    }

    SListElmt *member;
    void *data;
    set_init(seti, set1->match, NULL);

    for(member = set1->head; member != NULL; member = member->next) {
        if(set_is_member(set2, member->data)) {
            data = member->data;
            if(slist_ins_next(seti, seti->tail, data) != 0) {
                fprintf(stderr, "%s : Can't insert the member into the new set\n"
                        "Something wrong occurs\n", __func__);
                set_destroy(seti);
                return -1;
            }
        }
    }

    return 0;
}

int set_difference(Set *setd, const Set *set1, const Set *set2) {
    /* get the difference between set1 and set2 */
    if(set1->match == NULL) {
        fprintf(stderr, "%s : The input set doesn't have a legal match_function\n",
                __func__);
        return -1;
    }

    SListElmt *member;
    void *data;
    set_init(setd, set1->match, NULL);

    for(member = set1->head; member != NULL; member = member->next) {
        if( ! set_is_member(set2, member->data)) {
            data = member->data;
            if(slist_ins_next(setd, setd->tail, data) != 0) { /* error occurs when insert data */
                fprintf(stderr, "%s : Can't insert the member into the new set\n"
                        "Something wrong occurs\n", __func__);
                set_destroy(setd);
                return -1;
            }
        }
    }
    return 0;
}

int set_is_member(const Set *set, const void *data) {
    SListElmt *member;
    for(member = set->head; member != NULL; member = member->next)
        if(set->match(data, member->data))
            return 1;

    return 0;
}

int set_is_subset(const Set *set_small, const Set *set_big) {
    SListElmt *member;

    /* the ideal small set is larger than the bigger one */
    if(set_small->size > set_big->size)
        return 0;

    for(member = set_small->head; member != NULL; member = member->next)
        if(!set_is_member(set_big, member->data))
            return 0;

    return 1;
}

int set_is_equal(const Set *set1, const Set *set2) {

    /* firstly , thier sizes */
    if(set1->size != set2->size)
        return 0;

    return (set_is_subset(set1, set2) && set_is_subset(set2, set1));
}
