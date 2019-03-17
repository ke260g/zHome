#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>

#include<stdio.h>
#include<stdlib.h>

#define TIMEOUT 5
#define BUF_LEN 1024

#define t_malloc(type) (type *)malloc(sizeof(type))

typedef struct timeval timeval_s;

int main(void) {
    timeval_s *tv = t_malloc(timeval_s);
    fd_set *readfds = t_malloc(fd_set);

    FD_ZERO(readfds); /* clear all the fd in the 'readfds' fd_set */
    FD_SET(STDERR_FILENO, readfds);/* wait the stdin input the data */

    tv->tv_sec = TIMEOUT; /* wait 5 second */
    tv->tv_usec = 0;

    int __ret; /* to store the syscal return value */
    __ret = select(STDERR_FILENO + 1,
                readfds,
                NULL,
                NULL,
                tv);
    if(__ret == -1) {
        perror("select()");
        return EXIT_FAILURE;
    } else if(!__ret)  {
        printf("%d seconds elapsed.\n", TIMEOUT);
        return EXIT_SUCCESS;
    }

    printf("Now the select() return %d.\n", __ret);

    if(FD_ISSET(STDERR_FILENO, readfds)) {
        char buf[BUF_LEN + 1];
        int len;

        fprintf(stdout, "Let's see the 'timeval'.\n"
                        "timeval->tv_sec : %ld\n"
                        "timeval->tv_usec : %ld\n",
                        tv->tv_sec, tv->tv_usec);

        len = read(STDERR_FILENO, buf, BUF_LEN);
        if(len == -1) {
            perror("read()");
            return EXIT_FAILURE;
        } else if(len) {
            buf[len] = '\0';
            printf("read from stdin is : %s\n", buf);
        }

        return EXIT_SUCCESS;
    }
    fprintf(stderr, "Some error occurs\n");
    return EXIT_FAILURE;
}
