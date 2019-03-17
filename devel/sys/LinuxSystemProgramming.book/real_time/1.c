#include<sched.h>
#include<stdio.h>
#include<stdlib.h>

#include<errno.h>

int main(int argc, char **argv){
    struct sched_param ap;
    const int sched_max_proirity = sched_get_priority_max(SCHED_FIFO);
    const int sched_min_proirity = sched_get_priority_min(SCHED_FIFO);
    ap.sched_priority = sched_max_proirity;

    int ret;
    errno = 0;
    ret = sched_setscheduler(0, SCHED_FIFO, &ap);
    if(errno || ret != 0) {
        perror("sched_setscheduler()");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
