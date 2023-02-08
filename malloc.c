#include "malloc.h"

void  *FIRST_CHUNK;
size_t LEN;
size_t AVAILABLE;

/**
 * first_time - Create the page and initialize memory and point
 * to the start address
 * @max_page: Variable to save the page
 * @block:    Size of block to allocate
 *
 * Return: Pointer to the start address of the page
 */
void *first_time(ssize_t *max_page, size_t block)
{
	ssize_t page = 0;

	page = sysconf(_SC_PAGESIZE);
	if (page == -1)
	{
		fprintf(stderr, "Line %d | %s: sysconf error\n", __LINE__, __func__);
		return (NULL);
	}
	for ((*max_page) = page; (size_t)(*max_page) < block; (*max_page) += page)
	{}
	FIRST_CHUNK = sbrk((*max_page));
	if (FIRST_CHUNK == (void *)-1)
	{
		fprintf(stderr, "Line %d | %s: sbrk error\n", __LINE__, __func__);
		return (NULL);
	}
	return (FIRST_CHUNK);
}

/**
 * new_block - Allocate new pages on the heap
 * @ptr:   Pointer to allocated page
 * @block: size of block to allocate
 * @size:  Is the size needed to be allocated for the user
 * @page:  Value of page
 *
 * Return: Pointer to allocated page
 */
void *new_block(void *ptr, size_t block, size_t size, ssize_t page)
{
	size_t tmp = 0;
	size_t new_page = 0;

	/* Page value for the first time, otherwise the rest of the page */
	tmp = LEN ? AVAILABLE : (size_t)page;
	page = sysconf(_SC_PAGESIZE);
	if (page == -1)
	{
		fprintf(stderr, "Line %d | %s: sysconf error\n", __LINE__, __func__);
		return (NULL);
	}
	while (tmp + new_page < block)
		new_page += (size_t)page;
	tmp += new_page;
	if (sbrk(tmp) == (void *)-1)
	{
		fprintf(stderr, "Line %d | %s: sbrk error\n", __LINE__, __func__);
		return (NULL);
	}
	/* Assigns the rest of the page value in the next block */
	AVAILABLE = tmp - block;

	/* Pattern found, more information in "test/compare.c" */
	(void) size;
	/* if (size % 0x10 <= 8 && size > 0xF) */
	/*	block = (size + ((8 - (size % 0x10)) + 8)); */

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
	void *ptr = NULL;
	size_t block = ALIGNMENT(size) + METADATA;
	size_t i = 0, block_size = 0, flag = 0;
	ssize_t page = 0;

	if ((ssize_t)size < 0)
	{
		fprintf(stderr, "Line %d | %s: ", __LINE__, __func__);
		fprintf(stderr, "Can not allocate negative memory\n");
		return (NULL);
	}
	if (!FIRST_CHUNK) /* Find the starting address */
	{
		FIRST_CHUNK = first_time(&page, block);
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
		ptr = new_block(ptr, block, size, page);
	/* Assign 0 to the previous block size */
	*(size_t *)ptr = 0;
	/* Indicates with a bit that this block is being used */
	(*(size_t *)((char *)ptr + 0x8))++;
	/* block Length */
	LEN++;
	return ((char *)ptr + METADATA);
}
