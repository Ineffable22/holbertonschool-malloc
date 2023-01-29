#include "malloc.h"
#define ALIGNMENT(size) (size + (8 - (size % 8)))

/**
 * first_time - First routine to create pagiante
 * @page: Variable to store page number
 *
 * Return: A pointer to the first chunk of the page
 */
void *first_time(ssize_t *page)
{
	void *first_chunk;

	(*page) = sysconf(_SC_PAGESIZE);
	if ((*page) == -1)
	{
		fprintf(stderr, "first_time: sysconf error");
		return (NULL);
	}
	first_chunk = sbrk((*page));
	if (first_chunk == (void *)-1)
	{
		perror("first_time: sbrk error");
		return (NULL);
	}
	return (first_chunk);
}

/**
 * naive_malloc - Allocate enough memory to store
 * @size: Is the size needed to be allocated for the user
 *
 * Return: A pointer to the allocated memory that is suitably aligned
 * for any kind of variable
 */
void *naive_malloc(size_t size)
{
	static void *first_chunk;
	static size_t len;
	void *ptr, *next_block = NULL;
	size_t block = ALIGNMENT(size) + sizeof(size), i, block_size, tmp;
	ssize_t page;

	if (!len)
	{
		first_chunk = first_time(&page);
		if (!first_chunk)
			return (NULL);
	}
	for (i = 0, ptr = first_chunk; i < len; i++)
	{
		block_size = *(size_t *)ptr;
		ptr = (char *)ptr + block_size;
	}
	tmp = len ? *(size_t *)ptr : (size_t)page;
	next_block = ((char *)ptr) + block;
	while (tmp < (sizeof(size) * 2) + ALIGNMENT(size))
	{
		page = sysconf(_SC_PAGESIZE);
		if (page == -1)
		{
			fprintf(stderr, "naive_malloc_page: sysconf error");
			return (NULL);
		}
		if (sbrk(page) == (void *)-1)
		{
			perror("naive_malloc_page: sbrk error");
			return (NULL);
		}
		tmp += page;
	}
	*(size_t *)next_block = tmp - block;
	*(size_t *)ptr = block;
	len++;
	return ((char *)ptr + sizeof(size));
}
