#ifndef __MSG_QUE_PROTOCOL__
#define __MSG_QUE_PROTOCOL__

#define KEY_PATHNAME "/dev/zero"    /* user-defined */
#define KEY_ID 4                    /* user-defined */

#define MAX_BUF_SIZE 128
#define MES_BUF_MTYPE 2
typedef struct msgbuf_t {           /* user-defined */
    long mtype;
    char mtext[MAX_BUF_SIZE];
} msgbuf_t;

#endif
