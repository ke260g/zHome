#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int socket_to_family(int sockfd) {
    struct sockaddr_storage ss;
    socklen_t len;

    len = sizeof(ss);
    if((getsockname(sockfd, (struct sockaddr *)&ss, &len)) < 0)
        return -1;
    return (ss.ss_family);
}
