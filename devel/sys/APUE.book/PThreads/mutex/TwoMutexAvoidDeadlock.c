#include<stdlib.h>
#include<pthread.h>

#define NHASH 29
#define HASH(id) (((unsigned long)id) % NHASH)

struct foo *fh[NHASH];
pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo {
    int f_count;
    pthread_mutex_t f_lock;
    int f_id;
    struct foo *f_next; /* protected by hashlock */
    /* a single-linked-list */
};

struct foo * foo_alloc(int id) { /* allocate the object */
    struct foo *fp;
    int idx;

    if((fp = (struct foo *)malloc(sizeof(struct foo))) != NULL) {
        fp->f_count = 1;
        fp->f_id = id;
        if(pthread_mutex_init(&fp->f_lock, NULL) != 0) {
            free(fp);
            return NULL;
        }

        idx = HASH(id);
        pthread_mutex_lock(&hashlock);

        /* fh[idx] is the head of single-linked-list, hash-table-bucket,
         * this is the `stack-like' single-linked-list */
        fp->f_next = fh[idx]; /* make the ->next point to the src-list */
        fh[idx] = fp;         /* make the head point to the new-node */

        pthread_mutex_lock(&fp->f_lock);
        pthread_mutex_unlock(&hashlock);
        /* continue initialization */
        pthread_mutex_unlock(&fp->f_lock);

    }
    return fp;
}

void foo_hold(struct foo *fp) { /* add reference to the object */
    pthread_mutex_lock(&fp->f_lock);
    fp->f_count++;
    pthread_mutex_unlock(&fp->f_lock);
}

struct foo *foo_find(int id) {
    struct foo *fp;
    pthread_mutex_lock(&hashlock);
    /* fh[HASH(id)] is to find the bucket */
    for(fp = fh[HASH(id)]; fp != NULL; fp = fp->f_next) {
        if(fp->f_id == id) {
            foo_hold(fp);
            break;
        }
    }
    pthread_mutex_unlock(&hashlock);
    return fp;
}

void foo_rele(struct foo *fp) {
    /* release a reference to the object */
    struct foo *tfp;
    int idx;

    /* block the access from another threads */
    pthread_mutex_lock(&fp->f_lock);
    if(fp->f_count == 1) {
        /* last reference */

        /* unblock the member to enbale-block the hash-table,
         * as we have to honor the lock-ordering */
        pthread_mutex_unlock(&fp->f_lock);

        /* locked the whole hash-table */
        pthread_mutex_lock(&hashlock);
        /* re-lock the fp, so that it can not be accessed by other thread */
        pthread_mutex_lock(&fp->f_lock);

        /* need to recheck the condition */
        if(fp->f_count != 1) {
            fp->f_count--;
            pthread_mutex_unlock(&fp->f_lock);
            pthread_mutex_unlock(&hashlock);
            return;
        }
        /* remove from list */
        idx = HASH(fp->f_id);
        tfp = fh[idx];
        if(tfp == fp) {
            /* head of linked-list */
            fh[idx] = fp->f_next;
        } else {
            while (tfp->f_next != fp)
                tfp = tfp->f_next;
            tfp->f_next = fp->f_next;
        }
        pthread_mutex_unlock(&hashlock);
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_destroy(&fp->f_lock);
        free(fp);
    } else {
        fp->f_count--;
        pthread_mutex_unlock(&fp->f_lock);
    }
}
