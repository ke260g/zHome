#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include<unistd.h>
#include<strings.h>
#include<limits.h> /* OPEN_MAX */

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#include"../../unp.h"

#define OPEN_MAX (100)

int main(int argc, char **argv) {
    int i, /* common counter */
        maxi,   /* max index, for client[] */
        nready, /* amount of ready fd */
        sockfd,
        listenfd,
        connfd; /* connet fd, allocated by accpet() */
    ssize_t n;
    char buff[MAXLINE];
    socklen_t socklen;
    struct sockaddr_in servaddr, cliaddr;
    struct pollfd client[OPEN_MAX];

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(1024);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 10);

    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;
    for(i = 1; i < OPEN_MAX; i++)
        client[i].fd = -1; /* -1 means available entry */
    maxi = 0;

    while(1) {
        nready = poll(client, maxi + 1, INFTIM);

        if(client[0].revents & POLLRDNORM) {
            /* new client connection */
            socklen = sizeof(cliaddr);
acc_etr:    connfd = accept(listenfd, (SA *)&cliaddr, &socklen);
            if(connfd < 0) {
                if (errno == EINTR)// || errno == ECONNABORTED)
                    goto acc_etr;   /* back to while(1) */
                else
                    err_quit("server: accept() error");
            }


            /* find a array-member to store fd */
            for(i = 0; i < OPEN_MAX; i++)
                if(client[i].fd < 0) { /* -1 */
                    client[i].fd = connfd;
                    break;
                }

            if(i == OPEN_MAX) /* meet the limitation */
                err_quit("too many clients");

            client[i].events = POLLRDNORM;
            if(i > maxi)
                maxi = i; /* max index in client[] */

            /* no more readable fd,
             * back to while(1) */
            if(--nready <= 0)
                continue;
        }

        for(i = 0; i <= maxi; i++) {
            /* check all client's input data */
            if(client[i].fd < 0)
                continue;

            sockfd = client[i].fd;
            if(client[i].revents & (POLLRDNORM | POLLERR)) {
                /* perform real echo service */
                n = Read(sockfd, buff, MAXLINE);
                if(n < 0) {
                    if(errno == ECONNRESET) { /* RST */
                    /* connection reset by client */
                        close(sockfd);
                        client[i].fd = -1; /* clear the client[] */
                    } else
                        err_sys("read error");
                } else if (n == 0) { /* EOF, FIN */
                    /* connection closed by client */
                    close(sockfd);
                    client[i].fd = -1; /* clear the client[] */
                } else
                    Writen(sockfd, buff, n);

                /* no more readable fd, back to while(1) */
                if(--nready <= 0)
                    break;
            }
        }
    }
    return 0;
}
