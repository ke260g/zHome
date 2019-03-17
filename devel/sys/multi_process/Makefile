MAIN = par_and_chi
BIN = 1 ${MAIN}
OBJS = ${addsuffix .o, ${BIN}}

CFLAGS = -Wall -O2

default: ${BIN}

${MAIN}: ${MAIN}.o
	${CC} -Wall -O2 -o $@ $^

1: 1.o
	${CC} -Wall -O2 -o $@ $^

%.o:

.PHONY: clean

clean:
	rm -f ${BIN}
distclean:
	rm -f ${BIN} ${OBJS}
