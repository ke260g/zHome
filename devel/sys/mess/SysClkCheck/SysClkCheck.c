/*
 * To check the operation system runtime clock resources
 *
 * software-clock-cycle and several clock resolution.
 */
#include<stdio.h>
#include<unistd.h>
#include<time.h>

#define CLOCK_NUM 4

const char *ClockName[] = {
    "CLOCK_REALTIME",
    "CLOCK_MONOTONIC",
    "CLOCK_PROCESS_CPUTIME_ID",
    "CLOCK_THREAD_CPUTIME_ID"
};

const int ClockId[] = {
    CLOCK_REALTIME,
    CLOCK_MONOTONIC,
    CLOCK_PROCESS_CPUTIME_ID,
    CLOCK_THREAD_CPUTIME_ID
};

int main(int argc, char **argv){
    printf("===================\n");
    printf("System clock ticks per second is %ld\n", sysconf(_SC_CLK_TCK));

    struct timespec res;
    int ret,
        i;

    for(i = 0; i < CLOCK_NUM; i++) {
        ret = clock_getres(ClockId[i], &res);
        if(ret)
            printf("Can't get the resolution of %s\n", ClockName[i]);
        else
            printf("The resolution of %s is %ld ns\n", ClockName[i], res.tv_nsec);
    }

    return 0;
}
