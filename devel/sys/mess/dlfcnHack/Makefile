LIB_SRC=local_lib

default: lib_dir/${LIB_SRC}.so main

lib_dir/local_lib.so: ${LIB_SRC}.c
	gcc -fPIC -c ${LIB_SRC}.c
	gcc -shared -Wl,-soname,${LIB_SRC}.so.1 -o lib_dir/${LIB_SRC}.so.1 ${LIB_SRC}.o
	rm ${LIB_SRC}.o
	ln -s ${LIB_SRC}.so.1 lib_dir/${LIB_SRC}.so

main: main.c
	gcc -o main main.c -ldl

clean:
	rm -f main ${LIB_SRC}.o lib_dir/*
