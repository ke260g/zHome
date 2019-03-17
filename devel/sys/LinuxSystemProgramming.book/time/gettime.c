#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>

int main(int argc, char **argv){
    clockid_t clocks[] = {
        CLOCK_REALTIME,
        CLOCK_MONOTONIC,
        CLOCK_PROCESS_CPUTIME_ID,
        CLOCK_THREAD_CPUTIME_ID,
        (clockid_t) - 1 };

    int i;

    for(i = 0; clocks[i] != (clockid_t) - 1; i++) {
        struct timespec ts;
        errno = 0;
        clock_gettime(clocks[i], &ts);
        if(errno)
            perror("failed to clock_gettime()");
        else
            printf("clock = %d sec = %ld nsec = %ld \n",
                    clocks[i], ts.tv_sec, ts.tv_nsec);
    }
    return EXIT_SUCCESS;
}
