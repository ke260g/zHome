#include<linux/fs.h>
#include<linux/device.h>
#include<linux/kobject.h>
#include<linux/module.h>
#include<linux/cdev.h>
#include<linux/err.h>
#include<linux/sched.h>
#include<linux/slab.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/major.h>

#define DEVICE_NAME             "xxxx"

static dev_t xxxx_dev_number;   /* Allotted device number */
static struct class *xxxx_class;       /* Tie with the device model */
#define xxxx_number (1)

/* Per-device (per-bank) structure */
struct xxxx_dev {
    struct cdev cdev;               /* The cdev structure */
};

static int xxxx_open(struct inode *inode, struct file *filp) {
    struct xxxx_dev *xxxx_devp;

    printk(DEVICE_NAME": xxxx open().\n");

    /* obtain the xxxx_dev object, created and init-ed in xxxx_init() */
    xxxx_devp = container_of(inode->i_cdev, struct xxxx_dev, cdev);
    filp->private_data = xxxx_devp; /* can be passed to _read(), _write() */

    /* more init codes for cmos_dev object
     * ... init codes ...
     */

    return 0;
}

static int xxxx_release(struct inode *inode, struct file *filp) {
    struct xxxx_dev *xxxx_devp;

    printk(DEVICE_NAME": xxxx close().\n");
    /* obtain the xxxx_dev object */
    xxxx_devp = filp->private_data;

    /* release some member in it
     * ... release codes ...
     */
    return 0;
}

static ssize_t xxxx_read(struct file *filp,
        char __user *buf,
        size_t conut, loff_t *offset) {
    /* obtain the xxxx_dev object */
    struct xxxx_dev *xxxx_devp;
    xxxx_devp = filp->private_data;
    /* communicate the object and userspace-memory */

    return 0;
}

static ssize_t xxxx_write(struct file *filp,
        const char __user *buf,
        size_t count, loff_t *offset) {
    /* obtain the xxxx_dev object */
    struct xxxx_dev *xxxx_devp;
    xxxx_devp = filp->private_data;
    /* communicate the object and userspace-memory */
    return 0;
}

/* File operations structure, Defined in linux/fs.h */
static struct file_operations xxxx_fops = {
    .owner    =   THIS_MODULE,      /* Owner */
    .open     =   xxxx_open,        /* Open method */
    .release  =   xxxx_release,     /* Release method */
    .read     =   xxxx_read,        /* Read method */
    .write    =   xxxx_write,       /* Write method */
    // .llseek   =   xxxx_llseek,      /* Seek method */
    // .ioctl    =   xxxx_ioctl,       /* Ioctl method */
};


static int __init xxxx_init(void) {
    int err;
    struct xxxx_dev *xxxx_devp;
    /* [1] <<== Request dynamic allocation of a device major number ==>> */
    err = alloc_chrdev_region(&xxxx_dev_number, 0, xxxx_number, DEVICE_NAME);
    if (err) {
        printk(KERN_DEBUG "Can't register device\n");
        return -1;
    }
    printk(DEVICE_NAME": major number is %d.\n", MAJOR(xxxx_dev_number));
    /* [1] >>== Request dynamic allocation of a device major number ==<< */

    /* [2] <<== init the xxxx_dev object ==>> */
    xxxx_devp = kmalloc(sizeof(struct xxxx_dev), GFP_KERNEL);
    if (!xxxx_devp) {
        printk("Bad Kmalloc\n");
        return -1;
    }
    xxxx_devp->cdev.owner = THIS_MODULE;
    /* more init xxxx_dev object codes */
    /* [2] >>== init the xxxx_dev object ==<< */

    /* [3] <<== init and add to char device ==>> */
    cdev_init(&xxxx_devp->cdev, &xxxx_fops);
    err = cdev_add(&xxxx_devp->cdev, (xxxx_dev_number + 0), 1);
    if(err) {
        printk(KERN_DEBUG "Can't add the cdev\n");
        return -1;
    }
    /* [3] >>== init and add to char device ==<< */

    /* [4] <<== create dir /sys/DEVICE_NAME ==>> */
    xxxx_class = class_create(THIS_MODULE, DEVICE_NAME);
    /* [4] >>== create dir /sys/DEVICE_NAME ==<< */

    /* [5] <<== create device-nodes and under /dev ==>> */
    /* under /sys/DEVICE_NAME   <- specified by @xxxx_class
     * nodes are DEVICE_NAME0, DEVICE_NAME1, ... <- specified by @fifth-param
     * cdev minor-number is defined in [@third-param - major-number] */
    device_create(xxxx_class, NULL, (xxxx_dev_number + 0), NULL, DEVICE_NAME"%d", 0);
    /* [5] >>== create device-nodes and under /dev ==<< */

    return 0;
}

static void __exit xxxx_cleanup(void) {

    /* Release the major number */
    unregister_chrdev_region(xxxx_dev_number, xxxx_number);

    /* remove /sys/DEVICE_NAME/{DEVICE_NAME0, DEVICE_NAME1}
     * remove /dev/{DEVICE_NAME0, DEVICE_NAME1} */
    device_destroy(xxxx_class, (xxxx_dev_number + 0));
    device_destroy(xxxx_class, (xxxx_dev_number + 1));

    /* remove dir /sys/DEVICE_NAME */
    class_destroy(xxxx_class);
    return;
}

module_init(xxxx_init);
module_exit(xxxx_cleanup);
MODULE_LICENSE("GPL");
