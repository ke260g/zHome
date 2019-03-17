+ popular UDP apps: DNS, NFS, SNMP

### simple diagram
+ server: socket(), bind(), recvfrom()
+ client: socket(), sendto()

+ udp `send` returns successfully only means
    there was room on the send-buffer-queue
+ asyncronous error, ICMP error
    not returned on a connectionless UDP socket
+ UDP socket can be a connected one
    `connect()`, but no tcp-three-handshake
    user `write()`, `send()`
+ `connect()` multiple times for a UNP socket
    to specify a new IP address and port
    to unconnect the socket, AF_UNSPEC
+ unconnected UDP, `sendto()` 2 times in kernel
    1. temporarily connect the socket
    2. output first datagram
    3. temporarily unconnect the socket
    4. temporarily connect the socket
    5. output second datagram
    6. temporarily unconnect the socket
    after 1.,2.,3. may stores the routing table
+ connected UDP, `write()` in kernel
    1. temporarily connect the socket
    2. output first datagram
    3. output second datagram
    4. temporarily unconnect the socket

### lack of flow control with udp

### upd socket receive buffer

### determining outgoing interface with udp
