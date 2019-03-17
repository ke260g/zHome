/* such program is used to get the inode of the files */
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<stdlib.h>
#include<stdio.h>

int get_inode(int fd) {
    struct stat buf;
    int ret = fstat(fd, &buf);
    if(ret < 0) {
        perror("fstat()");
        return -1;
    }
    return buf.st_ino;
}

int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr, "usage: %s <file>...\n", argv[0]);
        return EXIT_FAILURE;
    }

    int fd, inode;
    int i;
    for ( i = 1; i < argc ; i++ ) {
        fd = open(argv[i], O_RDONLY);
        if(fd < 0) {
            perror("open()");
            return EXIT_FAILURE;
        }
        inode = get_inode(fd);
        printf("file %s inode is %d\n", argv[i], inode);

    }
    return EXIT_SUCCESS;
}
