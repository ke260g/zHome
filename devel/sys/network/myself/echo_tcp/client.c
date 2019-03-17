#include<strings.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#define MAXLINE (1024)
#define DEFAULT_ECHO_PORT (20000)
int ECHO_PORT = DEFAULT_ECHO_PORT;

int parse_args_port(const char  *port_str, int *num);

void err_quit(const char *err_msg) {
    fprintf(stderr, "%s", err_msg);
    exit(EXIT_FAILURE);
}

void str_cli(FILE *fp, int sockfd) {
    char sendline[MAXLINE], recvline[MAXLINE];
    bzero(sendline, MAXLINE); bzero(recvline, MAXLINE);
    while(fgets(sendline, MAXLINE, fp) != NULL) {
    //while(1) {
        //fgets(sendline, MAXLINE, fp);
        sendline[MAXLINE - 1] = '\0';
        write(sockfd, sendline, strlen(sendline));
        bzero(sendline, MAXLINE);
        if(recv(sockfd, recvline, MAXLINE, 0) == 0)
            err_quit("str_cli: server terminates prematurely");
        fputs(recvline, stdout);
        bzero(recvline, MAXLINE);
    }
}

int main(int argc, char **argv) {
    int sockfd, n, err;
    struct sockaddr_in servaddr;
    int user_port;

    switch(argc) {
        case 2:
            printf("sending to the default port\n");
            break;
        case 3:
            if(parse_args_port(argv[2], &user_port))
                return -1;
            ECHO_PORT = user_port;
            break;
        default:
            err_quit("usage: program <IP address> <Port>.\n");
            return -1;
    }

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_quit("socket error\n");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    //servaddr.sin_port = htons(13); // daytime, well-known port
    servaddr.sin_port = htons(ECHO_PORT);
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        err_quit("inet_pton error for the invalid ip address or port, may be both\n");

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
    }
    printf("sending to the port %d\n", ECHO_PORT);

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
