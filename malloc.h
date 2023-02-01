#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>

#define ALIGNMENT(size) (size + (8 - (size % 8)))

/**
 * struct block_s - struct block
 * @start: start address
 * @used: Flag to indicate if the block is allocated
 */
typedef struct block_s
{
	void           *start;
	char           used;
} block_t;

/* ----- naive_malloc.c ----- */
void *naive_malloc(size_t size);

/* ----- malloc.c ----- */
void *_malloc(size_t size);

/* ----- free.c -----*/
void _free(void *ptr);

/* ----- calloc.c -----*/
void *_calloc(size_t nmemb, size_t size);

/* ----- realloc.c -----*/
void *_realloc(void *ptr, size_t size);

#endif /* _MALLOC_H_ */
