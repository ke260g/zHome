#include<stdio.h>
#include<setjmp.h>
#include<stdlib.h>
static jmp_buf buf;
#define LONGJMP_VAL (10)

// main():label1 -> main():branch1 -> corruption ->
// darkness() -> main():label1 -> main():branch2

void darkness(void) {
    printf("%s\n", __func__);
    longjmp(buf, LONGJMP_VAL);
    printf("line:%d\n", __LINE__); // this will not printf
}

void corruption(void) {
    darkness();
    printf("line:%d\n", __LINE__); // this will not printf
}

int main( int argc, char **argv ) {
    int ret;
    printf("%s %s\n", __DATE__, __TIME__);

    // first-time ret is 0,
    // second-time ret is passing-value from longjump
    ret = setjmp(buf); // label1

    printf("ret is %d\n", ret);
    if(!ret) // branch1
        corruption();
    else    // branch2
        printf("%s\n", __func__);
    return 0;
}
