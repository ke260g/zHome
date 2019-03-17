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

void echo_str(int sockfd, SA *pcliaddr, socklen_t clilen)
{
    ssize_t n;
    socklen_t len;
    char mesg[MAXLINE];

    getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &n, &len);
    perror("getsock()");
    printf("receive buffer size is %d bytes.\n", (int)n);
    while(1) {
        len = clilen;
        n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
        Sendto(sockfd, mesg, n, 0, pcliaddr, len);
        bzero(mesg, MAXLINE);
    }
}

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t socklen;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(1024);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(sockfd, (SA *)&servaddr, sizeof(servaddr));
    echo_str(sockfd, (SA *)&cliaddr, sizeof(cliaddr));
    return 0;
}
