#include<pthread.h>
void my_pthread_cond_wait(pthread_cond_t * c_Lock,
        pthread_mutex_t * m_Lock) {
    pthread_mutex_unlock(m_Lock);

    pthread_mutex_lock((pthread_mutex_t *)c_Lock);
    pthread_mutex_lock((pthread_mutex_t *)c_Lock);
    /* dead-lock, blocking, waiting for
     * async unlock */

    /* async-lock the pmx_pt */
    /* ... */

    pthread_mutex_lock((pthread_mutex_t *)m_Lock);
    /* dead-lock, blocking, waiting for
     * async unlock */
}

void my_pthread_cond_signal(pthread_cond_t * c_Lock) {
    pthread_mutex_unlock((pthread_mutex_t *)c_Lock);
}
