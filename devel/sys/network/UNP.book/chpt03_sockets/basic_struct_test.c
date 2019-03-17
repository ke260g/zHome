#include<netinet/in.h>
#include<stdio.h>

struct my_int {
    int value[20];
};
int main(int argc, char **argv) {
    int s = 0;
    struct my_int emx_int;
    struct sockaddr_in ad;

    emx_int.value[0] = 1286;
    printf("%p, %p.\n", &ad, &emx_int);
    printf("%p.\n", &ad.sin_family);
    printf("size of struct sockaddr_in is %ld bytes.\n", sizeof(struct sockaddr_in));
    printf("size of sa_family_t is %ld bytes.\n", sizeof(sa_family_t));
    printf("size of in_port_t is %ld bytes.\n", sizeof(in_port_t));
    printf("size of struct in_addr is %ld bytes.\n", sizeof(struct in_addr));
    printf("size of sin_zero is %ld bytes.\n", sizeof(ad.sin_zero));
    return 0;
}
