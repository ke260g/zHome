#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>

int main(int argc, char **argv){
    printf("%ld\n", sysconf(_SC_FSYNC));
    printf("%ld\n", sysconf(_SC_IPV6));
    printf("%ld\n", sysconf(_SC_PAGE_SIZE));
    printf("%d\n", getpagesize());

    printf("_SC_V7_ILP32_OFF32 %ld\n", sysconf(_SC_V7_ILP32_OFF32));
    printf("_SC_V7_ILP32_OFFBIG %ld\n", sysconf(_SC_V7_ILP32_OFFBIG));
    printf("_SC_V7_LPBIG_OFFBIG %ld\n", sysconf(_SC_V7_LPBIG_OFFBIG));
    printf("_SC_V7_LP64_OFF64 %ld\n", sysconf(_SC_V7_LP64_OFF64));

    return EXIT_SUCCESS;
}
