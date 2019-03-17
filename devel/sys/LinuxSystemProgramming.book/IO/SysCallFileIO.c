#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>

#include<unistd.h>

#include<string.h>

#include<stdlib.h>
#include<stdio.h>
#include<errno.h>

#define SYSCALL_COM_ERR -1

int main(int argc, char **argv){
    int __err = 0;

    char *pathfilename = "/etc/passwd";

    int fd;
    if((fd = open(pathfilename, O_RDONLY )) == SYSCALL_COM_ERR) {
        __err = errno;
        fprintf(stderr,"Open file %s : %s\n", pathfilename, strerror(__err));
        exit(EXIT_FAILURE);
    }

    int transbyte = 0;
    int len = 9000;

    char *buf_start = (char *)malloc(len);

    if((transbyte = read(fd, buf_start, len)) == -1) {
                __err = errno;
                fprintf(stderr,"Read file %s : %s\n", pathfilename, strerror(__err));
                exit(EXIT_FAILURE);
    }

    if(write(STDIN_FILENO, buf_start, len) == -1) {
        __err = errno;
        fprintf(stderr, "Output the file %s : %s\n", pathfilename, strerror(__err));
    }

    free(buf_start);

    if(close(fd) == SYSCALL_COM_ERR) {
        __err = errno;
        fprintf(stderr,"Close file %s : %s\n", pathfilename, strerror(__err));
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
