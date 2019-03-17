# Makefile for the shudu solution project 

CFLAGS = -pipe -O2 -L. -fPIC
LIB = shudu

all: main lib

main: main.o  lib$(LIB).so maze.c
	@gcc $(CFLAGS) -l$(LIB) -o $@ $^

main.o: main.c

lib: lib$(LIB).so

lib$(LIB).so: $(LIB).c maze.c
	@gcc $(CFLAGS) -shared -o $@ $^
