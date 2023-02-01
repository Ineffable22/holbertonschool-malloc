#include "malloc.h"

int main(void)
{
	char *str, *tmp_p, *to_free;
	int i;
	size_t block_size;
	void *ptr;
	block_t *block, *tmp_block;

	printf("==========Free deallocation test==========\n");
	printf("Starting break is %p\n", sbrk(0));
	for (i = 0; i < 10; i++)
	{
		str = _malloc(10);
		if (str == NULL)
			return (EXIT_FAILURE);
		strcpy(str, "Holberton");
		str[9] = '\0';
		if (i == 5)
			to_free = str;
		block = (block_t *)(str - sizeof(size_t) - sizeof(block_t));
	}
	_free(to_free);
	ptr = block->start;
	for (i = 0; i < 10; i++)
	{
		tmp_block = (block_t *)((char *)ptr);
		tmp_p = (char *)((char *)ptr + sizeof(size_t) + sizeof(block_t));
		printf("str: %s | used => %d\n", tmp_p, tmp_block->used);
		block_size = *(size_t *)((char *)ptr + sizeof(block_t));
		ptr = (char *)ptr + block_size;
	}
	printf("Final break is %p\n\n", sbrk(0));
	return (EXIT_SUCCESS);
}
