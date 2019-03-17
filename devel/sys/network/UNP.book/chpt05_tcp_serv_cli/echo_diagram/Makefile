CFLAGS = -O2

.PHONY: all clean

SERVER_NAME = server
CLIENT_NAME = client
LDFLAGS = -L../.. -lunp

all: ${SERVER_NAME} ${CLIENT_NAME}

${SERVER_NAME}.o: ${SERVER_NAME}.c

${CLIENT_NAME}.o: ${CLIENT_NAME}.c

${SERVER_NAME}: ${SERVER_NAME}.o
	${CC} -o $@ $^ ${LDFLAGS}

${CLIENT_NAME}: ${CLIENT_NAME}.o
	${CC} -o $@ $^ ${LDFLAGS}

clean:
	${RM} ${SERVER_NAME} ${CLIENT_NAME}

distclean: clean
	${RM} *.o
