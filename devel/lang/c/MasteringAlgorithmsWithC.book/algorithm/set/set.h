#ifndef SET_H
#define SET_H

#include"slist/slist.h"
#include<stdlib.h>

typedef SList Set;

int set_init(Set *set, int (*match_func)(const void *key1, const void *key2),
        void (*destroy)(void *data));

#define set_destroy slist_destroy
/* set_destroy(Set *set); */
int set_insert(Set *set, const void *data); /* insert a member into the set */
int set_remove(Set *set, void **data); /* remove a member from the set */

int set_union(Set *setu, const Set *set1, const Set *set2); /* combine two sets into a union one */
int set_intersection(Set *seti, const Set *set1, const Set *set2); /* get the intersection between set1 and set2 */
int set_difference(Set *setd, const Set *set1, const Set *set2); /* get the difference between set1 and set2 */

int set_is_member(const Set *set, const void *data);        /* whether data is a member into set */
int set_is_subset(const Set *set_small, const Set *set_big); /* whether set_small is the subset of set_big */
int set_is_equal(const Set *set1, const Set *set2);         /* whether set1 is equal to set2 */

#endif /* SET_H */
