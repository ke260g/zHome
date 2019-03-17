#include<stdio.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<string.h>
#include<errno.h>
#include<sys/stat.h>

#include"msg_que_protocol.h"
const char *secret_msg = "Beautiful world";

msgbuf_t msg_buf = {
    .mtype = MES_BUF_MTYPE,
};

int main(int argc, char **argv) {
    int ret,
        msg_que_id;
    key_t msg_que_key;

    strncpy(msg_buf.mtext, secret_msg, strlen(secret_msg));
    msg_buf.mtext[strlen(secret_msg) + 1] = '\0';

    msg_que_key = ftok(KEY_PATHNAME, KEY_ID);

    msg_que_id = msgget(msg_que_key,
            IPC_CREAT| S_IRUSR |S_IWUSR);
    /* S_IRUSR, S_IWUSR is the `mode_t' bit,
     * defined in <sys/stat.h>
     * refered to the man 2 open */
    if(msg_que_id == -1) {
        perror("Error to msgget()");
        goto err1;
    }

    ret = msgsnd(msg_que_id, &msg_buf, sizeof(msg_buf), IPC_NOWAIT);
    if(ret) {
        perror("Error to msgsnd()");
        goto err2;
    }

    printf("key : 0x%x\n", msg_que_key);
    printf("id  :   %d\n", msg_que_id);
    printf("This is msg_que server.\n");
    printf("I have sent a secret message.\n");

    getchar();
    printf("Destroy the message queue and exit.\n");

err2:
    msgctl(msg_que_id, IPC_RMID, NULL);
err1:
    return 0;
}
