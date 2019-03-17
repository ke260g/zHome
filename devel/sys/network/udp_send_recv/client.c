#include"udp_send_recv.h"

#define ECHO_PORT (2046)
int main(void) {
    char str[12] = "I am client.";
    udp_send(str, 12, "127.0.0.1", ECHO_PORT);
    return 0;
}
