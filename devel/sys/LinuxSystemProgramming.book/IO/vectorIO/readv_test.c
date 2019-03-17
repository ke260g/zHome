#include<sys/stat.h>
#include<sys/types.h>
#include<sys/uio.h>

#include<fcntl.h>
#include<unistd.h>

#include<stdio.h>
#include<stdlib.h>

typedef struct iovec iovec_s;

int main(int argc, char **argv){
    char foo[24], bar[22], baz[25];
    iovec_s iov[3];
    ssize_t nr;
    int fd, i;

    fd = open("mission.txt", O_RDONLY);
    if(fd == -1) {
        perror("open()");
        return EXIT_FAILURE;
    }

    /* define iovec structure */
    iov[0].iov_base = foo;
    iov[0].iov_len = sizeof(foo);
    iov[1].iov_base = bar;
    iov[1].iov_len = sizeof(bar);
    iov[2].iov_base = baz;
    iov[2].iov_len = sizeof(baz);

    nr = readv(fd, iov, 3);
    if(nr == -1) {
        perror("readv()");
        return EXIT_FAILURE;
    }

    for(i = 0; i < 3; i++)
        printf("%d : %s", i, (char *)iov[i].iov_base);

    if(close(fd)) {
        perror("close()");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
