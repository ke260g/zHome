
/*
 * epoll(); syscall test
 * only in linux
 * usage :
 * $ ./<execuate_file_name>  < <path/to/a/file>
 * $ ./<execuate_file_name>
 */

#include<stdio.h>
#include<unistd.h>
#include<sys/epoll.h>
#include<stdlib.h>

#define TIMEOUT 5

#define t_malloc(type) (type *)malloc(sizeof(type))
typedef struct pollfd pollfd_s;

int main(int argc, char **argv){
    int epfd = epoll_create(1);
    if(epfd == -1) {
        perror("epoll_create()");
        return EXIT_FAILURE;
    }

    enum {EVENT_STDIN, EVENT_STDOUT};
    struct epoll_event **event = (struct epoll_event **)malloc(sizeof(struct epoll_event *) * 2);

    event[EVENT_STDIN] = (struct epoll_event *)malloc(sizeof(struct epoll_event));
    event[EVENT_STDOUT] = (struct epoll_event *)malloc(sizeof(struct epoll_event));

    int __ret;

    event[EVENT_STDIN]->events = EPOLLIN;
    __ret = epoll_ctl(epfd,
            EPOLL_CTL_ADD,
            STDIN_FILENO,
            event[EVENT_STDIN]);
    if(!__ret) {
        perror("epoll_ctr()");
        return EXIT_FAILURE;
    }

    event[EVENT_STDOUT]->events = EPOLLOUT;
    __ret = epoll_ctl(epfd,
            EPOLL_CTL_ADD,
            STDOUT_FILENO,
            event[EVENT_STDOUT]);
    if(!__ret) {
        perror("epoll_ctr()");
        return EXIT_FAILURE;
    }

    printf("stdin is readable\n");

    printf("stdout is writable\n");

    free(event[EVENT_STDIN]);
    free(event[EVENT_STDOUT]);
    free(event);


    return EXIT_SUCCESS;
}
