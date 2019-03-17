#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
#include<signal.h>

pid_t child_pid;

#define my_execl(cmd_str) (execl("/bin/sh", "sh", "-c", cmd_str, NULL))
void child_sig_handler(int signum) {
    int wstatus;
    int ret;
    ret = waitpid(child_pid, &wstatus, WNOHANG);
    putchar('\n');

    if(ret == child_pid)
        printf("child is dead.\n");
    else
        printf("child's state is changed, but not dead.\n");
#if 0
    if(WIFEXITED(wstatus))
        printf("Child is terminated normally.\n");
    if(WIFSTOPPED(wstatus))
        printf("Child is stopped.\n");
    if(WIFCONTINUED(wstatus))
        printf("Child is continued.\n");
#endif
    putchar('\n');
}

int main(int argc, char **argv) {
    pid_t pid,
          my_pid;
    my_pid = getpid();

    if((pid = fork()) == -1) {
        perror("fork()");
    } else if(pid > 0) {
        //if(my_execl("./1"))
        //    perror("execl()");
        child_pid = pid;
        signal(SIGCHLD, child_sig_handler);
        while(1) {
            printf("I am parent %d, my child is %d.\n", my_pid, pid);
            sleep(10);
            kill(pid, SIGCONT);
        }
    } else { /* pid == 0 */
        //if(my_execl("./1"))
        //    perror("execl()");
        int i,
            j;
        i = 0;
        j = 0;
        while(1) {
            printf("Where is my parent? I am %d.\tNo, I am %d.\n", pid, getpid());
            sleep(1);

            if(i < 2)
                i++;
            else {
                i = 0;
                raise(SIGTSTP);
            }

            if(j < 9)
                j++;
            else {
                exit(0);
            }
        }
    }

    return 0;
}
