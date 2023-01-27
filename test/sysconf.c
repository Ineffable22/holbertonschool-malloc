#include <unistd.h>
#include <stdio.h>

int main()
{
	printf("Tamaño de las páginas de memoria: %ld bytes\n", sysconf(_SC_PAGESIZE));
	printf("Número de ticks por segundo en el sistema: %ld\n", sysconf(_SC_CLK_TCK));
	printf("Número de procesadores: %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
	printf("Número total de páginas de memoria física en el sistema: %ld\n", sysconf(_SC_PHYS_PAGES));
	return 0;
}
