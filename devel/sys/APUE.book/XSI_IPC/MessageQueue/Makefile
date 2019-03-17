CLIENT = msg_que_client
SERVER = msg_que_server

OBJS = ${CLIENT}.o ${SERVER}.o
BIN = ${CLIENT} ${SERVER}

CFLAGS = -Wall -O2

default: ${CLIENT} ${SERVER}

%.o:

${CLIENT}: ${CLIENT}.o
	$(CC) ${CFLAGS} -o $@ $^

${SERVER}: ${SERVER}.o
	$(CC) ${CFLAGS} -o $@ $^

.PHONY: clean distclean
clean:
	rm -f ${CLIENT} ${SERVER}
distclean:
	rm -f ${OBJS} ${BIN}
