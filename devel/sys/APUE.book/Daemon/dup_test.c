#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

char buf[] = "fda";

int main(int argc, char **argv) {
    int fd0;

    fd0 = open("output.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    dup2(fd0, STDOUT_FILENO);
    truncate("output.txt", 0);
    printf("fd0 is %d.\n", fd0);

    close(fd0);
    return 0;
}
