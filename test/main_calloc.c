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
 * str_test - Test the memory allocation with pointer to char type
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int str_test(void)
{
	char *str, *text = "Holberton";
	int i;
	size_t size_of_the_chunk;
	size_t size_of_the_previous_chunk;
	void *chunks[10], *chunk;
	char prev_used;
	void *p;

	printf("==========String allocation test==========\n");
	printf("Starting break is %p\n", sbrk(0));
	for (i = 0; i < 10; i++)
	{
		str = _calloc(10, 2);
		chunks[i] = (void *)((char *)str - 0x10);
		if (str == NULL)
			return (EXIT_FAILURE);
		strcpy(str, text);
		printf("%p: %s, ", (void *)str, str);
		chunk = (void *)(str - sizeof(size_t));
		printf("chunk addr: %p, ", (void *)chunk);
		printf("size: %lu, ", *((size_t *)chunk));
		printf("break: %p\n", sbrk(0));
		pmem(str - 0x10, 0x10);
	}

	for (i = 0; i < 10; i++)
	{
		p = chunks[i];
		printf("chunks[%d]: ", i);
		pmem(p, 0x10);
		size_of_the_chunk = *((size_t *)((char *)p + 0x8));
		prev_used = size_of_the_chunk & 1;
		size_of_the_chunk -= prev_used;
		size_of_the_previous_chunk = *((size_t *)((char *)p));
		printf("chunks[%d]: %p, size = %li, prev (%s) = %li\n",
		       i, p, size_of_the_chunk,
		       (prev_used ? "allocated" : "unallocated"), size_of_the_previous_chunk);
	}
	printf("Final break is %p\n\n", sbrk(0));
	return (EXIT_SUCCESS);
}

/**
 * int_test - Test the memory allocation with pointer to integer type
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int int_test(void)
{
	int *num;
	int i, j;

	printf("==========Integer allocation test==========\n");
	printf("Starting break is %p\n", sbrk(0));
	for (i = 0; i < 10; i++)
	{
		void *chunk;

		num = _calloc(10, 2);
		if (num == NULL)
			return (EXIT_FAILURE);
		for (j = 0; j < 10; j++)
			num[j] = j;
		printf("%p: ", (void *)num);
		for (j = 0; j < 10; j++)
			printf("%d, ", num[j]);
		chunk = (void *)(num - sizeof(size_t));
		printf("chunk addr: %p, ", (void *)chunk);
		printf("size: %lu, ", *((size_t *)chunk));
		printf("break: %p\n", sbrk(0));
	}
	printf("Final break is %p\n\n", sbrk(0));
	return (EXIT_SUCCESS);
}

/**
 * main - main program to test the memory allocation
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	if (str_test() == EXIT_FAILURE)
	{
		fprintf(stderr, "str_test: Error\n");
		return (EXIT_FAILURE);
	}
	if (int_test() == EXIT_FAILURE)
	{
		fprintf(stderr, "int_test: Error\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
