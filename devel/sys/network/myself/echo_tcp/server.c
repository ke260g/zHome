#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include<unistd.h>
#include<strings.h>

#include<sys/wait.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#include <errno.h>
#include <limits.h>

#define MAXLINE (65000)
#include<errno.h>
#include<signal.h>

#define DEFAULT_ECHO_PORT (4000)
unsigned int ECHO_PORT = DEFAULT_ECHO_PORT;

int parse_args_port(const char  *port_str, int *num);

static void sig_child(int signum) {
    pid_t child_pid;
    int wstatus;
    while((child_pid = waitpid(-1, &wstatus, WNOHANG)) > 0)
        ;
    return;
}

void str_echo(int sockfd) {
    ssize_t n;
    char buf[65000];

begin:
    bzero(buf, MAXLINE);
    while ((n = recv(sockfd, buf, MAXLINE, 0)) > 0) {
        buf[MAXLINE - 1] = '\0';
        printf("%s", buf);
        send(sockfd, buf, strlen(buf), 0);
        bzero(buf, MAXLINE);
    }

    if(n < 0 && errno == EINTR)
        goto begin;
    else if(n < 0)
        fprintf(stderr, "str_echo: read_error");
}

int main(int argc, char **argv) {
    int listenfd,
        connfd; /* connet fd, allocated by accpet() */
    struct sockaddr_in servaddr, cliaddr;
    char buff[MAXLINE];
    time_t ticks;
    int user_port;
    int ret;
    socklen_t socklen;
    pid_t pid;

    switch(argc) {
        case 1:
            printf("listening the default port\n");
            break;
        case 2:
            if(parse_args_port(argv[1], &user_port))
                return -1;
            ECHO_PORT = user_port;
            break;
        default:
            printf("usage: %s [port]\n", argv[0]);
            return -1;
    }

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(ECHO_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    errno = 0;
    ret = listen(listenfd, 10);
    if(ret == -1) {
        int errno_r = errno;
        fprintf(stderr, "port: %d is invalid, %s", ECHO_PORT, strerror(errno_r));
        return -1;
    }
    printf("listening port: %d\n", ECHO_PORT);
    signal(SIGCHLD, sig_child);

    while(1) {
        socklen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &socklen);
        if(connfd < 0) {
            if (errno == EINTR)
                continue;   /* back to while(1) */
            else // error handler
                ;
        }

        pid = fork();
        if(pid == 0) { // child process
            /* cleanup the master server end resources */
            close(listenfd);
            /* perform the real service */
            printf("connection from %s, port %d.\n",
                    inet_ntop(AF_INET, &cliaddr.sin_addr,
                        buff, sizeof(buff)),
                    ntohs(cliaddr.sin_port));

            str_echo(connfd);
            close(connfd);
            exit(0);
        }

        // parent, listening-process
        printf("Serv: My child is %d.\n", pid);
        close(connfd);
    }
    return 0;
}
