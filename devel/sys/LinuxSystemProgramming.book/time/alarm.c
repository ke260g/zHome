#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<time.h>

void alarm_handler(int signum) {
    printf("Hey, this is alarm handler\n");
}

int main(int argc, char **argv){
    unsigned alarm_rem;

    errno = 0;
    signal(SIGALRM, alarm_handler);
    if(errno)
        perror("failed to register SIGALRM handler signal()");

    errno = 0;
    alarm_rem = alarm(99);
    if(errno)
        perror("failed to set the alarm(99)");
    else
        printf("Uppon alarm remain %d seconds\n", alarm_rem);

    struct timespec tm10s = { .tv_sec = 10, .tv_nsec = 0 };
    errno = 0;
    nanosleep(&tm10s, NULL);
    if(errno)
        perror("failed to nanosleep()");

    errno = 0;
    alarm_rem = alarm(9999);
    if(errno)
        perror("failed to set the alarm(9999)");
    else
        printf("Uppon alarm remain %d seconds\n", alarm_rem);

    while(1)
        pause();
    return EXIT_SUCCESS;
}
