#include<stdlib.h>
#include<pthread.h>

struct job {
    /* double linked-list, queue */
    struct job *j_prev;
    struct job *j_next;

    pthread_t j_id; /* tells which thread handles this job */
    /* more stuff */
};

struct queue {
    struct job *q_head;
    struct job *q_tail;
    pthread_rwlock_t q_lock;
};

/* initialize a queue */
int queue_init(struct queue *qp) {
    int err;
    qp->q_head = NULL;
    qp->q_tail = NULL;
    err = pthread_rwlock_init(&qp->q_lock, NULL);
    if(err)
        return err;
    /* contiue initialization */
    return 0;
}

/* insert a job at the head of queue */
void job_insert(struct queue *qp,
        struct job *jp) {
    pthread_rwlock_wrlock(&qp->q_lock);
    jp->j_next = qp->q_head;
    jp->j_prev = NULL;
    if(qp->q_head != NULL)
        qp->q_head->j_prev = jp; /* not a empty queue */
    else
        qp->q_tail = jp; /* it's a empty queue */

    qp->q_head = jp; /* new queue head */
    pthread_rwlock_unlock(&qp->q_lock);
}

/* append a job on the tail of the queue. */
void job_append(struct queue *qp,
        struct job *jp) {
    pthread_rwlock_wrlock(&qp->q_lock);
    jp->j_next = NULL;
    jp->j_prev = qp->q_tail;
    if(qp->q_tail != NULL) /* not a empty queue */
        qp->q_tail->j_next = jp;
    else /* it's a empty, queue,
            append the head of queue */
        qp->q_head = jp;

    qp->q_tail = jp;
    pthread_rwlock_unlock(&qp->q_lock);
}

/* remove the given job from a queue */
void job_remove(struct queue *qp,
        struct job *jp) {
    pthread_rwlock_wrlock(&qp->q_lock);

    if(jp == qp->q_head) {
        qp->q_head = jp->j_next;
        if(qp->q_tail = jp) /* leave the last one job only */
            qp->q_tail = NULL;
        else
            jp->j_next->j_prev = jp->j_prev;
    } else if(jp == qp->q_tail) {
        qp->q_tail = jp->j_prev;
        jp->j_prev->j_next = jp->j_next; /* jp->j_next is NULL? */
    } else {
        jp->j_prev->j_next = jp->j_next;
        jp->j_next->j_prev = jp->j_prev;
    }
    pthread_rwlock_unlock(&qp->q_lock);
}

/* find a job for the given thread id */
struct job *job_find(struct queue *qp,
        pthread_t id) {
    struct job *jp;
    if(pthread_rwlock_rdlock(&qp->q_lock))
        return NULL;
    for(jp = qp->q_head; jp != NULL; jp = jp->j_next)
        if(pthread_equal(jp->j_id, id))
                break;
    pthread_rwlock_unlock(&qp->q_lock);
    return jp;
}
