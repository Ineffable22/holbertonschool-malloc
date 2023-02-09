CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -I./

naive_malloc:
	$(CC) $(CFLAGS) naive_malloc.c test/main_naive.c
	./a.out
	rm a.out

malloc:
	$(CC) $(CFLAGS) malloc.c test/main.c
	./a.out
	rm a.out

malloc2:
	$(CC) $(CFLAGS) malloc.c test/compare.c free.c 
	./a.out
	rm a.out

malloc3:
	$(CC) $(CFLAGS) malloc.c test/main_2.c free.c 
	./a.out
	rm a.out

free:
	$(CC) $(CFLAGS) malloc.c free.c test/main_free.c
	./a.out
	rm a.out

free2:
	$(CC) $(CFLAGS) malloc.c free.c test/main_free2.c
	./a.out
	rm a.out

calloc:
	$(CC) $(CFLAGS) malloc.c free.c calloc.c test/main_calloc.c
	./a.out
	rm a.out

realloc:
	$(CC) $(CFLAGS) malloc.c free.c calloc.c realloc.c test/main_realloc.c
	./a.out
	rm a.out

betty:
	betty *.c *.h