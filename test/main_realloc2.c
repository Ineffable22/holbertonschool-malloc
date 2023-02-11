/* Description: Reallocating from 100 bytes to 100 bytes */
#include "malloc.h"

#define ALLOC_SIZE 100
#define REALLOC_SIZE 100

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
	long i;
	void *ptr;
	void *new;

	ptr = _malloc(ALLOC_SIZE);
	if ((unsigned long int)ptr % 8 != 0)
	{
		fprintf(stderr, "Address is not correctly aligned\n");
		return (EXIT_FAILURE);
	}
	memset(ptr, 'H', ALLOC_SIZE);

	new = _realloc(ptr, REALLOC_SIZE);
	if (new != ptr)
	{
		fprintf(stderr, "Realloc should do nothing when old size is the same as new size\n");
		return (EXIT_FAILURE);
	}
	ptr = new;

	for (i = 0; i < _MIN(ALLOC_SIZE, REALLOC_SIZE); i++)
	{
		if (((char *)ptr)[i] != 'H')
		{
			fprintf(stderr, "Memory has been overwritten\n");
			return (EXIT_FAILURE);
		}
	}

	printf("OK\n");
	return (EXIT_SUCCESS);
}
