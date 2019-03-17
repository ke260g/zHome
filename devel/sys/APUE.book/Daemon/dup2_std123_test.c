#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>

#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char **argv) {
    int tmpfd, fd0, fd1, fd2;
    tmpfd = open("output.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    truncate("output.txt", 0);

    fd0 = dup2(tmpfd, STDIN_FILENO);
    fd1 = dup2(tmpfd, STDOUT_FILENO);
    fd2 = dup2(tmpfd, STDERR_FILENO);

    if(fd0 != STDIN_FILENO || fd1 != STDOUT_FILENO || fd2 != STDERR_FILENO)
        printf("dup2 occurs err.\n");
    printf("After dup2, fd0 is %d, fd1 is %d, fd2 is %d\n",
            fd0, fd1, fd2);
    fprintf(stderr, "Just test the stderr.\n");

    return 0;
}
