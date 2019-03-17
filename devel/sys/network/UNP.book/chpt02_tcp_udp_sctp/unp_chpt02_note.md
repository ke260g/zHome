+ what is handled by protocol
+ what is handled by the application

### A big picture of TCP/IP family.

+ **IPv4**, 1980s, 32-bit addr, (TCP/UDP/SCTP/ICMP/IGMP)
+ **IPv6**, 1990s, 128-bit addr, (TCP/UDP/SCTP/ICMPv6)
+ **TCP**, Transport Control Protocol,
    **connection-oriented**, full-duplex *byte-stream*
+ **UDP**, User Datagram Protocol, connectionless
+ **SCTP**, Stream Control Transmission Protocol,
    **message-oriented**, full-duplex *association*
+ **IGMP**, Internet Group Management Protocol,
    multicasting, optional with IPv4
+ **ICMP**, Internet Control Message Protocol,
    error and ctrl info between routers and hosts
+ **ICMPv6**,
+ **ARP**, Address Resolution Protocol,
    maps an IPv4 addr into a hardware addr
+ **RARP**, Reverse Address Resolution Protocol,
    maps a hardware addr into an IPv4 addr
+ **BPF**, BSD Packet Filter, access to the datalink layer, BSD-kernel
+ **DLPI**, DataLink Provider Interface, access to datalink layer, SVR4

---
### Protocol and its RFCs
| Protocol | RFCs |
|:-:|:--|
| UDP | RFC 768 |
| TCP | RFC 793, RFC 1323, RFC 2581, RFC 3390 |
| SCTP | RFC 2960, RFC 3309, RFC 3286 |

---
### TCP features
+ retransmit if an ack is not received in a certain time.
+ estimate the round-trip time (RTT) between client and server,
    (how long to wait an ack)
+ sequencing, associate a sequence-number for each byte
+ data-unit: segment
+ flow control, advertised window,
    changes dynamically over time, 2-windows(cli/serv)
+ full-duplex
+ byte-stream, only between one server and one client

---
### SCTP features
+ full-duplex, sequencing, flow control like TCP
+ message-oriented, sequenced delivery of individual records
+ multiple streams between a single connection
+ multihoming, multi-IP-addr at a same time

---
### TCP Connection Establishment and Termination
##### refer the 11 states provided by `man netstat`, and state-diagram
##### Three-Way Handshake ( 3 segments ) ( analogy of telephone )
1. server, passive open, `socket()`, `bind()`, `listen()`
2. client, active open, `connect()`, **send:client-SYN**
3. server, **recv:client-SYN**,
    **send:client-SYN-ack** and
    **send:server-SYN** in a single segment
4. client, **recv:client-SYN-ack**, **send:server-SYN-ack**

##### TCP options ( each SYN can contain TCP optins )
+ MSS, maximum segment size
+ Window scale, specify **bigger** advertised window size
+ Timestamp, prevent possible data corruption caused by
    old, delayed or duplicated segments.

##### Termination ( 3 or 4 segments, as 2. and 3. can be combined )
1. *one*, active close, `close()`, **send:one-FIN**
2. *the_other*, passive close, recv:one-FIN, send:one-FIN-ack
3. sometimes later, *the_other* `close()`, send:the_other-FIN
4. *one*, recv:one-FIN-ack,
    sometimes later, recv:the_other-FIN, send:the_other-FIN-ack

##### TCP termination special points
+ TIME_WAIT,
    1. to implement full-duplex-close reliably, allow *half-closed*
    2. to allow old duplicate segments to expire
+ MSL, maximum segment lifetime
+ routing anomlies, do routing-loops, lost-packet becomes duplicate

---
### SCTP Association Establishment and Termination
##### state-diagram
##### Four-Way Handshake ( 4 segments )
1. server, passive open, `socket()`, `bind()`, `listen()`
2. client, active open, `connect()`, send:INIT-msg
3. server, recv:INIT-msg, send:INIT-Ack-msg[cookie, etc]
4. client, recv:INIT-Ack-msg, send:cookie-echo-msg
5. server, send:cookie-echo-Ack-msg

##### Termination
1. *one*, active close, send:SHUTDOWN
2. *the_other*, passive close, send:SHUTDOWN-ACK
3. *one*, send:SHUTDOWN-COMPLETE
+ Note: SCTP do not need TIME_WAIT, as msg is always with tags.

---

### Port Number
+ port number is maintained by IANA
+ server uses **well-known port**
+ client uses **ephemeral port**

##### Port Number Range
1. well-known ports, 0~1023, assigned by superior only
2. registered-ports, 1024~49151,
3. dynamic/private ports, 49152~65535, **ephemeral ports**

###### Socket Pair
+ TCP, four-tuple, Local-IP, Local-Port, Foreign-IP, Foreign-Port
+ SCTP, a set of each one

##### Buffer Sizes and Limitations
+ maximum size of an IPv4 datagram is 2^16 bytes, including header
+ IPv6, jumbo payload option, only for mtu > 2^16 bytes
+ MTU, Maximum Transmission Unit, dictated by hardware
+ path-MTU, smallest MTU in the path between two hosts
+ Ethernet MTU, 1500 bytes, often as the path-MTU
+ Datagram-Size > MTU, IP(v6) perform fragmentation

---
### Standard Internet Services
##### those services are provided by `inetd` daemon on Unix
| Name | TCP port | UDP port | RFC | Description |
|:-:|:-:|:-:|:-:|:-:|
| echo | 7 | 7 | 862 | echo back |
| discard | 9 | 9 | 863 | discard |
| daytime | 13 | 13 | 867 | date, time |
| chargen | 19 | 19 | 864 | etc |
| time | 37 | 37 | 868 | date, time |

##### Protocol Usage by Common Internet Application
Section 2.13, Figure 2.19
