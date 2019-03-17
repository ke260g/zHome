 /* LDD3 quick note */

send_sig(SIGUSR1, current, 0);
/* send posix-singal to userspace,
 * third-param is normally set to `0' */

typedef u8;
typedef u16;
typedef u32;
typedef u64;

PAGE_SIZE;

#if 1 /* <<== duplex-list ==>> */
/* create and initialize */
LIST_HEAD(list); /* or */ struct list_head list;
//INIT_LIST_HEAD(&list);
list_add(struct list_head *new, struct list_head *head);
list_add_tail(struct list_head *new, struct list_head *head);

list_del(struct list_head *entry);
list_del_init(struct list_head *entry);
/* @entry is removed from the list.
 * If @entry might ever be reinserted into another list,
 * you should use list_del_init,
 * which reinitializes the linked list pointers. */
list_move(struct list_head *entry,
        struct list_head *head);
list_move_tail(struct list_head *entry,
        struct list_head *head);
/* @entry is removed from its current list
 * and added to the beginning of @head.
 *
 * To put @entry at the end of @head,
 * use list_move_tail instead. */
list_empty(struct list_head *head);
/* returns a non-zero if the given list is empty.  */

list_splice(struct list_head *list, struct list_head *head);
/* insert @list immediately after @head. */

LIST_HEAD *pos;
list_for_each(pos, head) {
    do_something(pos);
};

list_for_each_prev(pos, head) {
    do_something(pos);
};

/* If your loop may delete entries in the list,
 * use this version. It simply stores the
 * next entry in the list in next
 * at the beginning of the loop,
 * so it does not get confused
 * if the entry pointed to by cursor is deleted. */
list_for_each_safe(struct list_head *cursor,
        struct list_head *next,
        struct list_head *list);

list_for_each_entry(type *cursor,
        struct list_head *list, member_name);
list_for_each_entry_safe(type *cursor,
        type *next,
        struct list_head *list,
        member);
/* These macros ease the process of dealing with
 * a list containing a given type of structure.
 * Here, cursor is a pointer to the containing structure type,
 * and member is the name of the `list_head' structure
 * within the containing structure.
 * With these macros, there is no need to
 * put list_entry calls inside the loop. */

#endif /* >>== duplex-list ==<< */

#if 1 /* <<== mutex ==>> */
/* mutex */
#include<linux/mutex.h>
struct mutex lock;
mutex_init(struct mutex *lock);
mutex_lock(struct mutex *lock);
mutex_is_lock(struct mutex *lock);
mutex_try_lock(struct mutex *lock);
mutex_destroy(struct mutex *lock);

#include<linux/semaphore.h>
struct semaphores sem;
sema_init(&sem, 1); /* init with unlock state */
sema_init(&sem, 0); /* init with locked state */
down(&sem); /* lock un-interruptable */
down_interruptible(&sem); /* userspace can be interrupted */
down_trylock(&sem);
down_killable(&sem);
long jiffies = 10;
down_timeout(&sem, jiffies);

up(&sem);   /* unclock */
#endif /* >>== mutex ==<< */

#if 1/* <<== transfer mem between user-space and kernel-space ==>> */
#include<asm/uaccess.h>
/* address verification */
int ret = access_ok(int type, const void *addr, unsigned long size);
/*
 * @type is eithor VERIFY_READ or VERIFY_WRITE,
 * means read-from-user or write-to-user
 * return : 1 for success; 0 for failure, it's suggested to return -EFAULT
 */
/* after verification, specific data type can be transfer */
put_user(void *kernel, void *user); /* put to user, it is not safe!!!  */
get_user(void *kernel, void *user); /* get from user, it is not safe!!! */

/* anyway, using interface below is more wisdom */
copy_to_user(void *user, void *kernel, unsigned long size);
copy_from_user(void *kernel, void *user, unsigned long size);
#endif /* >>== transfer mem between user-space and kernel-space ==<< */

#if 1 /* <<== capability ==>> */
#include<linux/sched.h>
int capable(int capability);
/* @capability is one of CAP_* (defined in #include<linux/capability>) */
/* >>== capability ==<< */

/* <<== wait queue for sleep ==>> */
wait_queue_head_t queue;
init_waitqueue_head(&queue);

wait_event(queue, condition);
wait_event_interruptible(queue, condition);
wait_event_timeout(queue, condition, timeout);
wait_event_interruptible_timeout(queue, condition, timeout);
/* @condition is the expression in if(condition) */

void wake_up(struct wait_queue **q);
void wake_up_interruptible(struct wait_queue **q);
void wake_up_nr(struct wait_queue **q, int nr);
void wake_up_interruptible_nr(struct wait_queue **q, int nr);
void wake_up_all(struct wait_queue **q);
void wake_up_interruptible_all(struct wait_queue **q);
void wake_up_interruptible_sync(struct wait_queue **q);
/* never sleep when you are running in an atomic context. */
/* never sleep when holding a lock */
/* cannot sleep if you have disabled interrupts. */
#endif /* >>== wait queue for sleep ==<< */

#if 1 /* <<== manual sleep ==>> */
typedef struct { /* ... */ } wait_queue_t;
init_waitqueue_entry(wait_queue_t *entry, struct task_struct *task);
/* The wait_queue_t type is used to place a process onto a wait queue. */
void prepare_to_wait(wait_queue_head_t *queue, wait_queue_t *wait, int state);
void prepare_to_wait_exclusive(wait_queue_head_t *queue,
        wait_queue_t *wait,
        int state);
void finish_wait(wait_queue_head_t *queue,
        wait_queue_t *wait);
#endif /* >>== manual sleep ==<< */

#if 1 /* <<== process running status ==>> */
set_current_state(TASK_INTERRUPTIBLE);
set_current_state(TASK_RUNNING);
set_current_state(TASK_INTERRUPTIBLE);

schedule(); /* allocate */
schedule_timeout(unsigned long);
#endif /* >>== process running status ==<< */

#if 1 /* <<== jiffies and time ==>> */
#include <linux/jiffies.h>
#include <linux/time.h>
// obtain
unsigned long j, stamp_1, stamp_half, stamp_n;
j = jiffies;                      /* read the current value */
stamp_1    = j + HZ;              /* 1 second in the future */
stamp_half = j + HZ/2;            /* half a second */
stamp_n    = j + n * HZ / 1000;   /* n milliseconds */
/* HZ means one second in `jiffies' calculate unit */

u64 get_jiffies_64(void);
void do_gettimeofday(struct timeval *tv);
struct timespec current_kernel_time(void);

// comparing two jiffies
int time_after(unsigned long a,
        unsigned long b); /* (a > b) ? 1 : 0 */
int time_before(unsigned long a,
        unsigned long b); /* (a < b) ? 1 : 0 */
int time_after_eq(unsigned long a,
        unsigned long b); /* (a >= b) ? 1 : 0 */
int time_before_eq(unsigned long a,
        unsigned long b); /* (a <= b) ? 1 : 0 */

// convert
unsigned long timespec_to_jiffies(struct timespec *value);
void jiffies_to_timespec(unsigned long jiffies,
        struct timespec *value);
unsigned long timeval_to_jiffies(struct timeval *value);
void jiffies_to_timeval(unsigned long jiffies,
        struct timeval *value);

// delay and sleep
#include <linux/delay.h>
void ndelay(unsigned long nsecs);
void udelay(unsigned long usecs);
void mdelay(unsigned long msecs);
void msleep(unsigned int millisecs);
unsigned long msleep_interruptible(unsigned int millisecs);
void ssleep(unsigned int seconds)
#endif /* >>== jiffies and time ==<< */

#if 1 /* <<== kernel timers ==>> */
#include <linux/timer.h>
    struct timer_list {
        /* ... */
        unsigned long expires;
        void (*function)(unsigned long);
        unsigned long data;
    };
void init_timer(struct timer_list *timer);
struct timer_list TIMER_INITIALIZER(_function, _expires, _data);
void add_timer(struct timer_list * timer);
int del_timer(struct timer_list * timer);
#endif /* >>== kernel timers ==<< */

#if 1 /* <<== tasklets, which resemble timer ==>> */
/*
 * always run on interrupt time, on same CPU
 * receive an unsigned long argu
 * you can only simply ask for it to be executed
 * at a later time chosen by the kernel.
 * sounds like async-callback timers.
 *
 * software interrupt
 */
#include <linux/interrupt.h>
struct tasklet_struct {
    /* ... */
    void (*func)(unsigned long);
    unsigned long data;
};
void tasklet_init(struct tasklet_struct *t,
        void (*func)(unsigned long),
        unsigned long data);
DECLARE_TASKLET(name, func, data);
DECLARE_TASKLET_DISABLED(name, func, data);

void tasklet_enable(struct tasklet_struct *t);
void tasklet_disable(struct tasklet_struct *t);
void tasklet_disable_nosync(struct tasklet_struct *t);
void tasklet_hi_schedule(struct tasklet_struct *t);
void tasklet_kill(struct tasklet_struct *t);
#endif /* >>== tasklets, which resemble timer ==<< */

#if 1/* <<== workqueue, like tasklet ==>> */
/*
 * run a function at some future time,
 * workqueue functions run in the context of a special kernel process,
 * more flexible, can be sleeped
 * on the same CPU
 * callback-function can be delayed for an explicit interval.
 */
struct workqueue_struct *create_workqueue(const char *name);
struct workqueue_struct *create_singlethread_workqueue(const char *name);
INIT_WORK(struct work_struct *work,
        void (*function)(void *),
        void *data);
PREPARE_WORK(struct work_struct *work,
        void (*function)(void *),
        void *data);
int queue_work(struct workqueue_struct *queue,
        struct work_struct *work);
int queue_delayed_work(struct workqueue_struct *queue,
        struct work_struct *work,
        unsigned long delay);
int cancel_delayed_work(struct work_struct *work);

/* after cancel_delayed_work returns 0 ,
 * you must follow that call with a call to: */
void flush_workqueue(struct workqueue_struct *queue);
void destroy_workqueue(struct workqueue_struct *queue);
#endif /* >>== workqueue, like tasklet ==<< */

#if 1 /* <<== shared queue ==>> */
// the default one is kernel
/* but you have to be careful to use it */
/* the interface is not noted here */
#endif /* >>== shared queue ==<< */

#if 1 /* <<== memory allocate ==>> */
#include <linux/slab.h> /* interface */
#include <linux/gfp.h> /* GPF_* macro */
// [1] most usages
void *kmalloc(size_t size, int flags);
/* @flags normally is set to `GFP_KERNEL' or `GFP_USER'
 * interrupt handlers, tasklets, and kernel timers need `GFP_ATOMIC'
 * as GFP_KERNEL can no
 * special flags: __GFP_DMA
 */
void kfree(void *addr);

// [2] cache manager, so-called slab allocator
// can  be  used  to allocate several objects of the same size.
kmem_cache_t *kmem_cache_create(const char *name, size_t size,
        size_t offset,
        unsigned long flags,
        void (*constor)(void *, kmem_cache_t *, unsigned long flags),
        void (*destructor)(void *, kmem_cache_t *, unsigned long flags));
int kmem_cache_destroy(kmem_cache_t *cache);
/* `SLAB_NO_REAP', `SLAB_HWCACHE_ALIGN', `SLAB_CACHE_DMA'
 * @flags that can be specified while creating a cache.
 * */
/* `SLAB_CTOR_ATOMIC', `SLAB_CTOR_CONSTRUCTOR'
 * @flags that the allocator can pass to
 * the constructor and the destructor functions. */
void *kmem_cache_alloc(kmem_cache_t *cache, int flags);
void kmem_cache_free(kmem_cache_t *cache, const void *obj);
/* /proc/slabinfo contains statistics on slab cache usage. */

// [3] mempool, try to avoid memory allocation failures
// by keeping an “emergency list” of allocated items.
mempool_t *mempool_create(int min_nr,
        mempool_alloc_t *alloc_fn,
        mempool_free_t *free_fn,
        void *data);
void mempool_destroy(mempool_t *pool);
void *mempool_alloc(mempool_t *pool, int gfp_mask);
void mempool_free(void *element, mempool_t *pool);

// [4] pages manipulate, very dangerous to do so

// [5] access physical mem through virtual mem
void *ioremap(unsigned long offset, unsigned long size);
void iounmap(void *addr);
#endif /* >>== memory allocate ==<< */

#if 1 /* <<== interrupt basic ==>> */
int request_irq(unsigned int irq,
    irq_handler_t (* handler)(int , void *),
    unsigned long flags,
    const char *dev_name,
    void *dev_id);
void disable_irq(int irq);
void disable_irq_nosync(int irq);
void enable_irq(int irq);
void free_irq(unsigned int irq, void *dev_id);
/*
 * @irq, irq source, init when boot, platform depend
 * @handler,
 * @flags, various bit mask
 * @dev_name, input-param, show in /proc/interrupts
 * @dev_id,
 */
#endif /* >>== interrupt basic ==<< */

#if 1 /* <<== kernel object ==>> */
struct cdev *device = container_of(kp, struct cdev, kobj);
#endif /* <<== kernel object ==>> */
