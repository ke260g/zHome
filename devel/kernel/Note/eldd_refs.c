/* well-known char device major number
 * define on Documentation/device.txt */
struct page pg; /* <linux/mm_types.h> */
struct timer_list trl;
struct timeval tv;
spinlock_t splk;
struct semaphore sema;
struct mutex mtx; /* new interface that replaces semaphore */
rwlock_t rwl;

/* <<== jiffies compare ==>> */
/* HZ: Number of times the system timer ticks in 1 second */
int now_jiffies = HZ;
time_after(a, b);
time_after_eq(a, b);
time_before(a, b);
time_before_eq(a, b);

/* Resumes execution if a specified condition
 * becomes true or if a timeout occurs */
wait_event_timeout();

/* <<== timer ==>> */
DEFINE_TIMER();
init_timer();
add_timer();
timer_pending();

/* <<== exec sync tools ==>> */
// [1] spin lock
spin_lock();    /* accquire */
spin_unlock();  /* release */
spin_lock_irqsave();
/* Saves interrupt state, disables interrupts and
 * preemption on local CPU, and locks their critical
 * section to regulate access by other CPUs */
spin_unlock_irqrestore();
/* Restores interrupt state and preemption and
 * releases the lock */

// [2] mutex
DEFINE_MUTEX(); /* declare and init */
mutex_init();   /* init */
mutex_lock();   /* accquire */
mutex_unlock(); /* release */

// [3] rwlock
read_lock(); read_trylock();
read_lock_bh();
read_lock_irq();
read_lock_irqsave();
read_unlock();
read_unlock_irq() read_unlock_irqrestore();
write_lock(); write_trylock();
write_trylock_irqsave();
write_lock_bh();
write_lock_irq();
write_lock_irqsave();
write_unlock();
write_unlock_irq(); write_unlock_irqrestore();

// [4] sema, old interface, use mutex instead
sema_init();    /* init sema */
up();           /* accquire */
down();         /* release */

/* <<== atomic ==>> */
atomic_inc();
atomic_inc_and_test();
atomic_dec()
atomic_dec_and_test();
clear_bit();
set_bit();
test_bit();
test_and_set_bit();

/* <<== linked list ==>> */
INIT_LIST_HEAD();
list_add();
list_add_tail();
list_del();
list_replace();
list_entry();
list_for_each_entry(); /* or */ list_for_each_entry_safe();
list_empty();
list_splice();

/* <<== delay and sleep ==>> */
udelay();
mdelay();

/* <<== memory allocate ==>> */
kmalloc();  /* physically contiguoues memory */
kzalloc();  /* obtain zeroed kmalloced memory */
kfree();

/* <<== kernel thread ==>> */
kernel_thread(int (*fn)(void *), void *arg, unsigned long flags);
DECLARE_WAITQUEUE(wait, current);
daemonsize("thread_name");
allow_signal(SIGKILL);
signal_pending(current);
set_current_state(TASK_); /* _RUNNING, _INTERRUPTIBLE, _STOPPED, _TRACED */

/* <<== irq interface ==>> */
request_irq();
free_irq();
disable_irq();
disable_irq_nosync();
enable_irq();

open_softirq();
softirq_init();
raise_softirq_irqoff();
raise_softirq();

/* <<== tasklets ==>> */
struct tasklet_struct tklt;
tasklet_init();
tasklet_schedule();
tasklet_enable();
tasklet_disable();
tasklet_disable_nosync();
tasklet_kill();
tasklet_kill_immediate();

/* <<== kobject ==>> */
#include<linux/kobject.h>
struct kobject { };
struct kobj_type { };
struct kset { };
// kobject interface
kobject_init();
kobject_add();
kobject_init_and_add();
kobject_del();
kobject_create();
kobject_create_and_add();
kobject_rename();
kobject_move();
kobject_get();
kobject_namespace();
kobject_get_path();
// kobj_type
get_ktype();
// kset interface
kset_init();
kset_register();
kset_unregister();
kset_create_and_add();
to_kset();
kset_get();
kset_put;
kset_find_obj();

/* <<== driver, device, class ==>> */
#include<linux/device.h>
struct class { };
struct device_driver { };
struct bus_type { };
struct device { };

class_create();
class_destroy();
class_create_file_ns();
class_remove_file_ns();

device_create();
device_destroy();
device_create_file();
device_remove_file()
device_remove_file_self();

driver_create_file();
driver_remove_file();
driver_find_device();
driver_for_each_device();
