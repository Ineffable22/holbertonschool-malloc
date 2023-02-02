#include "malloc.h"

/**
 * str_test - Test the memory allocation with pointer to char type
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int str_test(void)
{
	char *str;
	int i;

	printf("==========String allocation test==========\n");
	printf("Starting break is %p\n", sbrk(0));
	for (i = 0; i < 10; i++)
	{
		void *chunk;
		str = naive_malloc(10);
		if (str == NULL)
			return (EXIT_FAILURE);
		strcpy(str, "Holberton");
		str[9] = '\0';
		printf("%p: %s, ", (void *)str, str);
		chunk = (void *)(str - sizeof(size_t));
		printf("chunk addr: %p, ", (void *)chunk);
		printf("size: %lu, ", *((size_t *)chunk));
		printf("break: %p\n", sbrk(0));
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

		num = naive_malloc(10);
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
