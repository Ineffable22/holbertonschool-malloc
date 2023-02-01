#include "malloc.h"

/**
 * _free - Function that frees a memory space
 * @ptr: Is a pointer to the memory space to be freed
 *
 * Return: Nothing
 */
void _free(void *ptr)
{
	if (ptr)
		((block_t *)((char *)ptr - sizeof(size_t) - sizeof(block_t)))->used = 0;
}
