#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/ioctl.h>
#include<signal.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>

#define FILENAME ("/dev/cmos1")

void user1_sighandler(int signum) {
    printf("I get the signal sighandler.\n");
}

int main(int argc, char **argv) {
    int fd, ret;
    time_t timeCurrent;
    signal(SIGUSR1, user1_sighandler);
    fd = open(FILENAME, O_NONBLOCK);
    if(fd < 0) {
        perror("first open()");
    }

    printf("open() return %d.\n", fd);
    printf("first open() is return.\n");

    getchar();

    close(fd);
    return 0;
}
