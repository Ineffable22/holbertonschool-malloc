#include "malloc.h"

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr:  Is a pointer to the memory space to resize
 * @size: Is the new size needed to be allocated for the user
 *
 * Return: pointer to the newly allocated memory block
 */
void *_realloc(void *ptr, size_t size)
{
	char *new_ptr = NULL;
	size_t old_size = 0;

	if (ptr == NULL || len == 0)
		return (_malloc(size));
	old_size = *(size_t *)((char *)ptr + sizeof(block_t));
	if (size == 0)
	{
		_free(ptr);
		return (NULL);
	}

	if (old_size == ALIGNMENT(size) + sizeof(block_t) + sizeof(size_t))
		return (ptr);

	new_ptr = _malloc(size);
	if (!new_ptr)
		return (NULL);

	memcpy(new_ptr, ptr, MIN(old_size, size));
	_free(ptr);
	return (new_ptr);
}
