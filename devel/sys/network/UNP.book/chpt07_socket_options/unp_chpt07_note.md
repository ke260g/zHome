+ levels in socket options
+ IP socket options for `getsockopt()` and `setsockopt()`
+ tcp/sctp socket options
+ socket states, option's timing consideration

### generic socket options, protocol-independent
+ **SO_BROADCAST**, not in p2p, tcp/sctp
+ **SO_DEBUG**, TCP only, kernel keeps track of details
+ **SO_DONTROUTE**,
+ **SO_ERROR**, **socket-pending error**
    1. `select()` return, errno set
    2. SIGIO
+ **SO_KEEPALIVE**, **keep-alive probe**, tcp segment
    timing parameter,
    detect and terminates half-open connection
    timeout implement
+ using `select()` to test whether a socket is readable
+ **SO_LINGER**, how `close()` operates for TCP/SCTP
    closed-socket send buffer, remaining-data go where
+ application-level ack
+ **SO_OOBINLINE**, MSG_OOB
+ **SO_RCVBUF**, **SO_SNDBUF**
    TCP-scale-option exchanges with peer on SYN
    client SO_RCVBUF must be set before `connect()`
    server SO_SNDBUF must be set before `listen()`
+ buffer minimum size is four times the MSS,
    four is a result of TCP's fast recovery algorithm
+ capacity of the pipe, bandwidth delay product
+ **SO_RCVLOWAT**, **SO_SNDLOWAT**, low-water-mark, `select()`
+ **SO_RCVTIMEO**, **SO_SNDTIMEO**, timeout
    `read()`, `readv()`, `recv()`, `recvfrom()`, `recvmsg()`
    `write(), `writev()`, `send()`, `sendto()`, `sendmsg()`
+ **SO_REUSEADDR**, **SO_REUSEPROT**
    all tcp server should specify SO_REUSEADDR
+ **SO_TYPE**, returns like SOCK_STREAM or SOCK_DGRAM
+ **SO_USELOOPBACK**, only for AF_ROUTE(routing domain)
    only option defaults to on

### IPv4 Socket Options
+ level of IPPROTO_IP
+ **IP_HDRINGCL**, set for raw-socket
    build our own IP-header for datagrams
+ **IP_OPTIONS**,
+ **IP_RECVDSTADDR**, `recvmsg()`
+ **IP_RECVIF**, `recvmsg()`
+ **IP_TOS**, Type-Of-Sevice
+ **IP_TTL**,
+ **IP_MULTICAST_TTL**

### ICMPv6 Socket Option
+ level of IPPROTO_ICMPV6
+ **ICMP6_FILTER**, fetch and set `struct icmp6_filter`

### IPv6 Socket Options
+ level of IPPROTO_IPV6
+ **IPV6_CHECKSUM**,
+ **IPV6_DONTFRAG**, a fragment for UDP and raw-socket
+ **IPV6_NEXTHOP**, specifies the next-hop addr
+ **IPV6_PATHMTU**, can only be retrived
+ **IPV6_RECVDSTOPTS**, ancillary data, `recvmsg()`:
    + any received-IPv6 dest-options
+ **IPV6_RECVHOPLIMIT**, ancillary data, `recvmsg()`:
    + received-hop-limit-field,
+ **IPV6_RECVHOPOPTS**, ancillary data, `recvmsg()`:
    + received-IPv6 hop-by-hop options
+ **IPV6_RECVPATHMTU**, ancillary data, `recvmsg()`:
    + path MTU of a path
+ **IPV6_RECVPKTINFO**, ancillary data, `recvmsg()`:
    + destination IPv6 addr
    + arriving interface index
+ **IPV6_RECVRTHDR**, ancillary data, `recvmsg()`:
    + received-IPv6 routing header
+ **IPV6_RECVTCLASS**, ancillary data, `recvmsg()`:
    + received traffic class, DSCP, ECN
+ **IPV6_UNICAST_HOPS**, hop-limit for outgoing datagrams
+ **IPV6_USE_MIN_MTU**, how to perform MTU discovery
+ **IPV6_V6ONLY**
+ IPV6_XXX,
    + header-modification, ancillary data
    + UDP, `recvmsg()`, `sendmsg()`
    + TCP, `getsockopt()`, `setsockopt()`

### TCP Socket Options
+ level of IPPROTO_TCP
+ **TCP_MAXSEG**, MSS of a tcp connection
+ **TCP_NODELAY**, disable Nagle algorithm
+ Nagle alogorithm:
    + reduce the number of small packets on a WAN
    + small means smaller than MSS
    + interacts with the delayed ACK algorithm
+ delayed ACK, ACK piggyback with the data
+ `writev()` versus **TCP_NODELAY**

### SCTP Socket Options
+ level of IPPROTO_SCTP
+ use `sctp_opt_info()` to receive these options
    + **SCTP_ASSOCINFO**, **SCTP_GET_PEER_ADDR_INFO**
    + **SCTP_PEER_ADDR_PARAMS**, **SCTP_PRIMARY_ADDR**
    + **SCTP_STOINFO**, **SCTP_STATUS**
+ **SCTP_ADAPTION_LAYER**, adaption-layer-indication, 32-bits
+ **SCTP_ASSOCINFO**, set and fetch `struct sctp_assocparams`
+ **SCTP_AUTOCLOSE**, autoclose time for an sctp-endpoint
+ **SCTP_DEFAULT_SEND_PARAM**, ancillary data, `sctp_sendmsg()`
    `struct sctp_sndrcvinfo`
+ **SCTP_DISABLE_FRAGMENTS**, fragment user message
+ **SCTP_EVENTS**, various SCTP notification
    `msg_flags set MSG_NOTIFICATION` in `recvmsg()`
    `struct sctp_event_subscribe`
+ **SCTP_GET_PEER_ADDR_INFO**
    `struct sctp_paddrinfo`
+ **SCTP_I_WANT_MAPPED_V4_ADDR**, IPv4-mapped addr on AF_INET
+ **SCTP_INITMSG**, `struct initmsg`
+ **SCTP_MAXBURST**, allow to set/fetch maximum burst size
+ **SCTP_MAXSEG**, allow to set/fetch maximum fragment size
+ **SCTP_NODELAY**, SCTP's Nagle algorithm
+ **SCTP_PEER_ADDR_PARAMS**, set/fetch params on association
    `struct sctp_paddrparams`
+ **SCTP_PRIMARY_ADDR**,
    `struct sctp_setprim`
+ **SCTP_RIOINFO**, `RIO infomation`
    `struct sctp_rioinfo`
+ **SCTP_SET_PEER_PRIMARY_ADDR**
    `struct sctp_setpeerprim`
+ **SCTP_STATUS**,
    `struct sctp_status`
