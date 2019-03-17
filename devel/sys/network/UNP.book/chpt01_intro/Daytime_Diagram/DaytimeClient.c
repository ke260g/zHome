#include<strings.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define MAXLINE (64)

static void err_quit(const char *err_msg) {
    if(err_msg)
        printf("%s", err_msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    int sockfd, n, err;
    char recvline[MAXLINE + 1];
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
    /* perform the real service */
#define MAXLINE (64)
    char buff[MAXLINE];
    printf("I am client, connection from %s, port %d.\n",
            inet_ntop(AF_INET, &servaddr.sin_addr,
                buff, sizeof(buff)),
            ntohs(servaddr.sin_port));

    while((n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = '\0'; /* EOL */
        if(fputs(recvline, stdout) == EOF)
            err_quit("fputs error.\n");
    }
    printf("Client Exit.\n");

    if(n < 0)
        err_quit("read error");
    return 0;
}
