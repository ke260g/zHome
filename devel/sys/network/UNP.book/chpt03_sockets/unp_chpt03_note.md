+ 4 functions pass a socket addr from process to kernel
    `bind()`, `connect()`, `sendto()`, `sendmsg()`
+ 5 functions pass a socket addr from kernel to process
    `accept()`, `recvfrom()`, `recvmsg()`,
    `getpeername()`, `getsockname()`
+ `struct sockaddr_in6`, member `uint32_t sin6_flowinfo`
   + low-order 20 bits are the **flow-label**
   + high-order 20 bits are **reserved**
+ generic socket addr structure

### Byte Stuff
+ Internet Protocol use Big-Endian,
    1. Historical implementation, Digital VAX implementation, 4.2BSD
    2. where byte-order is big-endian
    3. Besides, `long` means 32 bits

+ byte-order convert interface `#include<netinet/in.h>`
    `htons()`, `htonl()`, `ntohs()`, `ntohl()`
    1. `h` means host, `n` means network
    2. `s` means 16 bits, `l` means 32 bits.

+ byte-manipulation `#include<strings.h>`
    1. `void bzero(void *dst, size_t nbytes);`
    2. `void bcopy(const void *src, void *dst, size_t nbytes);`
    3. `int bcmp(const void *ptr1, const void *ptr2, size_t nbytes);`

+ ip address convertion `#include<arpa/inet.h>`
 + between ascii and network byte-ordered **old functions**
     1. `int inet_aton(const char *strptr, struct in_addr *addrptr);`
     2. `in_addr_t inet_addr(const char *strptr); /* deprecated */`
     3. `char *inet_ntoa(struct in_addr inaddr);`
 + between ascii and socket address structure **new functions**
     1. `int inet_pton(int family, const char *strptr, void *addrptr);`
        `/* ascii to sockaddr */`
     2. `const char *inet_ntop(int family, const void *addrptr, char *strptr, size_t len);`
        `/* sockaddr to ascii, @strptr can not be NULL */`

### About Buffer Stuff
+ `read()`, `write()` may I/O fewer bytes than required as kernel-buffer limits
+ stdio-buffer-problem V.S. line-based protocol
+ better implementation interface for stream I/O
    1. `ssize_t readn(int fd, void *buff, size_t nbytes);`
    2. `ssize_t writen(int fd, const void *buff, size_t nbytes);`
    3. version 1, `ssize_t readline(int fd, void *buff, size_t maxlen);`
    4. version 2, `readline()`
