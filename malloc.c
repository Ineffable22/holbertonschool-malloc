#include "malloc.h"

/**
 * first_time - Create the page and initialize memory and point
 * to the start address
 * @page: Variable to save the page
 *
 * Return: Pointer to the start address of the page
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
 * new_block - Allocate new pages on the heap
 * @ptr:   Pointer to allocated page
 * @len:   Number of pointers
 * @block: size of block to allocate
 * @page:  Value of page
 *
 * Return: Pointer to allocated page
 */
void *new_block(void *ptr, size_t *len, size_t block, ssize_t page)
{
	void *next_block;
	size_t tmp = 0;

	tmp = *len ? *(size_t *)ptr : (size_t)page;
	next_block = ((char *)ptr) + block;
	while (tmp < block)
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
	*(size_t *)((char *)ptr + sizeof(block_t)) = block;
	return (ptr);
}


/**
 * _malloc - Allocate enough memory to store
 * @size: Is the size needed to be allocated for the user
 *
 * Return: A pointer to the allocated memory that is suitably aligned
 * for any kind of variable
 */
void *_malloc(size_t size)
{
	void *ptr;
	block_t *tmp_block;
	size_t block = ALIGNMENT(size) + sizeof(block_t) + sizeof(size);
	size_t i, block_size, flag = 0;
	ssize_t page = 0;

	/* Find address */
	if (len == 0)
	{
		first_chunk = first_time(&page);
		if (!first_chunk)
			return (NULL);
	}

	for (ptr = first_chunk, i = 0; i < len; i++)
	{
		block_size = *(size_t *)((char *)ptr + sizeof(block_t));
		tmp_block = (block_t *)ptr;
		if (tmp_block->used == 0 && block_size <= block)
		{
			flag = 1;
			break;
		}
		ptr = (char *)ptr + block_size;
	}
	if (!flag)
		ptr = new_block(ptr, &len, block, page);
	tmp_block = (block_t *)ptr;
	tmp_block->start = first_chunk;
	tmp_block->used = 1;
	len++;
	return ((char *)ptr + sizeof(size) + sizeof(block_t));
}
