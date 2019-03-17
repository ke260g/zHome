#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<sys/shm.h>

#define SECRET_NUM 2046
// #define SECRET_NUM 1874
int shm_id;

int main(int argc, char **argv) {
    int pid;

    shm_id = shmget(IPC_PRIVATE, sizeof(int), S_IRUSR | S_IWUSR);
    printf("New shm_id is %d\n", shm_id);

    if((pid = fork()) < 0) {
        perror("Error to fork()\n");
        return EXIT_FAILURE;
    } else if(pid > 0) { /* parent */
        int *secret_buf;
        if((secret_buf = shmat(shm_id, NULL, 0)) == (void *)-1) {
            perror("Parent: Error to shmat()\n");
            kill(pid, SIGTERM);/* kill the child */
            return EXIT_FAILURE;
        }
        *secret_buf = SECRET_NUM;
        printf("Parent: I send a secret number.\n");
        sleep(6);   /* wait the child to obtain */

        shmctl(shm_id, IPC_RMID, NULL);
    } else { /* child */
        sleep(2);   /* wait for secret buf */
        int *secret_buf;
        if((secret_buf = shmat(shm_id, NULL, SHM_RDONLY)) == (void *)-1) {
            perror("Child: Error to shmat()\n");
            return EXIT_FAILURE;
        }
        printf("Child: The secret number is %d\n", *secret_buf);
    }

    return 0;
}
