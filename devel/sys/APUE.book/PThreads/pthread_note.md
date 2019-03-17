# pthread Catalog
Resources,Identification, Creation, Termination,
mutex, spin, rwlock, cond, barrier

---
### Resources
+ ##### shared resources in a single process
    + text-section of the executalbe program
    + global and heap mem
    + stacks
    + file descriptors
+ ##### uni-resources
    + a set of regs values
    + a stack
    + a scheduling priority and policy
    + a signal mask
    + an errno variable
    + thread-specific data

---
### Interface common behavior
+ any trylock() interface will return the errno EBUSY if failed.
+ any timed\*() interface will return the errno ETIMEOUT if failed.

---
### Identification:
```c
pthread_t tid;
pthread_equal(pthread_t, pthread_t); // return 0 or 1
pthread_self(void);     // return tid
```

---
### Creation:
```c
pthread_create(pthread_t *output_param-tid_pt,
        const pthread_attr_t *input_param-attr,
        void *(* new_thread_start_routine)(void *),
        void *arg);
```


---
### Termination:
```c
pthread_exit(void *retval);
pthread_join(pthread_t thread, void **retval);
pthread_cancel(pthread_t tid);

/* only pthread_exit() will invole the pushed cleanup_rontines.
 * we have to match calls to _pop() with the calls to _push()
 * after the pthread_exit() */
pthread_cleanup_push(void (* routine)(void *),
        void *arg);
pthread_cleanup_pop(int execute);

/* detach the thread, which will be un-joinable */
pthread_detach(pthread_t tid);
```

---
### Mutex-Lock:
```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int pthread_mutex_init(pthread_mutex_t *output_param-mutex,
        const phtread_mutexattr_t *input_param-attr);
int pthread_mutex_destroy(pthread_mutex_t *input_param);

/* following functions @mutex is the input_param */
pthread_mutex_lock(pthread_mutex_t *mutex);
pthread_mutex_unlock(pthread_mutex_t *mutex);
phtread_mutex_trylock(pthread_mutex_t *mutex);
pthread_mutex_timedlock(pthread_mutex_t *mutex,
        const struct timespec *abstime);
```
###### mutex dead lock
+ a thread itself tries to lock the same mutex twice.
+ one thread hold a mutex and block while trying to lock a second mutex,
meanwhile another thread holding the second mutex tries to lock the first mutex.

---
### Spin-Lock
```c
/* like a mutex, except that instead of blocking a process by sleeping,
 * blocking by busy-waiting(spinning).
 * used in situations where locks are held for short periods of times
 * and threads don't want to incur the cost being descheduled.
 * It's the low-level primitives to implement other types of locks.
 * It's useful in a non-preemptive kernel.
 *
 * @pshared is one of PTHREAD_PROCESS_PRIVATE or PTHREAD_PROCESS_SHARED
 */
pthread_spin_init(pthread_spinlock_t *lock,
        int pshared);
pthread_destroy(pthread_spinlock_t *lock);

pthread_spin_lock(pthread_spinlock_t *lock);
pthread_spin_trylock(pthread_spinlock_t *lock);
pthread_spin_unlock(pthread_spinlock_t *lock);
```

---
### RW-Lock:
```c
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER
int pthread_rwlock_init(pthread_rwlock_t *output_param-rwlock,
        const pthread_rwlockattr_t *attr);
int phtread_rwlock_destroy(pthread_rwlock_t *input_param-rwlock);

/*
 * When a rwlock is write-locked with #_wrlock(),
 * all threads attempting to lock it with #_wr/rdlock()
 * will block until it is unlocked.
 * When a rwlock is read-locked with #_rdlock(),
 * all threads attempting to lock it in read mode with #_rdlock()
 * will be given access,
 * but any threads attempting to lock it in write-mode with #_wrlock()
 * will block until all the threads have released thier read-lock.
 */
pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
pthread_rwlock_unlock(phtread_rwlock_t *rwlock);

pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);

pthread_rwlock_timedrdlock(pthread_rwlock_t *rwlock,
        const struct timespec *abstime);
pthread_rwlock_timedwrlock(pthread_rwlock_t *rwlock,
        const struct timespec *abstime);
```

---
### Condition-Lock
```c
/* It's complicated to use, see my_cond_implement.c */
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_init(pthread_cond_t *output_param-cond,
        const pthread_condattr_t *input_param-attr);
phtread_destroy_(pthread cond_t *input_param-cond);

pthread_cond_wait(pthread_cond_t *cond),
    pthread_mutex_t *mutex);
pthread_cond_timedwait(pthread_cond_t *cond,
        pthread_mutex_t *mutex,
        const struct timespec *abstime);

pthread_cond_signal(pthread_cond_t *cond); /* wake up at least one */
pthread_cond_broadcast(pthread_cond_t *cond); /* wake up all */
```

---
### Barriers
```c
/* allow each thread to wait until all cooperating threads
 * have reached the same point, and the continue to exec,
 * the implement-theory is simple, just a mutex with a @count. */
int pthread_barrier_init(pthread_barrier_t *barrier,
        const pthread_barrierattr_t *attr,
        unsigned int count);
int pthread_barrier_destroy(pthread_barrier_t *barrier);
int pthread_barrier_wait(pthread_barrier_t *barrier);
```
