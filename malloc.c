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
	{
		new_page += (size_t)page;
	}
	tmp += new_page;
	if (new_page)
	{
		if (sbrk(tmp) == (void *)-1)
		{
			fprintf(stderr, "Line %d | %s: sbrk error\n", __LINE__, __func__);
			return (NULL);
		}
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
 * restructure_block - Restructures the block if it was freed
 * @ptr:       Pointer to the current block
 * @block:     block size to allocate
 * @prev_used: previous block size
 *
 * Return: Nothing
 */
void restructure_block(void **ptr, size_t block, size_t prev_used)
{
	size_t new_size = prev_used - block;
	void *prev_block = ((char *)(*ptr) - prev_used);
	void *next_block = ((char *)prev_block + block);

	/* Assign value to the previous block size */
	*(size_t *)(*ptr) = new_size;

	/* Assign 0 in the previous block size of prev_block*/
	*(size_t *)prev_block = 0;
	if (new_size <= METADATA)
	{
		/* Assign block size */
		*(size_t *)((char *)prev_block + 0x8) = prev_used;
	}
	else
	{
		/* Assign block size */
		*(size_t *)((char *)prev_block + 0x8) = block + 1;

		/* Assign size in remaining block */
		(*(size_t *)next_block) = 0;
		(*(size_t *)((char *)next_block + 0x8)) = new_size;
	}
	(*ptr) = ((char *)(*ptr) - prev_used);
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
	size_t i = 0, block_size = 0, prev_size = 0, used = 0;
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
	ptr = FIRST_CHUNK; /* Find final or empty(freed) adrress */
	for (i = 0; i < LEN; i++)
	{
		prev_size = *(size_t *)(ptr);
		block_size = (*(size_t *)((char *)ptr + 0x8)) - 1 + (prev_size ? 1 : 0);
		used = (block_size & 1);
		block_size = ((!prev_size && used) ? block_size + 1 : block_size);
		/* Validate if Block is freed */
		if (prev_size && !used && prev_size >= block)
		{
			restructure_block(&ptr, block, prev_size);
			break;
		}
		ptr = (char *)ptr + block_size;
	}
	if (!prev_size) /* New block if no previous free block is found */
	{
		ptr = new_block(ptr, block, size, page);
		/* Indicates with a bit that this block is being used */
		(*(size_t *)((char *)ptr + 0x8))++;
	}
	LEN++; /* block Length */
	return ((char *)ptr + METADATA);
}
