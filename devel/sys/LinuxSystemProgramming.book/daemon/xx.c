/*
 * to start X in a daemon
 */
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv) {
    int ret;
    char *argvs[2] = {
        "startx",  NULL};

    int status = daemon(0, 0);
    ret = execv("/usr/bin/startx", argvs);
    if(ret == -1)
        abort();

    return status;
}
