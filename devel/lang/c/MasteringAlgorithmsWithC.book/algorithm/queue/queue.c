#include<stdlib.h>
#include"slist/slist.h"
#include"queue.h"

int queue_enqueue(Queue *queue, const void *data) {
    return slist_ins_next(queue, queue->tail, data);
}

int queue_dequeue(Queue *queue, void **data) {
    return slist_rem_next(queue, NULL, *data);
}
