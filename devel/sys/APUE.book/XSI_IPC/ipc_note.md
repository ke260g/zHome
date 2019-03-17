# ipc Catalog
pipe, fifo, message_queues, semaphores,
xsi_ipc_key, shared_memory, posix_semaphores

---
### pipe
```c
int fd[2];
pipe(int fd[2]); /* @fd is the output param */
/* fd[0] is open for reading,
 * fd[1] is open for writing */

FILE *popen(const char *cmdstring, const char *type);
pclose(FILE *fp);
/* @type is either "w" or "r",
 * @cmdstring is like
 * $ sh -c 'cmdstring'
 * in command line */
```

##### a coprocess example
```c
```

---
### fifo
```c
mkfifo(const char *path, mode_t mode);
mkfifoat(int fd, const char *path, mode_t mode);
/* @mode is macro like S_IRUSR, S_I* */
```

---
### xsi_ipc_key
```c
#include<sys/ipc.h>
key_t ftok(const char *path, int id);
/* to create a new key_t,
 * @path and @id is user-defined */
```
+ ipc_id is for user
+ key_t is used in kernel
+ msq, sem, shm are so-called ipc-object

---
### shared_memory
```c
#include<sys/shm.h>
int shmget(key_t key, size_t size, int flag);
/* @key can be IPC_PRIVATE, return shared_memory_id */

shmctl(int shmid, int cmd, struct shmid_ds *buf);
void *shmat(int shmid, const void *addr, int flag);
shmdt(const void *addr);
/* @shmid is returned by `shmget()'
 * @cmd is one of IPC_STAT, IPC_SET, IPC_RMID
 * @flag can be set SHM_LOCK, SHM_UNLOCK, SHM_RND
 * @addr in `shmat()' is usually setted to NULL,
 * @addr in `shmdt()' is returned by `shmat()' */
```
---
### message_queues
```c
#include<sys/msg.h>
int msgget(key_t key, int flag);
/* @key can be IPC_PRIVATE, return message_queues_id */

int msgctl(int msqid, int cmd,
        struct msqid_ds *buf);
int msgsnd(int msqid, const void *ptr,
        size_t nbytes, int flag);
ssize_t msgrcv(int msqid, void *ptr,
        size_t nbytes, long type, int flag);

/* @msqid is returned by `msgget()'
 * @cmd is one of IPC_STAT, IPC_SET, IPC_RMID
 * @flag can be set to IPC_NOWAIT for noblocked
 * @type in `msgrcv()'
 *       == 0, recieve first message;
 *       > 0, recieve relative message-type;
 *       < 0, recieve the first message,
 *            if its message-type <= (-type);
 * @ptr points to a (long int) that contains the
 *      positive integer message-type, and it is immediately followed by
 *      the message data.  */
struct my_mesg {
    /* self-implement, convient message structure */
    long mtype;
    char mtext[nbytes]; /* message data, of length @nbytes */
};
```
