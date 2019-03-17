/* my daemon_init implement,
 * fork from the Figure-13.1-APUE
 * fixed some bug,
 * more portable.
 */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/resource.h>
#include<sys/stat.h>
#include<syslog.h>
#include<signal.h>

void daemon_init(const char *cmd) {
    int i,
        tmpfd,
        fd0,
        fd1,
        fd2;
    pid_t pid;
    struct rlimit rl; /* resource limit */
    struct sigaction sa; /* sig action */

    /* clear file creation mask */
    umask(0);
    /* get max number of file descriptors */
    if(getrlimit(RLIMIT_NOFILE, &rl) < 0)
        fprintf(stderr, "%s: can't get file limit\n", cmd);

    /* become a session leader to lose controlling tty. */
    if((pid = fork()) < 0)
        fprintf(stderr, "%s: can't fork\n", cmd);
    else if(pid != 0) /* parent */
        exit(0);
    /* child */
    setsid();

    /* ensure future open won't allocate controlling ttys. */
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if(sigaction(SIGHUP, &sa, NULL) < 0)
        fprintf(stderr, "%s can't ignore SIGHUP\n", cmd);
    if((pid = fork()) < 0)
        fprintf(stderr, "%s can't fork\n", cmd);
    else if(pid != 0) /* parent */
        exit(0);

    /* child */
    /* change the current working dir to the root
     * so we won't prevent file system from being unmounted */
    if(chdir("/") < 0)
        fprintf(stderr, "%s can't change dir to /\n", cmd);

    /* close all open file descriptors */
    if(rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for(i = 0; i < rl.rlim_max; i++)
        close(i);

    /* attach file descriptors 0, 1 and 2 to /dev/null. */
    tmpfd = open("/dev/null", O_RDWR);
    fd0 = dup2(tmpfd, STDIN_FILENO);
    fd1 = dup2(tmpfd, STDOUT_FILENO);
    fd2 = dup2(tmpfd, STDERR_FILENO);

    /* initialize the log file */
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if(fd0 != STDIN_FILENO ||
            fd1 != STDOUT_FILENO ||
            fd2 != STDERR_FILENO) {
        syslog(LOG_ERR, "unexpected file descriptors %d %d %d",
                fd0, fd1, fd2);
        exit(1);
    }
}
