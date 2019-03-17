#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char **argv){
    clockid_t clocks[] = {
        CLOCK_REALTIME,
        CLOCK_MONOTONIC,
        CLOCK_PROCESS_CPUTIME_ID,
        CLOCK_THREAD_CPUTIME_ID,
        (clockid_t) -1 };
    int i; /* counter */

    for ( i = 0; clocks[i] != (clockid_t) - 1; i++ ) {
        struct timespec res;
        errno = 0;
        clock_getres(clocks[i], &res);
        if(errno)
            perror("failed to clock_getres()");
        else
            printf("clock = %d sec = %ld nsec = %ld\n",
                    clocks[i], res.tv_sec, res.tv_nsec);
    }

    return EXIT_SUCCESS;
}
