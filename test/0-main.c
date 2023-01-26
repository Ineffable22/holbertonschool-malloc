#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	void *ptr;

	ptr = sbrk(0);
	printf("Starting break is %p\n", ptr);

	return (EXIT_SUCCESS);
}
