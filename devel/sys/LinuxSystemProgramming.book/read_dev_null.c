#include<stdio.h>
#include<stdlib.h>

#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc, char **argv){
    char c;
    int ret, fd;

    fd = open("/dev/null", O_RDONLY);
    if(fd < 0) {
        perror("open()");
        return EXIT_FAILURE;
    }
    ret = read(fd, &c, sizeof(char));
    if(ret) {
        perror("read()");
        return EXIT_FAILURE;
    }
    if(c == 0)
        printf("yes\n");
    return EXIT_SUCCESS;
}
