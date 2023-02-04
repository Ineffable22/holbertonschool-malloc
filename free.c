#include "malloc.h"

/**
 * _free - Function that frees a memory space
 * @ptr: Is a pointer to the memory space to be freed
 *
 * Return: Nothing
 */
void _free(void *ptr)
{
	void *size = 0;

	if (ptr)
	{
		size = (char *)ptr - (METADATA / 2);
		(*(size_t *)size)--;
		*(size_t *)((char *)size - (METADATA / 2)) = (*(size_t *)size);
	}
}
