#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include<unistd.h>
#include<strings.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#include"../../unp.h"
static void sig_child(int signum)
{
    pid_t child_pid;
    int wstatus;
    while((child_pid = waitpid(-1, &wstatus, WNOHANG)) > 0)
        printf("child %d is done.\n", child_pid);
    return;
}

void str_echo(int sockfd)
{
    ssize_t n;
    char buf[MAXLINE];
#if 0 /* calculate sum of two integers */
    while(1) {
        long arg[2];
        if((n = Readline(sockfd, buf, MAXLINE)) == 0)
            return; /* connection closed by other peer */
        if(sscanf(buf, "%ld %ld", &arg[0], &arg[1]))
            snprintf(buf, sizeof(buf), "%ld\n", arg[0] + arg[1]);
        else
            snprintf(buf, sizeof(buf), "input error.\n");

        n = strlen(buf);
        Writen(sockfd, buf, n);
    }
#endif

#if 1 /* original version */
begin:
    while(Readline(sockfd, buf, MAXLINE) > 0) {
        printf("Serv: receive a message.\n");

        buf[MAXLINE - 2] = '\n';
        buf[MAXLINE - 1] = '\0';
        Writen(sockfd, buf, strlen(buf));
        printf("Serv: send back to client.\n");
        bzero(buf, MAXLINE);
    }
    if(n < 0 && errno == EINTR)
        goto begin;
    else if(n < 0)
        err_sys("str_echo: read_error");
#endif
}

int main(int argc, char **argv) {
    int listenfd,
        connfd; /* connet fd, allocated by accpet() */
    struct sockaddr_in servaddr, cliaddr;
    char buff[MAXLINE];
    time_t ticks;
    socklen_t socklen;
    pid_t pid;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(1024);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 10);
    signal(SIGCHLD, sig_child);

    while(1) {
        socklen = sizeof(cliaddr);
        connfd = accept(listenfd, (SA *)&cliaddr, &socklen);
        if(connfd < 0) {
            if (errno == EINTR)// || errno == ECONNABORTED)
                continue;   /* back to while(1) */
            else
                exit(EXIT_SUCCESS);
        }

        printf("accept() returns %d.\n", connfd);
        pid = fork();
        if(pid == 0) {
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
        printf("Serv: My child is %d.\n", pid);
        close(connfd);
    }
    return 0;
}
