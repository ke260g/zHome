#include<stdlib.h>
#include<stdio.h>

#include<unistd.h>
#include<signal.h>


/* custom SIGINT hanlder */
static void signal_handler(int sig){
    if(sig == SIGINT)
        printf("Caught SIGINT!\n");
    else if(sig == SIGTERM)
        printf("Caught SIGTERM!\n");
    else { /* actually this can't be happened */
        fprintf(stderr, "Unexpected signal!\n");
        exit(EXIT_FAILURE);
    }
        exit(EXIT_FAILURE);
}

int main(int argc, char **argv){

    /* register signal_handler as the SIGINT handler */
    if(signal(SIGINT, signal_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGINT!\n");
        exit(EXIT_FAILURE);
    }

    /* register signal_handler as the SIGTERM handler */
    if(signal(SIGTERM, signal_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGTERM!\n");
        exit(EXIT_FAILURE);
    }

    /* reset the SIGPROF to the default action */
    if(signal(SIGPROF, SIG_DFL) == SIG_ERR) {
        fprintf(stderr, "Cannot reset the SIGPROF!\n");
        exit(EXIT_FAILURE);
    }

    /* ignore SIGHUP */
    if(signal(SIGHUP, SIG_IGN) == SIG_ERR) {
        fprintf(stderr, "Cannot ignore SIGHUP!\n");
        exit(EXIT_FAILURE);
    }

    while(1)
        pause();

    return EXIT_SUCCESS;
}
