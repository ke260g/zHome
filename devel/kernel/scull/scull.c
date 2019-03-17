#include<linux/fs.h>

#include<asm/param.h>
#include<linux/errno.h>
#include<linux/kernel.h>
#include<linux/sched.h>
#include<linux/types.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/semaphore.h>
#include<linux/signal.h>
#include<linux/errno.h>
#include<asm/uaccess.h> /* user access */
#include"scull.h"
#include"scull_ioctl.h"

static const int scull_major;   /* waited to be alloced */
static const int scull_minor = 0;
static const int scull_nr_devs = 4;
static int scull_quantum = SCULL_QUANTUM;
static int scull_nr_qsets = SCULL_NR_QSETS;

static struct scull_dev scull0;
static dev_t devno;

static int scull_trim(struct scull_dev *dev) {
    /* release the whole device data */
    struct scull_qset *next,
                      *dptr; /* data-pointer */
    int qset = dev->qset; /* "dev" is not null */
    int i;

    if(dev == NULL)
        return -1;

    /* data-pointer is the first listitem */
    for(dptr = dev->data; dptr; dptr = next) {
        /* ergod the qset-link-list */
        if(dptr->data) {
            /* ergod the quantum-array */
            for(i = 0; i < qset; i++)
                kfree(dptr->data);
            dptr->data = NULL;
        }
        next = dptr->next;
        kfree(dptr);
    }
    dev->size = 0;
    dev->quantum = scull_quantum;
    dev->qset = scull_nr_qsets;
    dev->data = NULL;
    return 0;
}

static struct scull_qset *scull_follow(struct scull_dev *dev, int item) {
    struct scull_qset *qset = NULL;
    return qset;
}

#if 0
static loff_t scull_llseek(struct file *file,
        loff_t off,
        int value) { }
#endif

static loff_t scull_llseek(struct file *filp, loff_t off, int whence)
{
    struct scull_dev *dev = filp->private_data;
    loff_t newpos;
    switch(whence) {
        case 0: /* SEEK_SET */
            newpos = off;
            break;
        case 1: /* SEEK_CUR */
            newpos = filp->f_pos + off;
            break;
        case 2: /* SEEK_END */
            newpos = dev->size + off;
            break;
        default: /* can't happen */
            return -EINVAL;
    }

    if(newpos < 0)
        return -EINVAL;
    filp->f_pos = newpos;
    return newpos;
}

static long scull_ioctl(struct file *filp,
        unsigned int cmd,
        unsigned long arg) {
    int err, tmp, retval;
    /* it can't detect whether user pass the third argument */

    err = 0;
    retval = 0;
    /*
     * extract the type and number bitfields, and don't decode
     * wrong cmds: return ENOTTY(inappropriate ioctl) before access_ok()
     */
    if(_IOC_TYPE(cmd) != SCULL_IOC_MAGIC)
        return -ENOTTY;
    if(_IOC_NR(cmd) > SCULL_IOC_MAGIC)
        return -ENOTTY;
    /*
     * the direction is a bitmask, and VERIFY_WRITE catches R/W
     * transfers. `Type' is user-oriented, while
     * access_ok is kernel-oriented, so the concept of
     * "read" and "write" is reversed
     */
#if 0 /* access_ok() may be always return `1' */
    if(_IOC_DIR(cmd) & _IOC_READ)
        err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
    else if(_IOC_DIR(cmd) & _IOC_WRITE)
        err = !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
    if(err)
        return -EFAULT;
#endif

    switch(cmd) {
        case SCULL_IOCRESET:
            scull_quantum = SCULL_QUANTUM;
            scull_nr_qsets = SCULL_NR_QSETS;
            break;
        case SCULL_IOCSQUANTUM: /* Set: arg points to the value */
            if (! capable (CAP_SYS_ADMIN))
                return -EPERM;
            retval = copy_from_user(&scull_quantum, (int __user *)arg, sizeof(int));
            break;
        case SCULL_IOCTQUANTUM: /* Tell: arg is the value */
            if (! capable (CAP_SYS_ADMIN))
                return -EPERM;
            retval = copy_to_user((int __user *)arg, &scull_quantum, sizeof(int));
            break;
        case SCULL_IOCQQUANTUM: /* Query: return it (it's positive) */
            return scull_quantum;
        case SCULL_IOCXQUANTUM: /* eXchange: use arg as pointer */
            if (! capable (CAP_SYS_ADMIN))
                return -EPERM;
            tmp = scull_quantum;
            retval = copy_from_user(&scull_quantum, (int __user *)arg, sizeof(int));
            if (retval == 0)
                retval = copy_to_user((int __user *)arg, &tmp, sizeof(int));
            break;
        case SCULL_IOCHQUANTUM: /* sHift: like Tell + Query */
            if (! capable (CAP_SYS_ADMIN))
                return -EPERM;
            tmp = scull_quantum;
            scull_quantum = arg;
            return tmp;
        default:  /* redundant, as cmd was checked against MAXNR */
            return -ENOTTY;
    }

    return retval;
}

static ssize_t scull_read(struct file *filp,
        char __user *buf, size_t count, loff_t *f_pos) {
    struct scull_dev *dev = filp->private_data;
    struct scull_qset *dptr; /* the first listitem */
    int quantum = dev->quantum,
        qset = dev->qset;
    int item,   /* which link-list item is to read */
        rest,   /* offset in the item */
        s_pos,  /* dptr->data[s_pos] */
        q_pos;  /* dptr->data[s_pos] + q_pos */
    int itemsize = quantum * qset; /* how many bytes in the listitems */

    ssize_t retval = 0;

    if(down_interruptible(&dev->sem))
        return -ERESTARTSYS;
    if(*f_pos >= dev->size)
        goto out;
    if(*f_pos + count > dev->size)
        count = dev->size - *f_pos;

    /* find listitem, qset index, and offset in the quantum */
    item = (long)*f_pos / itemsize;
    rest = (long)*f_pos % itemsize;
    s_pos = rest / quantum;
    q_pos = rest % quantum;

    /* follow the list up to the right position */
    dptr = scull_follow(dev, item);
    if(dptr == NULL || !dptr->data || !dptr->data[s_pos])
        goto out; /* don't fill holes */

    /* read only up to the end of this quantum */
    if(count > quantum - q_pos)
        count = quantum - q_pos;

    if(copy_to_user(buf, dptr->data[s_pos] + q_pos, count)) {
        retval = -EFAULT;
        goto out;
    }
    *f_pos += count;
    retval = count;
out:
    up(&dev->sem);
    return retval;
}

static ssize_t scull_write(struct file *filp,
        const char __user *buf,
        size_t count,
        loff_t *f_pos) {
    struct scull_dev *dev = filp->private_data;
    struct scull_qset *dptr;
    int quantum = dev->quantum,
        qset = dev->qset;
    int itemsize = quantum * qset;
    int item, rest, s_pos, q_pos;
    ssize_t retval = -ENOMEM;
    if(down_interruptible(&dev->sem))
        return -ERESTARTSYS;

    /* find listitem, qset index and offset in the quantum */
    item = (long)*f_pos / itemsize;
    rest = (long)*f_pos % itemsize;
    s_pos = rest / quantum;
    q_pos = rest % quantum;

    /* follow the list up to the right position */
    dptr = scull_follow(dev, item);
    if(dptr == NULL)
        goto out;
    if(!dptr->data) {
        dptr->data = kmalloc(qset * sizeof(char *), GFP_KERNEL);
        if(!dptr->data)
            goto out;
        memset(dptr->data, 0, qset * sizeof(char *));
    }
    if(!dptr->data[s_pos]) {
        dptr->data[s_pos] = kmalloc(quantum, GFP_KERNEL);
        if(!dptr->data[s_pos])
            goto out;
    }

    /* write only up to the end of this quantum */
    if(count > quantum - q_pos)
        count = quantum - q_pos;
    if(copy_from_user(dptr->data[s_pos] + q_pos, buf, count)) {
        retval = -EFAULT;
        goto out;
    }
    *f_pos += count;
    retval = count;
    /* update the size */
    if(dev->size < *f_pos)
        dev->size = *f_pos;
out:
    up(&dev->sem);
    return retval;
}

static int scull_open(struct inode *inode,
        struct file *filp) {
    struct scull_dev *dev;      /* device info */
    int retval;
    //  send_sig(SIGUSR1, current, 0);

    /* find the appropriate device structure */
    dev = container_of(inode->i_cdev, struct scull_dev, cdev);
    filp->private_data = dev;   /* for other methods */
    /* now trim to 0 the length of the device if open was write-only */

    if((filp->f_flags & O_ACCMODE) == O_WRONLY){
        scull_trim(dev);  /* ignore error */
    }

    if((filp->f_flags & O_NONBLOCK) == O_NONBLOCK) {
        retval = down_trylock(&dev->sem);
        if(retval) {
            printk("retval is %d\n", retval);
            retval = -EBUSY;
        }
    } else {
        // retval = down_interruptible(&dev->sem);
        printk("line:%d, jiffies is %ld.\n", __LINE__, (long)get_jiffies_64());
        retval = down_timeout(&dev->sem, 4 * HZ);
        printk("line:%d, jiffies is %ld.\n", __LINE__, (long)get_jiffies_64());
    }

    if(retval) {
        printk(KERN_INFO"scull failed to open, pid:%d\n", current->pid);
        return retval;
    }
    printk(KERN_INFO"scull has been opened, major:%d, minor:%d, pid:%d\n",
            imajor(inode), iminor(inode), current->pid);
    return 0; /* success */
}

static int scull_release(struct inode *inode,
        struct file *filp) {
    struct scull_dev *dev;      /* device info */
    dev = filp->private_data;
    up(&dev->sem);
    printk(KERN_INFO"scull has been closed.\n");
    return 0;
}

static struct file_operations scull_fops = {
    //.owner = THIS_MODULE,
    .llseek = scull_llseek,
    .read = scull_read,
    .write = scull_write,
    .unlocked_ioctl = scull_ioctl,
    //.compat_ioctl = scull_ioctl, /* I don't know why it will not be invoked */
    .open = scull_open,
    .release = scull_release,
};

static void scull_setup_cdev(struct scull_dev *dev,
        int index) {
    int err;
#if 0 /* way */
    dev_t dev = MKDEV(scull_major, scull_minor);
    err = register_chrdev_region(dev, scull_nr_devs, "scull");
#else
    err = alloc_chrdev_region(&devno, scull_minor,
            scull_nr_devs, "scull");
#endif
    if(err) {
        /* error handler */
        printk(KERN_WARNING"scull: can't get major %d\n", scull_major);
        return;
    }
#if 0 /* obtain a standalone cdev */
    struct cdev *my_cdev = cdev_alloc();
    my_cdev->ops = &my_ops;
    err = cdev_add(my_cdev, devno, 1);
#else
    cdev_init(&(dev->cdev), &scull_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->cdev.ops = &scull_fops;
    err = cdev_add(&dev->cdev, devno, 1);
#endif
    if(err)
        printk(KERN_ALERT "Error %d add scull%d\n", err, index);
    sema_init(&dev->sem, 1);
}

static int __init init_func(void) {
    printk(KERN_ALERT "This is init_func\n");
    scull_setup_cdev(&scull0, 0);

    printk("============================\n");
    printk("Scull's Major-Dev-Num is %d\n", MAJOR(devno));
    printk("Scull's Minor-Dev-Num is %d\n", MINOR(devno));
    return 0;
}

static void __exit cleanup_func(void) {
    printk("This is cleanup_func\n");

#if 0 /* test for the printk prompt */
    printk(KERN_EMERG "KERN_EMERG\n");
    printk(KERN_ALERT "KERN_ALERT\n");
    printk(KERN_CRIT "KERN_CRIT\n");
    printk(KERN_ERR "KERN_ERR\n");
    printk(KERN_WARNING "KERN_WARNING\n");
    printk(KERN_NOTICE "KERN_NOTICE\n");
    printk(KERN_INFO "KERN_INFO\n");
    printk(KERN_CONT "KERN_CONT\n");
#endif
    cdev_del(&scull0.cdev);
    unregister_chrdev_region(devno, scull_nr_devs);
}

module_init(init_func);
module_exit(cleanup_func);
