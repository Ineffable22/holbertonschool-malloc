#include "malloc.h"

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
 * main - updating with correct checks
 *
 * Return: EXIT_FAILURE if something failed. Otherwise EXIT_SUCCESS
 */
int main(void)
{
	void *p;
	int i;
	size_t size_of_the_chunk;
	size_t size_of_the_previous_chunk;
	void *chunks[10];
	char prev_used;

	for (i = 0; i < 10; i++)
	{
		p = _malloc(1024 * (i + 1));
		chunks[i] = (void *)((char *)p - 0x10);
	}
	_free((char *)(chunks[3]) + 0x10);
	_free((char *)(chunks[7]) + 0x10);
	_free(NULL);

	for (i = 0; i < 10; i++)
	{
		p = chunks[i];
		printf("chunks[%d]: ", i);
		pmem(p, 0x10);
		size_of_the_chunk = *((size_t *)((char *)p + 8));
		prev_used = size_of_the_chunk & 1;
		size_of_the_chunk -= prev_used;
		size_of_the_previous_chunk = *((size_t *)((char *)p));
		printf("chunks[%d]: %p, size = %li, prev (%s) = %li\n",
		       i, p, size_of_the_chunk,
		       (prev_used ? "allocated" : "unallocated"), size_of_the_previous_chunk);
	}
	return (EXIT_SUCCESS);
}
