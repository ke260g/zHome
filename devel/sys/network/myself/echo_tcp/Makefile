CFLAGS = -O2

.PHONY: all clean

SERVER_NAME = server
CLIENT_NAME = client
HELPER_IFACE = parse_args_port

all: ${SERVER_NAME} ${CLIENT_NAME}

${HELPER_IFACE}.o: ${HELPER_IFACE}.c

${SERVER_NAME}.o: ${SERVER_NAME}.c

${CLIENT_NAME}.o: ${CLIENT_NAME}.c

${SERVER_NAME}: ${SERVER_NAME}.o ${HELPER_IFACE}.o
	${CC} -o $@ $^ ${LDFLAGS}

${CLIENT_NAME}: ${CLIENT_NAME}.o ${HELPER_IFACE}.o
	${CC} -o $@ $^ ${LDFLAGS}

clean:
	${RM} ${SERVER_NAME} ${CLIENT_NAME}

distclean: clean
	${RM} *.o
