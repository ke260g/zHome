#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

void atexit_handler(void) {
    printf("I exit.\n");
}
int main(int argc, char **argv) {
    atexit(atexit_handler);

    /* illegal memory access */
#if 0
    int *a = NULL;
    *a = 1;
#endif

    return 0;
}
