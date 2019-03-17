#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<signal.h>
#include<errno.h>

#include<unistd.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int udp_send(const void *buf,
    int len,
    const char *ipv4_addr,
    const int port) {
    int sockfd, ret;
    struct sockaddr_in servaddr;

    ret = sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(ret < 0) {
        printf("%s: failed to socket\n", __func__);
        return -1;
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    //servaddr.sin_port = htons(13); // daytime, well-known port
    servaddr.sin_port = htons(port);
    ret = inet_pton(AF_INET, ipv4_addr, (struct sockaddr *)&servaddr.sin_addr);
    if(ret <= 0) {
        printf("%s: inet_pton error for the invalid ip\n", __func__);
        return -1;
    }

    ret = sendto(sockfd, buf, len, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if(ret < 0) {
        printf("%s: sendto() error\n", __func__);
        return -1;
    }
    close(sockfd);
    return ret;
}

int udp_recv(void *buf,
    const int len,
    const port) {
    int ret;
    int sockfd;
    struct sockaddr_in cliaddr;
    socklen_t socklen;
    socklen = sizeof(cliaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&cliaddr, sizeof(cliaddr));

    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(port);
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    ret = bind(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    if(ret < 0) {
        printf("bind error\n");
        return -1;
    }

    ret = recvfrom(sockfd, buf, len, 0, NULL, NULL);
    printf("%s: receive %d bytes\n", __func__, ret);

    close(sockfd);
    return ret;
}

static void sig_handler(int signum) {
    printf("udp_send_recv: readform() waited time out %d", signum);
}

int udp_recv_wait(void *buf,
    const int len,
    const int port,
    const int wait_second) {

    timer_t timerid;
    struct itimerspec it;
    int ret;

    int sockfd;
    struct sockaddr_in cliaddr;
    socklen_t socklen;

    /* network interface init */
    socklen = sizeof(cliaddr);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&cliaddr, sizeof(cliaddr));

    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(port);
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    ret = bind(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    if(ret < 0) {
        printf("bind error\n");
        return -1;
    }

    /* timer structure init */
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_nsec = 0;
    it.it_value.tv_sec = wait_second;
    it.it_value.tv_nsec = 0;

    struct sigevent evp;
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sig_handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGUSR1, &act, NULL);
    memset(&evp, 0, sizeof(evp));
    evp.sigev_signo = SIGUSR1;
    evp.sigev_notify = SIGEV_SIGNAL;

    timer_create(CLOCK_REALTIME, &evp, &timerid);
    timer_settime(timerid, 0, &it, NULL);
    /* blocked function */
    ret = -1;
    ret = recvfrom(sockfd, buf, len, 0, NULL, NULL);
    timer_delete(timerid);

    printf("%s: receive %d bytes\n", __func__, ret);

    close(sockfd);
    return ret;
}
