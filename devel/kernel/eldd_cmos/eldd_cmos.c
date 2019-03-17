/* a virtual device example from eldd, named cmos */
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

/*
 * access CMOS via two I/O address, indexReg and dataPointer
 *
 * register layout on the cmos:
 * CMOS_BANK0_INDEX_PORT, specify the desired CMOS bank0 offset in this register
 * CMOS_BANK0_DATA_PORT, Read/Write data from/to the address specified in bank0
 * CMOS_BANK1_INDEX_PORT
 * CMOS_BANK1_DATA_PORT
 */

#define NUM_CMOS_BANKS          2
#define CMOS_BANK_SIZE          (0xFF*8)
#define DEVICE_NAME             "cmos"
#define CMOS_BANK0_INDEX_PORT   0x70
#define CMOS_BANK0_DATA_PORT    0x71
#define CMOS_BANK1_INDEX_PORT   0x72
#define CMOS_BANK1_DATA_PORT    0x73

static dev_t cmos_dev_number;   /* Allotted device number */
static struct class *cmos_class; /* Tie with the device model */

/* Per-device (per-bank) structure */
struct cmos_dev {
    unsigned short current_pointer; /* Current pointer within the bank */
    unsigned int size;              /* Size of the bank */
    int bank_number;                /* CMOS bank number */
    struct cdev cdev;               /* The cdev structure */
    char name[10];                  /* Name of I/O region */
    /* ... */                       /* Mutexes, spinlocks, wait
                                       queues, .. */
    char priv_str[20];
};

static int cmos_open(struct inode *inode, struct file *filp) {
    struct cmos_dev *cmos_devp;

    printk(DEVICE_NAME": cmos open().\n");

    /* obtain the cmos_dev object, created and init-ed in cmos_init() */
    cmos_devp = container_of(inode->i_cdev, struct cmos_dev, cdev);
    filp->private_data = cmos_devp; /* can be passed to _read(), _write() */

    /* more init codes for cmos_dev object
     * ... init codes ...
     */

    return 0;
}

static int cmos_release(struct inode *inode, struct file *filp) {
    struct cmos_dev *cmos_devp;

    printk(DEVICE_NAME": cmos close().\n");
    /* obtain the cmos_dev object */
    cmos_devp = filp->private_data;

    /* release some member in it
     * ... release codes ...
     */
    return 0;
}

static ssize_t cmos_read(struct file *filp,
        char __user *buf,
        size_t conut, loff_t *offset) {
    /* obtain the cmos_dev object */
    struct cmos_dev *cmos_devp;
    cmos_devp = filp->private_data;
    /* communicate the object and userspace-memory */
    return 0;
}

static ssize_t cmos_write(struct file *filp,
        const char __user *buf,
        size_t count, loff_t *offset) {
    /* obtain the cmos_dev object */
    struct cmos_dev *cmos_devp;
    cmos_devp = filp->private_data;
    /* communicate the object and userspace-memory */
    return 0;
}

/* File operations structure, Defined in linux/fs.h */
static struct file_operations cmos_fops = {
    .owner    =   THIS_MODULE,      /* Owner */
    .open     =   cmos_open,        /* Open method */
    .release  =   cmos_release,     /* Release method */
    .read     =   cmos_read,        /* Read method */
    .write    =   cmos_write,       /* Write method */
    // .llseek   =   cmos_llseek,      /* Seek method */
    // .ioctl    =   cmos_ioctl,       /* Ioctl method */
};

#if 0
static unsigned char addr_ports[NUM_CMOS_BANKS] = { CMOS_BANK0_INDEX_PORT, CMOS_BANK1_INDEX_PORT, };
static unsigned char data_ports[NUM_CMOS_BANKS] = { CMOS_BANK0_DATA_PORT, CMOS_BANK1_DATA_PORT,};
#endif

/* module_init() char device driver initialization, not in order
 * 1. request allocation of device major number
 * 2. allocate memory for the per device structure
 * 3. connecting the `fpos'(open(), read(), ...) with struct cdev
 * 4. associating the device major number with driver's cdev
 * 5. create device-nodes under /dev, /sys,
 * 6. initializing the hardware */

static int __init cmos_init(void) {
    int i, err;
    struct cmos_dev *cmos_devp;
    /* [1] <<== Request dynamic allocation of a device major number ==>> */
    err = alloc_chrdev_region(&cmos_dev_number, 0, NUM_CMOS_BANKS, DEVICE_NAME);
    if (err) {
        printk(KERN_DEBUG "Can't register device\n");
        return -1;
    }
    printk(DEVICE_NAME": major number is %d.\n", MAJOR(cmos_dev_number));
    /* [1] >>== Request dynamic allocation of a device major number ==<< */

    /* [2] <<== create dir /sys/DEVICE_NAME ==>> */
    cmos_class = class_create(THIS_MODULE, DEVICE_NAME);
    /* [2] >>== create dir /sys/DEVICE_NAME ==<< */

    for(i = 0; i < NUM_CMOS_BANKS; i++) {
        /* [3] <<== init the cmos_dev object ==>> */
        cmos_devp = kmalloc(sizeof(struct cmos_dev), GFP_KERNEL);
        if (!cmos_devp) {
            printk("Bad Kmalloc\n");
            return -1;
        }
        cmos_devp->cdev.owner = THIS_MODULE;
        /* more init cmos_dev object codes */
        /* [3] >>== init the cmos_dev object ==<< */

        /* [4] <<== init and add to char device ==>> */
        cdev_init(&cmos_devp->cdev, &cmos_fops);
        err = cdev_add(&cmos_devp->cdev, (cmos_dev_number + i), 1);
        if(err) {
            printk(KERN_DEBUG "Can't add the cdev\n");
            return -1;
        }
        /* [4] >>== init and add to char device ==<< */


        /* [5] <<== create device-nodes and under /dev ==>> */
        /* under /sys/DEVICE_NAME   <- specified by @cmos_class
         * nodes are DEVICE_NAME0, DEVICE_NAME1, ... <- specified by @fifth-param
         * cdev minor-number is defined in [@third-param - major-number] */
        device_create(cmos_class, NULL, (cmos_dev_number + i), NULL, DEVICE_NAME"%d", i);
        /* [5] >>== create device-nodes and under /dev ==<< */
    }

    return 0;
}

static void __exit cmos_cleanup(void) {
    int i; /* common counter */
    /* Release the major number */
    unregister_chrdev_region(cmos_dev_number, NUM_CMOS_BANKS);

    /* remove /sys/DEVICE_NAME/{DEVICE_NAME0, DEVICE_NAME1}
     * remove /dev/{DEVICE_NAME0, DEVICE_NAME1} */

    for(i = 0; i < NUM_CMOS_BANKS; i++)
        device_destroy(cmos_class, (cmos_dev_number + i));

    /* remove dir /sys/DEVICE_NAME */
    class_destroy(cmos_class);
    return;
}

module_init(cmos_init);
module_exit(cmos_cleanup);
MODULE_LICENSE("GPL");
