#include<sys/time.h>
#include<unistd.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>

static time_t tm_cur;

void alarm_handler(int signum) {
    printf("Hey, this is alarm handler\n");
    tm_cur = time(NULL);
    printf("%s\n\n", ctime(&tm_cur));
}

int main(int argc, char **argv){
    struct itimerval delay;
    int ret;

    errno = 0;
    signal(SIGALRM, alarm_handler);

    delay.it_interval.tv_sec = 7;
    delay.it_interval.tv_usec = 0;

    delay.it_value.tv_sec = 3;
    delay.it_value.tv_usec = 0;

    ret = setitimer(ITIMER_REAL, &delay, NULL);
    if(ret) {
        perror("failed to setitimer()");
        return EXIT_FAILURE;
    }else {
        printf("Timer begins.\n");
        tm_cur = time(NULL);
        printf("%s\n\n", ctime(&tm_cur));
    }

    while(1)
        pause();
    return EXIT_SUCCESS;
}
