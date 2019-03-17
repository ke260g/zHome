# I/O Multiplexing

### 5 I/O Models
+ blocking I/O
+ nonblocking I/O (error of EWOULDLBOCK)
+ I/O multiplexing (`select()` and `poll()`)
+ signal driven I/O (SIGIO)
+ asynchronous I/O (`aio_*()`)

##### comparation of 5 I/O Models

##### comparation of 5 I/O Mdels

### select()
+ 3 possibilities for waiting
    + wait forever, @timeval is NULL
    + wait up to a fixed amount of time
    + do not wait at all, means polling

+ fd_set type manipulate interface
    + `void FD_ZERO(fd_set *);` clear
    + `void FD_SET(fd_set *);` turn on
    + `void FD_CLR(fd_set *);` turn off
    + `int FD_ISSET(int fd, fd_set *);` check

+ return situation
    + `select()` return the ready amount of fd or -1
    + @readfds, @writefds, @exceptfds are value-result params
    + after `select()` return, `FD_ISSET()` can be used to
        test a specific descriptor in an `fd_set`,
        any fd that is not ready will be clear in the `fd_set`

+ when socket ready for reading in select()
    + data in socket receive buffer is >= low-water-mark
        low-water-mark, 1 is for default TCP/UDP
        low-water-mark can be set with SO_RCVLOWAT
    + read half of connection is closed, TCP received FIN
    + a listening socket, tcp completed-connections is nonzero
    + a socket error is pending, `getsockopt() with SO_ERROR`
+ when socket ready for writing in select()
    + data in socket send buffer is >= low-water-mark
        and either (i)the socket is conneceted or
        (ii) the socket does not require a connection(UDP)
        low-water-mark can be set with SO_RCVLOWAT
    + write half of connection is closed, TCP received RST
    + nonblocking socket `connect()` has completed or failed
    + a socket error is pending, `getsockopt() with SO_ERROR`
+ when socket ready for exception condition pending
    + there is out-of-band data
    + socket is still at the out-of-band mark
+ FD_SETSIZE, a macro, specify when kernel compile
+ mixing stdio and select will cause numerous problem
    + the `select()` do not note about the stdio buffer
+ int shutdown(int sockfd, int howto);
    + @howto, one of SHUT_RD, SHUT_WR, SHUT_RDWR
    + SHUT_RD,
    + SHUT_WR,
    + SHUT_RDWR, first SHUT_RD, second SHUT_WR

##### a select() server limitation
+ client amount is limited by server's FD_SETSIZE
+ server is more easily suffer DoS-attacks
+ `select()` can not easily handle EINTR situation

### `poll(struct pollfd *fds, nfds_t nfds, int timeout)`
+ the limited client can be set with @nfds
+ instead of value-result, two members in `struct pollfd`
    events, input-param, events of interest on fd
    revents, output-param, events that occurred on fd
+ event and revents flags constant
   POLLIN, POLLRDNORM, POLLRDBAND, POLLPRI
   POLLOUT, POLLWRNORM, POLLWRBAND
   POLLERR, POLLHUP, POLLNVAL
+ @timeout can be set INFTIM, means forever
