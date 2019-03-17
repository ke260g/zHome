#include<stdlib.h>
#include<stdio.h>

#include<unistd.h>
#include<signal.h>
#include<errno.h>

/* custom SIGINT hanlder */
static void SIGINT_handler (int signum) {
    printf("Caught SIGINT!\n");
}

int main(int argc, char **argv){
    if(signal(SIGINT, SIGINT_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGINT!\n");
    }

    pause();
    if(errno == EINTR)
        printf("pause() is returned\n");
    return EXIT_SUCCESS;
}
