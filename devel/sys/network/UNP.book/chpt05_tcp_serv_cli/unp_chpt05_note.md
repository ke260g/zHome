# simple echo client and server
### boundary condition
+ what happens when the client and server are started
+ what happens when the client terminates normally
+ what happens to the client
    if server host crashes
+ what happens to the client
    if server process terminates before the client is done
+ etc

### what these scenarios happens happens on network level

### network with signal stuff
##### blocked signal stuff
+ the default signal handler is blocked
+ POSIX guarantees that no additional signals will
    be **blocked** while signal handler is running
    **blocked** means can not be dilivered to process
+ be careful, Unix signals is **not queued**
+ by `sigemptyset(sa_mask)` and `sigaction()'
    signal handler can be **nonblocked**, which means
    signal can be **dilevered** instead of **discard**
+ selectively block and unblock a set of signals
    using `sigprocmask()`,
    protect a critical region of code,
    avoid certain signals being caught
    while that region of code is executing

##### SIGCHLD
+ `fork()' type concurrent server need to handling
+ child-process become zombine-process
    after service routines is done
+ zombines take up kernel-space, they must be cleaned
+ functions like `wait()` are using to clean zombines
+ But, `waitpid()` is the most useful one

##### SIGPIPE
+ when a process `write()` to a socket that has received
    and RST, the SIGPIPE is sent to the process,
    SIGPIPE default to terminates the process
+ the process must catch the SIGPIPE or set to ignore
+ either ignore or signal-handler return,
    `write()` return, `errno == EPIPE`
+ but first time receiced RST, write return successfully

##### slow system call
+ like `accept()`, `read()` can block forever
+ these syscall will be interrupted by signal and
    after signal-hanlder done, these syscall will
    return **EINTR**, we must handle such situation
    prepare for them to return **EINTR**

##### purposes for handling network with signal stuff
1. server must catch the SIGCHLD signal when `fork()` child
2. must handle slow syscall interrupted by signal
3. SIGCHLD handler must coded correctly with `waitpid()`
    to prevent and zombies from being left around
4. client has to catch SIGPIPE

### connection abort before accept()
##### details of aborted-connection scenario
1. three-way handshake completes,
2. the connection is established
3. before server calls accept(), client send RST
##### aborted connection is implementation
1. BSD, server, handled it completely in kernel
2. SVR4, server, accept() returns EPROTO
3. POSIX, server, accept() returns ECONNABORTED,
    because of EPROTO means fatal protocol-error,
    when ECONNABORTED, server can re-call accept()
4. any client do not know
    whether server calls accept() again or not

### Server disconnection
##### Crashing of Server Host
##### Crashing and Rebooting of Server Host
##### Shutdown of Server Host

### Data Format
##### passing text strings between server and client
##### passing binary structures between server and client
+ encounter the endian problem
+ encounter the C datatype implementation difference
+ encounter structure align problem
+ it is never wise to pass binary structures

##### Pass all numeric data as text strings
