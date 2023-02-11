#include "malloc.h"

#define ALLOC_SIZE 10
#define ALLOC_NB 26

/**
 * pmem - print mem
 * @p: memory address to start printing from
 * @bytes: number of bytes to print
 *
 * Return: nothing
 */
void pmem(void *p, unsigned int bytes)
{
	unsigned char *ptr;
	unsigned int i;

	ptr = (unsigned char *)p;
	for (i = 0; i < bytes; i++)
	{
		if (i != 0)
		{
			printf(" ");
		}
		printf("%02x", *(ptr + i));
	}
	printf("\n");
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
	int i;
	void *ptr[ALLOC_NB];
	size_t size_of_the_chunk;
	size_t size_of_the_previous_chunk;
	char prev_used;

	/* Allocate and initialize memory chunks */
	for (i = 0; i < ALLOC_NB; i++)
	{
		ptr[i] = (char *)_malloc(ALLOC_SIZE) - 0x10;
		if ((unsigned long int)ptr[i] % 8 != 0)
		{
			fprintf(stderr, "Address is not correctly aligned\n");
			return (EXIT_FAILURE);
		}
		memset((char *)ptr[i] + 0x10, 65 + i, ALLOC_SIZE);
	}

	/* Make sure that allocated chunks are left intact */
	for (i = 0; i < ALLOC_NB; i++)
	{
		if (i % 2 == 0)
			_free((char *)ptr[i] + 0x10);
	}

	for (i = 0; i < ALLOC_NB; i++)
	{
		printf("%s\n", (char *)ptr[i] + 0x10);
		printf("chunks[%d]: ", i);
		pmem(ptr[i], 0x10);
		size_of_the_chunk = *((size_t *)((char *)ptr[i] + 8));
		prev_used = size_of_the_chunk & 1;
		size_of_the_chunk -= prev_used;
		size_of_the_previous_chunk = *((size_t *)((char *)ptr[i]));
		printf("chunks[%d]: %p, size = %li, prev (%s) = %li\n",
		       i, ptr[i], size_of_the_chunk,
		       (prev_used ? "allocated" : "unallocated"), size_of_the_previous_chunk);
	}
	putchar(0xA);
	for (i = 0; i < ALLOC_NB; i++)
	{
		if (i % 2 != 0)
			continue;
		ptr[i] = (char *)_malloc(ALLOC_SIZE) - 0x10;
		if ((unsigned long int)ptr[i] % 8 != 0)
		{
			fprintf(stderr, "Address is not correctly aligned\n");
			return (EXIT_FAILURE);
		}
		memset((char *)ptr[i] + 0x10, 65 + i, ALLOC_SIZE);
	}

	for (i = 0; i < ALLOC_NB; i++)
	{
		printf("%s\n", (char *)ptr[i] + 0x10);
		printf("chunks[%d]: ", i);
		pmem(ptr[i], 0x10);
		size_of_the_chunk = *((size_t *)((char *)ptr[i] + 8));
		prev_used = size_of_the_chunk & 1;
		size_of_the_chunk -= prev_used;
		size_of_the_previous_chunk = *((size_t *)((char *)ptr[i]));
		printf("chunks[%d]: %p, size = %li, prev (%s) = %li\n",
		       i, ptr[i], size_of_the_chunk,
		       (prev_used ? "allocated" : "unallocated"), size_of_the_previous_chunk);
	}
	printf("OK\n");
	return (EXIT_SUCCESS);
}
