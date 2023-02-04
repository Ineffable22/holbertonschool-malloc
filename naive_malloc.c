#include "malloc.h"

/**
 * first_time - First routine to create pagiante
 * @page: Variable to store page number
 *
 * Return: A pointer to the first chunk of the page
 */
void *first_time(ssize_t *page)
{
	void *f_chunk;

	(*page) = sysconf(_SC_PAGESIZE);
	if ((*page) == -1)
	{
		fprintf(stderr, "first_time: sysconf error");
		return (NULL);
	}
	f_chunk = sbrk((*page));
	if (f_chunk == (void *)-1)
	{
		perror("first_time: sbrk error");
		return (NULL);
	}
	return (f_chunk);
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
	static void *f_chunk;
	static size_t length;
	void *ptr, *next_block = NULL;
	size_t block = ALIGNMENT(size) + sizeof(size), i, block_size, tmp;
	ssize_t page;

	if (!length)
	{
		f_chunk = first_time(&page);
		if (!f_chunk)
			return (NULL);
	}
	for (i = 0, ptr = f_chunk; i < length; i++)
	{
		block_size = *(size_t *)ptr;
		ptr = (char *)ptr + block_size;
	}
	tmp = length ? *(size_t *)ptr : (size_t)page;
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
	length++;
	return ((char *)ptr + sizeof(size));
}
