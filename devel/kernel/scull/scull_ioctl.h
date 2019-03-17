#ifndef __SCULL_IOCTL_H__
#define __SCULL_IOCTL_H__

/* ioctl() cmd */
/* use 'k' as magic number */
#define SCULL_IOC_MAGIC 'k'
/* Please use a different 8-bit number in your code */
#define SCULL_IOCRESET _IO(SCULL_IOC_MAGIC, 0)

/*
 * S means "Set": through a ptr,
 * T means "Tell": directly with the argument value
 * G means "Get": reply by setting through a pointer
 * Q means "Query": response is on the return value
 * X means "eXchange": switch G and S at atomically
 * H means "sHift": switch T and Q atomically
 */
#define SCULL_IOCSQUANTUM _IOW(SCULL_IOC_MAGIC, 1, int) /* io set quantum */
#define SCULL_IOCSQSET _IOW(SCULL_IOC_MAGIC, 2, int) /* io set qset */
#define SCULL_IOCTQUANTUM _IO(SCULL_IOC_MAGIC, 3) /* io tell quantum */
#define SCULL_IOCTQSET _IO(SCULL_IOC_MAGIC, 4) /* io tell qset */
#define SCULL_IOCGQUANTUM _IOR(SCULL_IOC_MAGIC, 5, int) /* ioc get quantum */
#define SCULL_IOCGQSET _IOR(SCULL_IOC_MAGIC, 6, int) /* ioc get qset */
#define SCULL_IOCQQUANTUM _IO(SCULL_IOC_MAGIC, 7) /* ioc query quantum */
#define SCULL_IOCQQSET _IO(SCULL_IOC_MAGIC, 8) /* ioc query qset */
#define SCULL_IOCXQUANTUM _IOWR(SCULL_IOC_MAGIC, 9, int)
#define SCULL_IOCXQSET _IOWR(SCULL_IOC_MAGIC, 10, int)
#define SCULL_IOCHQUANTUM _IO(SCULL_IOC_MAGIC, 11)
#define SCULL_IOCHQSET _IO(SCULL_IOC_MAGIC, 12)

#define SCULL_IOC_MAXNR 14

#endif /* __SCULL_IOCTL_H__ */
