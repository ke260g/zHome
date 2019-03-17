#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define SEM_KEY_PATH "/home/ll"

int main( int argc, char **argv ) {
    int semid;
    int retval;


    key_t sem_key = ftok(SEM_KEY_PATH, 2);
    semid = semget(sem_key, 1, 0644);
    if(semid == -1) {
        perror("semget: ");
    }

    struct sembuf semoparray = {.sem_num = 0, .sem_op = -1, .sem_flg = SEM_UNDO, };
    retval = semop(semid, &semoparray, 1);

    printf("pid: %10d,", getpid());
    printf("semop return: %5d,", retval);
    printf("Hello, Darkness\n");
    sleep(10);

    return 0;
}
