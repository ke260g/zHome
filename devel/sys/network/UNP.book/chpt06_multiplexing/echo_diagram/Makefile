CFLAGS = -O2

.PHONY: all clean

SERVER_SELECT = server_select
SERVER_POLL = server_poll
SERVER_NAME = server
CLIENT_NAME = client
LDFLAGS = -L../.. -lunp

SERVERS = ${SERVER_NAME} ${SERVER_POLL} ${SERVER_SELECT}
all: ${SERVERS} ${CLIENT_NAME}

# client
${CLIENT_NAME}.o: ${CLIENT_NAME}.c
${CLIENT_NAME}: ${CLIENT_NAME}.o
	${CC} -o $@ $^ ${LDFLAGS}

# server
${SERVER_NAME}.o: ${SERVER_NAME}.c
${SERVER_NAME}: ${SERVER_NAME}.o
	${CC} -o $@ $^ ${LDFLAGS}

# extra server
${SERVER_POLL}.o: ${SERVER_POLL}.c
${SERVER_POLL}: ${SERVER_POLL}.o
	${CC} -o $@ $^ ${LDFLAGS}

${SERVER_SELECT}.o: ${SERVER_SELECT}.c
${SERVER_SELECT}: ${SERVER_SELECT}.o
	${CC} -o $@ $^ ${LDFLAGS}


clean:
	${RM} ${SERVERS} ${CLIENT_NAME}

distclean: clean
	${RM} *.o
