#include "malloc.h"

/**
 * checker - Check if pointers are equal
 * @chunk1: Pointer to chunk of my own malloc
 * @chunk2: Pointer to chunk of real malloc
 * @str1: Pointer to metadata of my own malloc
 * @str2: Pointer to metadata of real malloc
 *
 * Return: 1 if successful, 0 otherwise
 */
int checker(void *chunk1, void *chunk2, char *str1, char *str2)
{
	unsigned char *ptr1 = (unsigned char *)str1;
	unsigned char *ptr2 = (unsigned char *)str2;
	unsigned int i;

	if (*((size_t *)chunk1) != *((size_t *)chunk2))
		return (1);

	for (i = 0; i < METADATA; i++)
	{
		if (*(ptr1 + i) != *(ptr2 + i))
			return (1);
	}
	return (0);
}

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
	char *str1, *str2, *text = "Holberton";
	int i;
	void *chunk1, *chunk2;

	printf("==========String allocation test==========\n");
	printf("Starting break is %p\n", sbrk(0));
	for (i = 0; i < 100; i++)
	{
		str1 = _malloc(i);
		if (str1 == NULL)
			return (EXIT_FAILURE);
		strcpy(str1, text);
		chunk1 = (void *)(str1 - sizeof(size_t));
		str2 = malloc(i);
		if (str2 == NULL)
			return (EXIT_FAILURE);
		strcpy(str2, text);
		chunk2 = (void *)(str2 - sizeof(size_t));
		if (checker(chunk1, chunk2, str1 - 0x10, str2 - 0x10))
		{
			printf("i => %d\n", i);
			printf("size1: %lu\n", *((size_t *)chunk1));
			printf("size2: %lu\n", *((size_t *)chunk2));
			pmem(str1 - 0x10, 0x10);
			pmem(str2 - 0x10, 0x10);
			putchar('\n');
		}
		_free(str1);
		_free(str2);
	}
	printf("Final break is %p\n\n", sbrk(0));
	return (EXIT_SUCCESS);
}
/*
 * Range 16-24	My result => 49		malloc result => 33
 * Range 32-40	My result => 65		malloc result => 49
 * Range 40-56	My result => 81		malloc result => 65
 * Range 64-72	My result => 97		malloc result => 81
 * Range 80-88	My result => 113	malloc result => 97
 * pattern match =>
 * if (size % 0x10 <= 8 && size > 0xF)
 *         block = (size + ((8 - (size % 0x10)) + 8));
 */

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
	return (EXIT_SUCCESS);
}
