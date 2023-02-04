CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -I./

all: compile run clean

# Variables:
# NUM = Enter the test number to run
# PREV = Previous command before ./a.out as strace
compile:
	$(CC) $(CFLAGS) $(NUM)-main.c

run:
	$(PREV) ./a.out

clean:
	rm a.out

heap: # Use the following command to explore the heap
	cat /proc/$(shell pgrep a.out)/maps

betty:
	betty *.c
