#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <strings.h>

#define BUF_LEN (1024)
#define ECHO_PORT (3095)

const char echo_msg[30] = "I am THIC, NanoPC-T3!";
int main( int argc, char **argv ) {
    int ret,
        sockfd;
    char buf[BUF_LEN];
    struct sockaddr_in cliaddr;
    socklen_t addrlen;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(ECHO_PORT);
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    addrlen = sizeof(cliaddr);

    bind(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    while(1) {
        ret = recvfrom(sockfd, buf, BUF_LEN, 0, (struct sockaddr *)&cliaddr, &addrlen);
        if(ret < 0) {
            sleep(5); continue;
        } else if (addrlen != sizeof(cliaddr)) {
            sleep(5); continue;
        }else {
            sendto(sockfd, echo_msg, 30, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
            sleep(5);
        }
    }

    return 0;
}
