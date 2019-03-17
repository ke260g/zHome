# compiler
CC ?= ${CROSS_COMPILE}gcc
AR ?= ${CROSS_COMPILE}ar
CFLAGS ?= -Wall -O2 -I../include
LDFLAGS ?= -L../lib -lgpiox

# libs
LIB_GPIOX = ../lib/libgpiox.a
PUBLIC_HEADER = ../include/gpiox.h

# current dir objects
OBJS = gpiox.o demo.o

# default target
defualt: ${LIB_GPIOX} ${PUBLIC_HEADER} demo
demo: demo.o
	$(CC) ${CFLAGS} -o $@ $< ${LDFLAGS}

# libs and objs
%.o:
${LIB_GPIOX}: gpiox.o
	$(AR) rcs $@ $^
${PUBLIC_HEADER}: gpiox.h
	cp $< $@

# cleanup
clean:
	${RM} demo
distclean: clean
	${RM} ${OBJS} ${LIB_GPIOX} ${PUBLIC_HEADER}
