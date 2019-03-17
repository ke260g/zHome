#include<strings.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include"../../unp.h"

void sig_pipe(int signum) {
    printf("SIGPIPE is caught.\n");
}

void echo_cli(int input_fd, int sockfd, const SA *pservaddr, socklen_t servlen) {
    ssize_t n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    socklen_t len;
    struct sockaddr *preply_addr;
    preply_addr = (SA *)Malloc(sizeof(servlen));

#if 1 /* connected-UDP */
    while(Read(input_fd, sendline, MAXLINE)) {
        Writen(sockfd, sendline, strlen(sendline));
        bzero(sendline, MAXLINE);

        n = Read(sockfd, recvline, MAXLINE);
        recvline[n] = '\0'; /* null terminates */
        Writen(STDOUT_FILENO, recvline, strlen(sendline));
        bzero(recvline, MAXLINE + 1);
    }
#endif
#if 0 /* unconnected-UDP  */
    while(Read(input_fd, sendline, MAXLINE)) {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        bzero(sendline, MAXLINE);

        len = servlen;
        n = recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);
#if 1 /* to avoid multi-host */
        if(len != servlen || memcmp(pservaddr, preply_addr, len) != 0) {
            printf("reply form %s (igonre)\n", sock_ntop(preply_addr, len));
            continue;
        }
#endif
        printf("reply form %s.\n", sock_ntop(preply_addr, len));
        recvline[n] = '\0'; /* avoid buffer overflow */
        Writen(STDOUT_FILENO, recvline, strlen(recvline));
        bzero(recvline, MAXLINE);
    }
#endif
}

int main(int argc, char **argv) {
    int sockfd, n, err;
    struct sockaddr_in servaddr;

    if(argc != 2)
        err_quit("usage: ./a.out <IP address>.\n");

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_quit("socket error\n");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    //servaddr.sin_port = htons(13); // daytime, well-known port
    servaddr.sin_port = htons(1024);
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        err_quit("inet_pton error for the invalid ip\n");
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    echo_cli(STDIN_FILENO, sockfd, (SA *)&servaddr, sizeof(servaddr));

    printf("Client Exit.\n");

    if(n < 0)
        err_quit("read error");
    return 0;
}
