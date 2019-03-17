/*
 * poll(); syscall test
 * usage :
 * $ ./<execuate_file_name>  < <path/to/a/file>
 * $ ./<execuate_file_name>
 */

#include<stdio.h>
#include<unistd.h>
#include<sys/poll.h>
#include<stdlib.h>

#define TIMEOUT 5

#define t_malloc(type) (type *)malloc(sizeof(type))
typedef struct pollfd pollfd_s;

int main(int argc, char **argv){
    pollfd_s fds[2];

    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    fds[1].fd = STDOUT_FILENO;
    fds[1].events = POLLOUT;

    int __ret = poll(fds, 2, TIMEOUT * 1000);
    /*
     * change the second parameter '2' to '1',
     * re-compile and run.
     */

    if(__ret == -1) {
        perror("poll");
        return EXIT_FAILURE;
    } else if (!__ret) {
        printf("%d seconds elapsed.\n", TIMEOUT);
        return 0;
    }

    if(fds[0].revents & POLLIN)
        printf("stdin is readable\n");

    if(fds[1].revents & POLLOUT)
        printf("stdout is writable\n");

    return EXIT_SUCCESS;
}
