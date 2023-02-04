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
	(*page) = sysconf(_SC_PAGESIZE);
	if ((*page) == -1)
	{
		fprintf(stderr, "first_time: sysconf error");
		return (NULL);
	}
	FIRST_CHUNK = sbrk((*page));
	if (FIRST_CHUNK == (void *)-1)
	{
		perror("first_time: sbrk error");
		return (NULL);
	}
	return (FIRST_CHUNK);
}

/**
 * new_block - Allocate new pages on the heap
 * @ptr:   Pointer to allocated page
 * @block: size of block to allocate
 * @page:  Value of page
 *
 * Return: Pointer to allocated page
 */
void *new_block(void *ptr, size_t block, ssize_t page)
{
	void *next_block;
	size_t tmp = 0;

	/* Page value for the first time, otherwise the rest of the page */
	tmp = LEN ? *(size_t *)ptr : (size_t)page;

	next_block = ((char *)ptr + block);
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
	/* Assigns the rest of the page value in the next block */
	*(size_t *)next_block = tmp - block;

	/* Assigns the current block size */
	*(size_t *)((char *)ptr + 0x8) = block;
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
	size_t block = ALIGNMENT(size) + 0x10;
	size_t i, block_size, flag = 0;
	ssize_t page = 0;

	/* Find the starting address */
	if (!FIRST_CHUNK)
	{
		FIRST_CHUNK = first_time(&page);
		if (!FIRST_CHUNK)
			return (NULL);
	}

	/* Find final or empty(freed) adrress */
	ptr = FIRST_CHUNK;
	for (i = 0; i < LEN; i++)
	{
		block_size = (*(size_t *)((char *)ptr + 0x8)) - 1;
		/* Validate if Block is freed */
		if (!(block_size | 0) && block_size <= block)
		{
			flag = 1;
			break;
		}
		ptr = (char *)ptr + block_size;
	}

	/* New block if no previous free block is found */
	if (!flag)
		ptr = new_block(ptr, block, page);

	/* Assign 0 to the previous block size */
	*(size_t *)ptr = 0;
	/* Indicates with a bit that this block is being used */
	(*(size_t *)((char *)ptr + 0x8))++;
	/* block Length */
	LEN++;
	return ((char *)ptr + 0x10);
}
