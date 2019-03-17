#include<sys/types.h>
#include<sys/stat.h>
#include<sys/uio.h>
#include<fcntl.h>

#include<unistd.h>

#include<string.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct iovec iovec_s;

int main(int argc, char **argv){
    iovec_s iov[3];
    ssize_t nr;
    int fd, i;

    char *buf[] = {
        "My name is Orona Tidny.\n",
        "My mission is simple.\n",
        "To fix villingze's past.\n"};
    fd = open("mission.txt", O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(fd == -1) {
        perror("open()");
        return 1;
    }

    for(i = 0; i < 3; i++) {
        iov[i].iov_base = buf[i];
        iov[i].iov_len = strlen(buf[i]);
    }

    nr = writev(fd, iov, 3);
    if(nr == -1) {
        perror("writev()");
        return 1;
    }

    printf("wrote %d bytes\n", (int)nr);

    if(close(fd)) {
        perror("close()");
        return 1;
    }

    return EXIT_SUCCESS;
}
