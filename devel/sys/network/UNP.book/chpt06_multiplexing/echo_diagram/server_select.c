/* this is a echo server,
 * but it is not safe,
 * can easily encounter DoS-attacks */
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

int main(int argc, char **argv) {
    int i, /* common counter */
        maxi,   /* max index, for client[] */
        maxfd,  /* maximum of fd */
        nready, /* amount of ready fd */
        sockfd,
        listenfd,
        connfd, /* connet fd, allocated by accpet() */
        client[FD_SETSIZE];
    struct sockaddr_in servaddr, cliaddr;
    char buff[MAXLINE];
    socklen_t socklen;
    fd_set rdset, allset;
    ssize_t n;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(1024);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 10);

    maxfd = listenfd; /* initialize */
    maxi = -1;      /* index into client[] */
    for(i = 0; i < FD_SETSIZE; i++)
        client[i] = -1;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    while(1) {
        rdset = allset;
        nready = select(maxfd + 1, &rdset, NULL, NULL, NULL);

        if(FD_ISSET(listenfd, &rdset)) {
            /* new client connection */
            socklen = sizeof(cliaddr);
acc_etr:    connfd = accept(listenfd, (SA *)&cliaddr, &socklen);
            if(connfd < 0) {
                if (errno == EINTR)// || errno == ECONNABORTED)
                    goto acc_etr;   /* back to while(1) */
            }

            /* find a array-member to store fd */
            for(i = 0; i < FD_SETSIZE; i++) {
                if(client[i] < 0) { /* -1 */
                    client[i] = connfd;
                    break;
                }
            }
            if(i == FD_SETSIZE) /* meet the limitation */
                err_quit("too many clients");

            FD_SET(connfd, &allset); /* add new fd */
            if(connfd > maxfd)
                maxfd = connfd; /* refresh the new maxfd */
            if(i > maxi)
                maxi = i; /* max index in client[] */

            /* no more readable fd,
             * back to while(1) */
            if(--nready <= 0)
                continue;
        }

        for(i = 0; i <= maxi; i++) {
            /* check all client's input data */
            if(client[i] < 0)
                continue;

            sockfd = client[i];
            if(FD_ISSET(sockfd, &rdset)) {
                /* perform real echo service */
                n = Read(sockfd, buff, MAXLINE);
                /* here, it's dangerous when the client
                 * send data but not enough,
                 * server will hung */
                if(n == 0) { /* EOF, FIN */
                    /* connection closed by client */
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1; /* clear the client[] */
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
