#ifndef UNP_SEND_RECV_H
#define UNP_SEND_RECV_H

// simple wrapper for udp recvfrom() and sendto() */
/*
 * @brief udp send buffer
 * @param buf buffer needed to be sent
 * @param len size of buf
 * @param ipv4_addr as its name
 * @return always return 0
 */
int udp_send(const void *buf,
        int len,
        const char *ipv4_addr,
        const int port);
/*
 * @brief udp receive buffer
 *      a block function
 * @param buf buffer will be received
 * @param len size of buf
 * @return actually bytes receive
 *      or -1 if time out or error eccurred
 */
int udp_recv(void *buf,
    const int len,
    const int port);

/*
 * @brief udp receive buffer
 *      after wait_second function return
 * @param buf buffer will be received
 * @param len size of buf
 * @param wait_second
 * @return actually bytes receive
 *      or -1 if time out or error eccurred
 */
int udp_recv_wait(void *buf,
    const int len,
    const int port,
    const int wait_second);
#endif /* UNP_SEND_RECV_H */
