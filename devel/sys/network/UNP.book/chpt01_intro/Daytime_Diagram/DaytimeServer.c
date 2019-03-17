#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include<unistd.h>
#include<strings.h>

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
    //servaddr.sin_port = htons(13); // daytime , well-known port
    servaddr.sin_port = htons(1024); // >1023 can be assigned by user
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 10);

    while(1) {
        socklen = sizeof(cliaddr);
        connfd = accept(listenfd,
                (struct sockaddr *)&cliaddr, &socklen);
        if((pid = fork()) == 0) {
            /* cleanup the master server end resources */
            close(listenfd);

            /* perform the real service */
            printf("connection from %s, port %d.\n",
                    inet_ntop(AF_INET, &cliaddr.sin_addr,
                        buff, sizeof(buff)),
                    ntohs(cliaddr.sin_port));
            ticks = time(NULL);
            snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
            write(connfd, buff, strlen(buff));
            sleep(10); /* just for tested blocked */
            close(connfd);
            exit(0);
        }
        close(connfd);
    }
    return 0;
}
