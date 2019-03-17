#include"stack.h"
#include"slist/slist.h"

#include<stdlib.h>

int stack_push(Stack *stack, const void *data) {
    return slist_ins_next(stack, NULL, data);
}

int stack_pop(Stack *stack, void **data) {
    return slist_rem_next(stack, NULL, data);
}
