```c
int socket(int family, int type, int protocol);
/* @family, AF_INET, AF_INET6, AF_LOCAL, AF_ROUTE, AF_KEY
 * @type, SOCK_STREAM, SOCK_DGRAM, SOCK_SEQPACKET, SOCK_RAW
 * @protocol, IPPROTO_TCP, IPPROTO_UDP, IPPROTO_SCTP
 *
 * @family, another group is PF_xxx
 *  1. AF_xxx means Address Family
 *  2. PF_xxx means Protocol Family */
```

---
```c
int connet(int sockfd,
        const struct sockaddr *servaddr,
        socklen_t addrlen);
/* When TCP, intialize the TCP three-handshake */
```

---
+ ARP, Asking for that host to Respoend with hardware address

---
```c
int bind(int sockfd,
        struct sockaddr *myaddr,
        socklen_t addrlen);
/* assigns a local protocol address to a socket,
 * the actual socket address can be known by
 * `getsockname()' only */
```

---
### Server Wildcard IP Address
+ INADDR_ANY, a macro, means *wildcard* IPv4 address
    ```c
    struct sockaddr_in servaddr;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    ```

+ in6addr_any, *wildcard* IPv6 address
    ```c
    struct sockaddr_in6 serv;
    serv.sin6_addr = in6addr_any;
    ```

---
### Server(s), bind wildcard IP versus non-wildcard IP
+ wildcard IP
    1. single server
    2. when a connection arrives,
    3. `getsockname()' to obtain client IP
+ non-wildcard IP
    1. multi server, each with a IP and domain-name
    2. the set of IPs are in a same subnet
    3. all IPs aliased onto a single network-interface
        `$ ifconfig alias`
    4. a **Ctrl Server**, binding to all IPs in subnet
    5. when connection arrives,
    6. **Ctrl Server** bind client IP for the required IP
+ which is advanced?
    + what issues handled by kernel
    + what issues handled by server-process
    + distinguish weak and strong end system
        1. the interface on which a packet arrives
        2. the destination IP of that packet

---
```c
int listen(int sockfd, int backlog);
/* performs 2 actions:
 *  passive activate a unconnected socket
 *  specify the maximum queued connections in kernel
 *
 * kernel maintains 2 queue:
 *  incomplete connection queue, sockets are in SYN_RCVD
 *  complete connection queue, sockets are in ESTABLISHED
 *
 * @backlog specify the sum of both
 *  do not set it `0', which is implement-defined
 *
 * large `backlog`, incompleted queue can grow
 * DoS attack, SYN-flooding, incomplete queue
 * What if specify the completed queue sum ? */
```

---
```c
int accept(int sockfd,
    struct sockaddr *cliaddr,
    socklen_t *addrlen);
/* @cliaddr, @addrlen used to
 * return the conneted client's IP
 *
 * return value is the new-fd, conneted socket versus
 * sockfd input `bind()', `listen()' is listening socket */
```
---
+ sockfd can't actually closed by `close()`, but `shutdown()`

---

