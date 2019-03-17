#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#include<sys/resource.h>
#include<sys/time.h>

int main(int argc, char **argv){
    errno = 0;
    int ret;
    int __err;
#if 0
    ret = nice(-3);

    __err = errno;
    if(errno != 0) {
        perror("nice()");
        printf("errno value is %d \n", __err);
    }
    printf("Nice value is currently %d\n", getpriority(0,0));

    printf("------------\n");
#endif

    nice(30);
    __err = errno;
    if( __err== EINVAL ) {
        printf("yes\n");
    }

    if( errno != 0 ) {
        perror("nice()");
        printf("errno value is %d \n", __err);
    }
    else
        printf("Nice value is currently %d\n", getpriority(0,0));
    printf("errno value is %d \n", __err);

    printf("EPERM == %d\n", EPERM);
    printf("EINVAL == %d\n", EINVAL);
    return EXIT_SUCCESS;
}
