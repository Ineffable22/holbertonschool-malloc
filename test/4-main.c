#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void *naive_malloc_page(size_t size)
{
	static void *first_chunk;
	static size_t len;
	void *ptr, *next_block = NULL;
	size_t block = size + sizeof(size), i, block_size, tmp;
	ssize_t page;

	if (len == 0)
	{
		page = sysconf(_SC_PAGESIZE);
		if (page == -1)
		{
			fprintf(stderr, "naive_malloc_page: sysconf error");
			return (NULL);
		}
		first_chunk = sbrk(page);
		if (first_chunk == (void *)-1)
		{
			perror("naive_malloc_page: sbrk error");
			return (NULL);
		}
	}
	for (i = 0, ptr = first_chunk; i < len; i++)
	{
		block_size = *(size_t *)ptr;
		ptr = (char *)ptr + block_size;
	}
	tmp = len ? *(size_t *)ptr : (size_t)page;
	next_block = ((char *)ptr) + block;
	*(size_t *)next_block = tmp - block;
	*(size_t *)ptr = block;
	len++;
	return ((char *)ptr + sizeof(size));
}

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	char *str;
	int i;

	printf("Starting break is %p\n", sbrk(0));

	for (i = 0; i < 10; i++)
	{
		void *chunk;

		str = naive_malloc_page(10);
		strcpy(str, "Holberton");
		str[9] = '\0';
		printf("%p: %s, ", (void *)str, str);
		chunk = (void *)(str - sizeof(size_t));
		printf("chunk addr: %p, ", (void *)chunk);
		printf("size: %lu, ", *((size_t *)chunk));
		printf("break: %p\n", sbrk(0));
	}

	printf("Final break is %p\n", sbrk(0));
	return (EXIT_SUCCESS);
}
