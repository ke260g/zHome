CFLAGS = -O2

.PHONY: all clean

SERVER_NAME = DaytimeServer
CLIENT_NAME = DaytimeClient

all: ${SERVER_NAME} ${CLIENT_NAME}

${SERVER_NAME}: ${SERVER_NAME}.c

${CLIENT_NAME}: ${CLIENT_NAME}.c

clean:
	${RM} ${SERVER_NAME} ${CLIENT_NAME}
