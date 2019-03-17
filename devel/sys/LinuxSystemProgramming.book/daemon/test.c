#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>

int ll_system(const char *cmd) {
    /*
     * fork of the system(),
     * but do not ignore any signle block
     */
    int status;
    pid_t pid;
    pid = fork();
    if(pid == -1)
        return -1;
    else if (pid == 0) {
        const char *argvs[4] = { "sh", "-c", cmd, NULL};
        execv("/bin/sh", (char **)argvs);
        exit(-1);
    }

    if(waitpid(pid, &status, 0) == -1)
        return -1;
    if(WIFCONTINUED(status))
        printf("oo");
    return 0;
}
