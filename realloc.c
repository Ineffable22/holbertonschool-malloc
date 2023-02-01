#include "malloc.h"

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr:      Is a pointer to the memory space to resize
 * @new_size: Is the new size needed to be allocated for the user
 *
 * Return: pointer to the newly allocated memory block
 */
void *_realloc(void *ptr, size_t new_size)
{
	char *new_ptr = NULL;
	size_t size = 0;

	if (ptr == NULL)
		return (_malloc(new_size));
	size = *(size_t *)((char *)ptr + sizeof(block_t));
	if (new_size == 0)
	{
		_free(ptr);
		return (NULL);
	}

	if (size == ALIGNMENT(new_size) + sizeof(block_t) + sizeof(size_t))
		return (ptr);

	new_ptr = _malloc(new_size);
	if (!new_ptr)
		return (NULL);

	memcpy(new_ptr, ptr, MIN(size, new_size));
	_free(ptr);
	return (new_ptr);
}
