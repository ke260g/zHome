#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include<stdlib.h>
#include<errno.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char **argv){
    if(argc != 2) {
        fprintf(stderr, "Usage : %s <absolute path to filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int fd = open("argv[1]", O_RDWR);
    if(fd == -1) {
        int __err = errno;
        fprintf(stderr, "Open error : %s \n",
                strerror(__err));
        return EXIT_FAILURE;
    }

    if(ftruncate(fd, 100) == -1) {
        int __err = errno;
        fprintf(stderr, "Ftruncate error : %s \n",
                strerror(__err));
        return EXIT_FAILURE;
    }

    close(fd);
    return EXIT_SUCCESS;
}
