#include<sys/types.h>
#include<sys/ioctl.h>
#include<sys/stat.h>

#include<fcntl.h>
#include<unistd.h>

#include<stdio.h>
#include<stdlib.h>

#include<linux/cdrom.h>

int main(int argc, char **argv){
    int fd, ret;

    if(argc != 2) {
        fprintf(stderr, "usage: %s <device to eject>\n", argv[0]);
        return EXIT_FAILURE;
    }

    fd = open(argv[1], O_RDONLY | O_NONBLOCK);
    if(fd < 0) {
        perror("open()");
        return EXIT_FAILURE;
    }
    ret = ioctl(fd, CDROMEJECT, 0);
    if(ret) {
        perror("ioctl");
        return EXIT_FAILURE;
    }
    ret = close(fd);
    if(ret) {
        perror("close");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
