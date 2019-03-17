#include"udp_send_recv.h"
#include<string.h>
#include<stdio.h>

#define LISTEN_PORT (2046)

int main(int argc, char **argv) {
    char buf[1024];
    int cnt;
    int i;
    memset(buf, '\0', 1024);
    for(i = 0; i < 10000; i++) {
        cnt = udp_recv(buf, 1024, LISTEN_PORT);
        buf[1023] = '\0';
        printf("%s\n", buf);
        memset(buf, '\0', 1024);
    }
    return 0;
}
