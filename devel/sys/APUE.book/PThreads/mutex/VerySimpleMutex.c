#include<pthread.h>
#include<stdlib.h>

typedef struct _foo {
    int id;
    int f_count;
    pthread_mutex_t f_lock;
} foo;

foo *foo_alloc(const int id) {
    /* allocate the object */
    foo *fpt;
    if((fpt = (foo *)malloc(sizeof(foo))) != NULL) {
        fpt->id = id;
        fpt->f_count = 1;
        if(pthread_mutex_init(&fpt->f_lock, NULL) != 0) {
            /* fail to init a muttex */
            free(fpt);
            return NULL;
        }
    }
    return fpt;
}

void foo_hold(foo *fpt) {
    /* add a reference to the object */
    pthread_mutex_lock(&fpt->f_lock);
    fpt->f_count++;
    pthread_mutex_unlock(&fpt->f_lock);
}

void foo_rele(foo *fpt) {
    pthread_mutex_lock(&fpt->f_lock);
    if(--fpt->f_count == 0) {
        /* last reference */
        pthread_mutex_unlock(&fpt->f_lock);
        pthread_mutex_destroy(&fpt->f_lock);
        free(fpt);
    } else
        pthread_mutex_unlock(&fpt->f_lock);
}
