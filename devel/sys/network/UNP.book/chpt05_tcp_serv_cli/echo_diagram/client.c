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

void str_cli(FILE *fp, int sockfd) {
    char sendline[MAXLINE], recvline[MAXLINE];
    bzero(sendline, MAXLINE); bzero(recvline, MAXLINE);
    signal(SIGPIPE, sig_pipe);
    while(Fgets(sendline, MAXLINE, fp) != NULL) {
        sendline[MAXLINE - 1] = '\0';
#if 0 /* new version */
        send(sockfd, sendline, strlen(sendline), MSG_DONTROUTE);
#endif
#if 1 /* better version */
        Writen(sockfd, sendline, strlen(sendline));
#endif
#if 0 /* for testing SIGPIPE */
        Writen(sockfd, sendline, 1);
        printf("errno is %d.\n", errno);
        sleep(1);
        Writen(sockfd, sendline + 1, strlen(sendline) - 1);
        printf("errno is %d.\n", errno);
#endif

        bzero(sendline, MAXLINE);
        if(Readline(sockfd, recvline, MAXLINE) == 0)
            err_quit("str_cli: server terminates prematurely");
        Fputs(recvline, stdout);
        bzero(recvline, MAXLINE);
    }
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

    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        err = errno;
        perror("connect()");
        switch(err) {
            case ECONNREFUSED:
                printf("errno is ECONNREFUSED.\n");
                break;
            case ETIMEDOUT:
                printf("errno is ETIMEDOUT.\n");
                break;
            case EHOSTUNREACH:
                printf("errno is EHOSTUNREACH.\n");
                break;
            case ENETUNREACH:
                printf("errno is ENETUNREACH.\n");
                break;
        }
        err_quit("connect error.\n");
        exit(EXIT_FAILURE);
    }

    char buff[MAXLINE];

    printf("I am client, connection from %s, port %d.\n",
            inet_ntop(AF_INET, &servaddr.sin_addr,
                buff, sizeof(buff)),
            ntohs(servaddr.sin_port));

    str_cli(stdin, sockfd);
    printf("Client Exit.\n");

    if(n < 0)
        err_quit("read error");
    return 0;
}
