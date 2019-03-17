#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define SEM_KEY_PATH "/home/ll"

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
} semun_arg;

void print_semid_ds(struct semid_ds *buf) {
    printf("sem_nsems: %d\n", buf->sem_nsems);
    printf("sem_otime: %d\n", buf->sem_otime);
    printf("sem_ctime: %d\n", buf->sem_ctime);
}

int main( int argc, char **argv ) {
    int semid;
    int retval;

    printf("pid: %d\n", getpid());

    key_t sem_key = ftok(SEM_KEY_PATH, 2);
    semid = semget(sem_key, 1, 0644 | IPC_CREAT);
    if(semid == -1) {
        perror("semget: ");
    }

#if 1 /* debug */
    // get sem[0]'s value
    retval = semctl(semid, 0, GETVAL);
    printf("semval: %d\n", retval);
#endif /* debug */

    // set sem[0] value
    semun_arg.val = 1;
    retval = semctl(semid, 0, SETVAL, semun_arg);
    printf("setval return: %d\n", retval);

    struct semid_ds *buf = (struct semid_ds *)malloc(sizeof(struct semid_ds));
    semun_arg.buf = buf;

    retval = semctl(semid, 0, IPC_STAT, semun_arg);
    if(retval == 0) {
        print_semid_ds(semun_arg.buf);
    } else {
        perror("semctl: ");
    }


#if 1 /* debug */
    // get sem[0]'s value
    retval = semctl(semid, 0, GETVAL);
    printf("semval: %d\n", retval);
#endif /* debug */

    free(buf);
    return 0;
}
