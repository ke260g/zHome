#ifndef STACK_H
#define STACK_H


#include"slist/slist.h"

#include <stdlib.h>

typedef SList Stack;
#define stack_init slist_init
#define stack_destroy slist_destroy

int stack_push(Stack *stack, const void *data);
int stack_pop(Stack *stack, void **data);
#define stack_peek(stack) ((stack)->head == NULL ? NULL :  (stack)->head->data)


#endif
