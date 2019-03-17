#ifndef __SCULL_H__
#define __SCULL_H__

#include<linux/semaphore.h>
#include<asm/ioctl.h>

#define SCULL_QUANTUM (4)
#define SCULL_NR_QSETS (4)

struct scull_qset {
    void **data;
    struct scull_qset *next;
};

struct scull_dev {
    struct scull_qset *data;  /* ptr to first quantum set */
    int quantum;                /* the current quantum size */
    int qset;                   /* the current array size */
    unsigned long size;         /* amount of data stored here */
    unsigned int access_key;    /* used by scull-uid and scull-priv */
    struct semaphore sem;       /* mutual exclusion semaphore */
    struct cdev cdev;           /* char device structure */
};

#endif
