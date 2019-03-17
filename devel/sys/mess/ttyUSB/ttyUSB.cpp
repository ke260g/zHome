#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<termio.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

#include"ttyUSB.hpp"

/*
 * private function
 * compative with C,
 * easily clone out into C interface
 */

/*
 * @brief write "n" bytes to a descriptor
 * @param fd input parameter, fd to write
 * @param buf input parameter, pointer to buffer will be written
 * @param count number of bytes to write
 * @return return number of bytes actually written
 */
static ssize_t writen(int fd, const void *buf, size_t count) {
    /* Write "n" bytes to a descriptor. */
    size_t		nleft;
    ssize_t		nwritten;
    const char	*ptr;

    ptr = (char *)buf;
    nleft = count;
    while (nleft > 0) {
        if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;		/* and call write() again */
            else
                return(-1);			/* error */
        }

        nleft -= nwritten;
        ptr   += nwritten;
    }
    return(count);
}

/* @breif read "n" bytes from a descriptor
 * @param fd, input parameter, fd to read
 * @param buf output parameter, read fd to store
 * @param count number of bytes actually read
 * @return return number of bytes actually read
 */
static ssize_t readn(int fd, void *buf, size_t count) {
	size_t	nleft;
	ssize_t	nread;
	char	*ptr;

	ptr = (char *)buf;
	nleft = count;
	while (nleft > 0) {
		if ( (nread = read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0;		/* and call read() again */
			else
				return(-1);
		} else if (nread == 0)
			break;				/* EOF */

		nleft -= nread;
		ptr   += nread;
	}
	return(count - nleft);		/* return >= 0 */
}

/*
 * @brief print the error message
 *      the orignal errno will be restored after return
 * @param s embedded debug string
 */
static void error_msg(const char *s) {
    int errno_r; /* errno restore */
    errno_r = errno;
    fprintf(stderr, "%s: %s: %s: %s\n",
        __FILE__, __func__, s, strerror(errno_r));
    errno = errno_r;
}

/*
 * @brief nice function to initialize a ttyUSB
 * @param br baud rate, only supports 9600, 19200, 115200
 * @param stop_bit 1 means one bit, 2 means two bits
 * @param dev_name dev_name, eg. /dev/ttyUSB0
 * @return return new the new file descriptor,
 *      or -1 if an error occurred.
 */
static int ttyUSB_init(const int br, const char par_mode,
    const int stop_bit, const char *dev_name) {
    int fd,
        ret;
    struct termios port_attr;

    memset(&port_attr, 0, sizeof(port_attr));
    switch (br) { /* check baud rate supported or not */
    case 9600:
        port_attr.c_cflag = B9600; break;
    case 19200:
        port_attr.c_cflag = B19200; break;
    case 115200:
        port_attr.c_cflag = B115200; break;
    default:
        error_msg("Not supported baud rate");
        errno = -EINVAL;
        return -1;
    }
    switch(par_mode) {
    case '0':
        port_attr.c_cflag &= ~PARENB; break;// shut off parity
    case '1':
        port_attr.c_cflag |= PARENB | PARODD; break;
    case '2':
        port_attr.c_cflag |= PARENB;
        port_attr.c_cflag &= ~PARODD;
        break;
    default:
        error_msg("Not supported parity mode");
        errno = -EINVAL;
        return -1;
    }

    switch(stop_bit) {
    case 1:
        port_attr.c_cflag &= ~CSTOPB; break;
    case 2:
        port_attr.c_cflag |= CSTOPB; break;
    default:
        error_msg("Not supported stop_bit");
        errno = -EINVAL;
        return -1;
    }

    fd = open(dev_name, O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd < 0) {
        error_msg("failed to open device");
        return -1;
    }

    tcflush(fd, TCIOFLUSH);
    // tcgetattr(fd, &port_attr);
    port_attr.c_iflag = IGNPAR | IGNBRK;
    port_attr.c_iflag &= ~IXON; port_attr.c_iflag &= ~IXOFF;
    port_attr.c_oflag = 0; // no remapping, no delays
    // port_attr.c_oflag |= OFILL; /* use fill-char delay */
    // port_attr.c_oflag &= ~OFILL; /* timed-delay */
    port_attr.c_cflag |= CS8; // char-8bits
    // port_attr.c_cflag &= ~CSIZE;
    port_attr.c_cflag |= CREAD; // enable reciever
    port_attr.c_cflag &= ~CRTSCTS; // disable RTS and CTS hardware control
    port_attr.c_cflag |= CLOCAL;

    ret = tcsetattr(fd, TCSANOW, &port_attr);
    if(ret < 0) {
        error_msg("failed to set tty attr");
        return -1;
    }
    tcflush(fd, TCIOFLUSH);
    return fd;
}


ttyUSB::ttyUSB() { }

ttyUSB::~ttyUSB() {
    if(fd > 0)
        close(fd);
}

int ttyUSB::_ttyUSB_init(const int br, const char par_mode,
   const int stop_bit, const char *dev_name) {
    fd = ttyUSB_init(br, par_mode, stop_bit, dev_name);
    return fd;
}

int ttyUSB::_writen(const void *buf, size_t count) {
    int ret;
    if(fd == -1)
        return -1;

    tcflush(fd, TCOFLUSH);
    ret = writen(fd, buf, count);
    usleep(50 * 1000);
    tcflush(fd, TCOFLUSH);
    return ret;
}

int ttyUSB::_readn(void *buf, size_t count) {
    int ret;
    if(fd == -1)
        return -1;
    // tcflush(fd, TCIFLUSH); 
    ret = readn(fd, buf, count);
    return ret;
}

int ttyUSB::_read(void *buf, size_t count) {
    int ret;
    if(fd == -1)
        return -1;
    ret = read(fd, buf, count);

    return ret;
}

void ttyUSB::_error_msg(const char *s) {
    return error_msg(s);
}

int ttyUSB::success(void) {
    return ((fd > 0) ? 0 : -1);
}
