#include "malloc.h"

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	void *p1, *p2;
	char c = 'H';

	p1 = sbrk(0);
	printf("Starting break is %p\n", p1);
	p2 = sbrk(1);
	p2 = sbrk(0);
	printf("Break after extension is %p\n", p2);

	*(char *)p1 = c;
	printf("Address of our char is %p\n", p1);
	printf("Value at this address is %c\n", *(char *)p1);
	return (0);
}
