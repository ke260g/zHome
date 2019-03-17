#include<unistd.h>
#include<sys/uio.h>

ssize_t naive_writev(int fd, const struct iovec *iov, int count) {
    ssize_t __ret = 0;

    int i;
    for ( i = 0; i < count; i++ ) {
        ssize_t nr = write(fd, iov[i].iov_base, iov[i].iov_len);
        if(nr == -1) {
            __ret = -1;
            break;
        }
        __ret += nr;
    }
    return __ret;

}
