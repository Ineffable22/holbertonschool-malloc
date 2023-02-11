/* Description: Allocating 3 times 8,192 bytes, free the first chunk, and allocate some chunks that should fit in the 8,192 bytes chunk that was just freed */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "malloc.h"

#define ALLOC_SIZE 8192
#define ALLOC_NB 3

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
	int i;
	void *ptr[ALLOC_NB];
	void *old;

	/* Allocate and initialize memory chunks */
	for (i = 0; i < ALLOC_NB; i++)
	{
		ptr[i] = _malloc(ALLOC_SIZE);
		if ((unsigned long int)ptr[i] % 8 != 0)
		{
			fprintf(stderr, "Address is not correctly aligned\n");
			return (EXIT_FAILURE);
		}
		memset(ptr[i], 'H', ALLOC_SIZE);
	}

	/* Make sure that allocated chunks are left intact, and free them */
	for (i = 0; i < ALLOC_NB; i++)
	{
		int j;

		for (j = 0; j < ALLOC_SIZE; j++)
		{
			if (((char *)ptr[i])[j] != 'H')
			{
				fprintf(stderr, "Allocated memory has been overwritten\n");
				return (EXIT_FAILURE);
			}
		}
	}

	/* Free the middle chunk, and allocate a smaller chunk */
	old = ptr[1];
	_free(ptr[1]);

	ptr[1] = _malloc(500);
	if (ptr[1] != old)
	{
		fprintf(stderr, "Malloc should use the first big enough freed chunk available\n");
		return (EXIT_FAILURE);
	}
	for (i = 0; i < 10; i++)
	{
		void *p;

		p = _malloc(500);
		if (p > ptr[2] || p < ptr[1])
		{
			fprintf(stderr, "Malloc should use the first big enough freed chunk available\n");
			return (EXIT_FAILURE);
		}
	}

	printf("OK\n");
	return (EXIT_SUCCESS);
}
