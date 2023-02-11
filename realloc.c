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

	if (!ptr)
		return (_malloc(size));
	if (size == 0)
	{
		_free(ptr);
		return (NULL);
	}
	old_size = *(size_t *)((char *)ptr - sizeof(size_t));

	if (old_size - 1 == ALIGNMENT(size) + METADATA)
		return (ptr);

	new_ptr = _malloc(size);
	if (!new_ptr)
		return (NULL);

	memcpy(new_ptr, ptr, _MIN(old_size, size));
	_free(ptr);
	return (new_ptr);
}
