CC = gcc
CFLAGS = -std=c99 -pipe -O2 -fPIC -lm -L. -g

all:	bubble_method select_method insert_method \
		quick_method merge_method heap_method

COM = com_func.so sort_methods.so num_memb.o

num_memb.o: num_memb.c
com_func.so: com_func.c
	@gcc $(CFLAGS) -shared -o $@ $^

sort_methods.so: sort_methods.c
	@gcc $(CFLAGS) -shared -o $@ $^

bubble_method:	bubble_method.o $(COM)
bubble_method.o: bubble_method.c

insert_method: insert_method.o $(COM)
insert_method.o: insert_method.c

select_method: select_method.o $(COM)
select_method.o: select_method.c

merge_method: merge_method.o $(COM)
merge_method.o: merge_method.c

quick_method: quick_method.o $(COM)
quick_method.o: quick_method.c

heap_method: heap_method.o $(COM)
heap_method.o: heap_method.c

shell_method: shell_method.o $(COM)
shell_method.o: shell_method.c

clean:
	rm *.o
