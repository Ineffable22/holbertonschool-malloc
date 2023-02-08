#include "malloc.h"

/**
 * _free - Function that frees a memory space
 * @ptr: Is a pointer to the memory space to be freed
 *
 * Return: Nothing
 */
void _free(void *ptr)
{
	void *next_ptr = NULL;
	size_t size = 0;

	if (ptr)
	{
		size = *(size_t *)((char *)ptr - (METADATA / 2)) - 1;
		next_ptr = (char *)ptr + size;
		*(size_t *)((char *)next_ptr - METADATA) = size;
		(*(size_t *)((char *)next_ptr - (METADATA / 2)))--;
	}
}
