```c
static struct cdev *my_cdev;

static char *dev_name;

static unsigned minor_basenumber = 0;
static unsigned minor_count = 4;
static dev_t mydevno;

static struct file_operations myfops = { };

static int irq_dev_id[4];
struct irq_desc {
    int irq;                /* irq-vector */
    unsigned long flags;    /* user-defined trigger-mode */
    char *name;             /* interrupt name */
};
struct irq_desc irqs_ary[] = {
    {IRQ_RESOURCE_1, IRQF_, "irq1"},
    {IRQ_RESOURCE_2, IRQF_, "irq2"},
    {IRQ_RESOURCE_3, IRQF_, "irq3"},
};
/* irq-vector is defined in <mach/irqs.h>, <plat/irqs.h> */
/* available mode is defined in <linux/interrupt.h>*/

static irqreturn_t interrupt_handler(int irq,
    void *dev_id) {
    switch(irq) {
        case IRQ_RESOURCE_1:
            /* related irq handle */;
            break;
        case IRQ_RESOURCE_2:
            ;
            break;
        case IRQ_RESOURCE_3:
            ;
            break;
    }
}

static int __init startup_func(void) {
    alloc_chrdev_region(&my_devno,
            minor_basenumber, minor_count,
            dev_name);
    /* to allocate a major device number
     * 'buttons_devno' is the output-param
     * tell the kernel here is a new-char-device
     * and his-id is 'my_devno' */

     my_cdev = cdev_alloc();
     /* allocate a char-device */

     my_cdev->owner = THIS_MODULE;
     my_cdev->dev = my_devno;
     my_cdev->ops = myfops;
     /* to implement a char-device,
      * ->dev specific major-num,
      * ->ops specific core implement handler
      * ->owner = THIS_MODULE is recommanded */

     cdev_add(my_cdev, my_devno);
     /* add the cdev-implement to the related 'my_devno',
      * to allow kernel find the what this char-device is */

     for(int i = 0; i < 4; i++)
         request_irq(irqs_ary[i].irq,   /* irq-vector, defined in <mach/irqs.h>, <plat/irqs.h> */
                 interrupt_handler,     /* register interrupt_handler, user-define */
                 irqs_ary[i].flags,     /* irq-mode, <linux/interrupt.h> */
                 irqs_ary[i].name,      /* irq-name, user-define, will be displayed in the /proc/interrupts */
                 (void *)&irqs_ary[i]   /* output-param, obtain the irq-id */
                 );
}

static void __exit buttons_cleanup(void) {
    for(int i = 0; i < 4; i++) {
        free_irq(irqs_ary[i].irq, (void *)&irq_dev_id[i]);
    }
    cdev_del(my_cdev);
    unregister_chrdev_region(my_devno, minor_count);
}
```
