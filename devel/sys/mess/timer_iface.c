#if 0
/* how to make read(), scanf(), recv(),
 * return after a specific time without
 * being dead blocked ?
 */
#include<time.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

static void sig_handler(int signum) {
    // c++, need to include<iostream>
    // std::cout << "read() waited time out " << signum << std::endl;

    // c, need to include<stdio.h>
    // printf("read() waited time out\n");
}

int func(int wait_second) {
    timer_t timerid;
    struct itimerspec it;
    int ret;
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_nsec = 0;
    it.it_value.tv_sec = wait_second;
    it.it_value.tv_nsec = 0;

    struct sigevent evp;
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sig_handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGUSR1, &act, NULL);
    memset(&evp, 0, sizeof(evp));
    evp.sigev_signo = SIGUSR1;
    evp.sigev_notify = SIGEV_SIGNAL;

    timer_create(CLOCK_REALTIME, &evp, &timerid);
    timer_settime(timerid, 0, &it, NULL);

    /* here begin blocked function
     * like read(), scanf, recv()
     */

    timer_delete(timerid);
    return 0;
}
#endif
