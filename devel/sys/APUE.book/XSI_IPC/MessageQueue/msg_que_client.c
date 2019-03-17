#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<string.h>

#include"msg_que_protocol.h"

msgbuf_t msg_buf;

int main(int argc, char **argv) {
    int ret,
        msg_que_id;
    key_t msg_que_key;

    msg_que_key = ftok(KEY_PATHNAME, KEY_ID);
    msg_que_id = msgget(msg_que_key, IPC_PRIVATE);

    if(msg_que_id == -1) {
        perror("Error to msgget()");
        goto err1;
    }

    ret = msgrcv(msg_que_id, &msg_buf, MAX_BUF_SIZE,
            MES_BUF_MTYPE, MSG_NOERROR | IPC_NOWAIT);

    if(ret == -1) {
        perror("Error to msgrcv()");
        return 0;
    }

    printf("key : 0x%x\n", msg_que_key);
    printf("id  :   %d\n", msg_que_id);
    printf("This is msg_que client.\n");
    printf("I get the secret message : %s.\n", msg_buf.mtext);

err1:
    return 0;
}
