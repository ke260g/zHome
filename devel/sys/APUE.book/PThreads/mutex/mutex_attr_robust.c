#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<sys/shm.h>

static int shm_id;
static pid_t pid;
static pthread_mutex_t *com_mutex_pt;
static pthread_mutexattr_t attr;

int main(int argc, char **argv) {
    int i,
        ret;

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_ROBUST);

    shm_id = shmget(IPC_PRIVATE,
            sizeof(pthread_mutex_t), S_IRUSR | S_IWUSR);
    com_mutex_pt = shmat(shm_id, NULL, 0);
    if(com_mutex_pt == (void *)-1) {
        fprintf(stderr, "error to shmat().\n");
        abort();
    }

    pthread_mutex_init(com_mutex_pt, &attr);
    printf("Begin to fork.\n");

    if((pid = fork()) < 0)
        abort();
    else if(pid > 0) { /* parent */
        printf("\tParent begins to lock the mutex.\n");
        pthread_mutex_lock(com_mutex_pt);
        for(i = 0; i < 6; i++) {
            printf("\tHolding the mutex, parent will die after %d second.\n", 6 - i);
            sleep(1);
        }
        printf("Parent exit.\n");
    } else {
        for(i = 0; i < 3; i++) {
            printf("Child will lock the mutex after %d second.\n", 3 - i);
            sleep(1);
        }
        printf("Child begins to lock the mutex.\n");
        ret = pthread_mutex_lock(com_mutex_pt);
        if(ret == EOWNERDEAD)
            printf("ret is EOWNERDEAD.\t");
        printf("Child: pthread_mutex_lock() return %d.\n", ret);

        printf("Child exit.\n");
    }

    shmctl(shm_id, IPC_RMID, NULL);
    pthread_mutexattr_destroy(&attr);
    return 0;
}
