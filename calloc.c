#include "malloc.h"

/**
 * _calloc - Allocates space in the heap
 * @nmemb: Is the number of elements in the array
 * @size:  Is the size of each element
 *
 * Return: A  pointer to the allocated memory that is suitably aligned
 * for any kind of variable
 */
void *_calloc(size_t nmemb, size_t size)
{
	void *p = _malloc(nmemb * size);

	return (!p ? NULL : memset(p, 0, nmemb * size));
}
