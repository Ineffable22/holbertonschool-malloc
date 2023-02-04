#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * pmem - print mem
 * @p: memory address to start printing from
 * @bytes: number of bytes to print
 *
 * Return: nothing
 */
void pmem(void *p, unsigned int bytes)
{
	unsigned char *ptr;
	unsigned int i;

	ptr = (unsigned char *)p;
	for (i = 0; i < bytes; i++)
	{
		if (i != 0)
		{
			printf(" ");
		}
		printf("%02x", *(ptr + i));
	}
	printf("\n");
}

/**
 * main - using the 0x10 bytes to jump to next malloc'ed chunks
 *
 * Return: EXIT_FAILURE if something failed. Otherwise EXIT_SUCCESS
 */
int main(void)
{
	void *p;
	int i;
	void *heap_start;
	size_t size_of_the_block;

	heap_start = sbrk(0);
	write(1, "START\n", 6);
	for (i = 0; i < 10; i++)
	{
		p = malloc(1024 * (i + 1));
		*((int *)p) = i;
		printf("%p: [%i]\n", p, i);
	}
	p = heap_start;
	for (i = 0; i < 10; i++)
	{
		pmem(p, 0x10);
		size_of_the_block = *((size_t *)((char *)p + 8)) - 1;
		printf("%p: [%i] - size = %lu\n",
		       (void *)((char *)p + 0x10),
		       *((int *)((char *)p + 0x10)),
		       size_of_the_block);
		p = (void *)((char *)p + size_of_the_block);
	}
	write(1, "END\n", 4);
	return (EXIT_SUCCESS);
}

/**
 * RTFSC
 * At this stage, we probably want to check the source code of malloc to confirm what we just found (malloc.c from the glibc).
 *
 * 1055
 * 1056       malloc_chunk details:
 * 1057    
 * 1058        (The following includes lightly edited explanations by Colin Plumb.)
 * 1059    
 * 1060        Chunks of memory are maintained using a `boundary tag' method as
 * 1061        described in e.g., Knuth or Standish.  (See the paper by Paul
 * 1062        Wilson ftp://ftp.cs.utexas.edu/pub/garbage/allocsrv.ps for a
 * 1063        survey of such techniques.)  Sizes of free chunks are stored both
 * 1064        in the front of each chunk and at the end.  This makes
 * 1065        consolidating fragmented chunks into bigger chunks very fast.  The
 * 1066        size fields also hold bits representing whether chunks are free or
 * 1067        in use.
 * 1068    
 * 1069        An allocated chunk looks like this:
 * 1070    
 * 1071    
 * 1072        chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * 1073                |             Size of previous chunk, if unallocated (P clear)  |
 * 1074                +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * 1075                |             Size of chunk, in bytes                     |A|M|P|
 * 1076          mem-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * 1077                |             User data starts here...                          .
 * 1078                .                                                               .
 * 1079                .             (malloc_usable_size() bytes)                      .
 * 1080                .                                                               |
 * 1081    nextchunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * 1082                |             (size of chunk, but used for application data)    |
 * 1083                +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * 1084                |             Size of next chunk, in bytes                |A|0|1|
 * 1085                +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * 1086    
 * 1087        Where "chunk" is the front of the chunk for the purpose of most of
 * 1088        the malloc code, but "mem" is the pointer that is returned to the
 * 1089        user.  "Nextchunk" is the beginning of the next contiguous chunk.
 */
