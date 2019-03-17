/* an echo server that handles both udp and tcp */
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
        ;
    return;
}

int main(int argc, char **argv) {
    int listenfd, connfd, udpfd,
        nready, maxfdp1;
    char mesg[MAXLINE];
    pid_t childpid;
    fd_set rset;
    ssize_t n;
    socklen_t len;
    const int on = 1;
    struct sockaddr_in cliaddr, servaddr;

    /* listening socket for tcp */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(1025);
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    listen(listenfd, 5);

    /* create UDP socket */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(1025);
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(udpfd, (SA *)&servaddr, sizeof(servaddr));

    /* for tcp to cleanup child-process */
    signal(SIGCHLD, sig_child);

    FD_ZERO(&rset);
    maxfdp1 = max(listenfd, udpfd) + 1;
    while(1) {
        FD_SET(listenfd, &rset);
        FD_SET(udpfd, &rset);
        nready = select(maxfdp1, &rset, NULL, NULL, NULL);
        if(nready < 0) {
            if(errno == EINTR)
                continue;
            else
                err_sys("select error");
        }
        if(FD_ISSET(listenfd, &rset)) {
            len = sizeof(cliaddr);
            connfd = accept(listenfd, (SA *)&cliaddr, &len);
            childpid = fork();
            if(childpid == 0) { /* child process */
                close(listenfd);
                str_echo(connfd);
                exit(0);
            }
            /* parent process */
            close(connfd);
        }
        if(FD_ISSET(udpfd, &rset)) {
            len = sizeof(cliaddr);
            n = recvfrom(udpfd, mesg, MAXLINE, 0, (SA *)&cliaddr, &len);
            sendto(udpfd, mesg, n, 0, (SA *)&cliaddr, len);
        }
    }
    return 0;
}
