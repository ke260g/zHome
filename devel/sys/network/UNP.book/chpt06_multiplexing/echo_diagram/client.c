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
    char sendline[MAXLINE], recvline[MAXLINE], buf[MAXLINE];
    bzero(sendline, MAXLINE); bzero(recvline, MAXLINE);
    signal(SIGPIPE, sig_pipe);
#if 1 /* select() and shutdown() version */
        int maxfdp1, stdineof, n;
        fd_set rdset; /* read fd set */
        stdineof = 0;
        FD_ZERO(&rdset);
    while (1) {
        if (stdineof == 0)
            FD_SET(fileno(fp), &rdset);
        FD_SET(sockfd, &rdset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        Select(maxfdp1, &rdset, NULL, NULL, NULL);

        if(FD_ISSET(sockfd, &rdset)) { /* socket is readable */
            if(read(sockfd, buf, MAXLINE) == 0) {
                if(stdineof == 1)
                    return; /* normal terminates */
                else
                    err_quit("str_cli: server terminates prematurely");
            }
            buf[MAXLINE - 1] = '\0';
            Writen(fileno(stdout), buf, strlen(buf));
        }
        if(FD_ISSET(fileno(fp), &rdset)) { /* input is readable */
            if(read(fileno(fp), buf, MAXLINE) == 0) {
                stdineof = 1;
                Shutdown(sockfd, SHUT_WR); /* send FIN */
                FD_CLR(fileno(fp), &rdset);
                continue;
            }
            buf[MAXLINE - 1] = '\0';
            Writen(sockfd, buf, strlen(buf));
        }
    }
#endif

#if 0 /* original version */
    while(Readline(fileno(fp), sendline, MAXLINE) > 0) {
        sendline[MAXLINE - 2] = '\n';
        sendline[MAXLINE - 1] = '\0'; /* avoid input-overflow */
        Writen(sockfd, sendline, strlen(sendline));
        bzero(sendline, MAXLINE);

        if(Readline(sockfd, recvline, MAXLINE) == 0)
            err_quit("str_cli: server terminates prematurely");
        sendline[MAXLINE - 2] = '\n';
        sendline[MAXLINE - 1] = '\0'; /* avoid input-overflow */
        Writen(fileno(stdout), recvline, strlen(recvline));
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
