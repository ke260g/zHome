#ifndef QUEUE_H
#   define QUEUE_H

#include<stdlib.h>
#include"slist/slist.h"

typedef SList Queue;

#define queue_init slist_init
#define queue_destroy slist_destroy

int queue_enqueue(Queue *queue, const void *data);
int queue_dequeue(Queue *queue, void **data);
#define queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)

#endif /* QUEUE_H */
