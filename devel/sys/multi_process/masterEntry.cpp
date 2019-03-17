#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstdio>

static pid_t mainctrl_pid;

void wait_child_to_die(int signum) {
    int ret;
    ret = waitpid(mainctrl_pid, NULL, WNOHANG);
    if(ret != mainctrl_pid)
        return;

    printf("\t\e[43;31;1m"
            "mainctrl is dead."
            "\e[0m\n");
    /* perform mainctrl-death handler  */
}

int main(int argc, char **argv) {
    pid_t pid;
    pid = fork();
    if(pid < 0) {
        /* fatal error handler */
        return -1;
    } else if (pid > 0) {
        /* parent, perform monitor-process */
        mainctrl_pid = pid;
        signal(SIGCHLD, wait_child_to_die);
        while(1)
            pause();
    } else /* pid == 0 */ {
        // exec the mainctrl-routine
    }
    return 0;
}
