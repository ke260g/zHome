#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/fcntl.h>

#include<stdio.h>
#include<stdlib.h>

int main(void) {
    int fd = open("/home/ll/1.txt", O_RDONLY);
    void *p = malloc(10);
    void *ptr = mmap(0, 10, PROT_READ, MAP_SHARED, fd, 0);
    printf("ptr == %p\n", ptr);
    printf("p == %p\n", p);
    while(1);
    return 0;
}
