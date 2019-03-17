#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/ioctl.h>
#include<signal.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include"../scull_ioctl.h"

void user1_sighandler(int signum) {
    printf("I get the signal sighandler.\n");
}

int main(int argc, char **argv) {
    int fd, ret;
    time_t timeCurrent;
    signal(SIGUSR1, user1_sighandler);
    fd = open("/dev/scull0", O_NONBLOCK);
    if(fd < 0) {
        perror("first open()");
    }
    printf("open() return %d.\n", fd);
    printf("first open() is return.\n");

    int retQuantum = -1;
    ret = ioctl(fd, SCULL_IOCGQUANTUM, NULL);
    printf("ret return %d, retQuantum is %d.\n", ret, retQuantum);

    getchar();
    time(&timeCurrent); printf("%s.", ctime(&timeCurrent));
    fd = open("/dev/scull0", 0);
    if(fd < 0) {
        perror("second open()");
    }
    time(&timeCurrent); printf("%s.", ctime(&timeCurrent));

    close(fd);
    return 0;
}
