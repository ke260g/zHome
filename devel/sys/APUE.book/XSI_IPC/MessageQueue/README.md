# Demo to show how a message queue work.
> using api `msgctl()`, `msgget()`, `msgsnd()`, `msgrcv()`

### Suggested Backgroud Knowledge (at least)
+ Section 15.6 to 15.7, Chapter 15, APUE e3
+ man 2 open or the sys-call `open()' usage

### usage:
1. `<shell prompt>$ make`
2. `<shell prompt>$ ./msg_que_server`
3. type CTRL-Z
4. `<shell prompt>$ ./msg_que_client`
5. `<shell prompt>$ fg %./msg_que_server`
6. type ENTER

##### Working Flow(According to the usage)
1. Build 2 program, one is *client*, the other is *server*.
2. Run the *server*, the server create a message queue, send a **secret message** and wait.
3. CTRL-Z is to suspend the *server*, but the msg_que is keeping.
4. Run the *Client*, get the **secret message** from the msg_que created by the *server*.
5. Allow the *server* come back to the foreground.
6. ENTER is used to destroy the msg_que. This behavior can be refered to the source code.

### Note:
* msg_que means message queue
### Reference
+ man-pages of related api.
