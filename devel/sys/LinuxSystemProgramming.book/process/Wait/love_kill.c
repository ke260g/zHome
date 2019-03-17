#include<stdio.h>
#include<wait.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void void_func(int signum) {

}

int main(int argc, char **argv) {
    int wstatus,
        pid,
        ret,
        i;  /* common counter */

    if((pid = fork()) < 0) {
        fprintf(stderr, "Error to fork().\n");
        exit(EXIT_FAILURE);

    } else if(pid > 0) { /* parent */
#if 0 /* wait */
        ret = waitpid(pid, &wstatus, 0);
        if(ret == -1)
            perror("waitpid():");
        printf("wait() returns %d.\n", ret);
#endif
        sleep(2);

        printf("Parent: I send SIGUSR1 to my child.\n");
        kill(pid, SIGUSR1);

        if(waitpid(pid, NULL, 0) == pid)
            printf("Parent: My child is dead\n");
    } else { /* child */

#if 0 /* illegal memory access */
        int *pt = NULL;
        *pt = 0;
#endif
        printf("Child: I am %ld pid.\n", (long)getpid());

        signal(SIGUSR1, void_func); /* a `wake up' signal */

        pause();    /* wait for any singal */
            printf("Child: I am waitup.\n");

        for(i = 6; i > -1; i--) {
            printf("Child: I will be killed after %d second.\n", i);
            sleep(1);
        }

        exit(EXIT_FAILURE);
    }

    exit(EXIT_FAILURE);
}
