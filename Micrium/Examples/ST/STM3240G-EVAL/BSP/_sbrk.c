#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

char *heap_end = 0;
caddr_t _sbrk(int incr) {
	extern char _end; /* Defined by the linker */
	extern char __cs3_heap_end; /* Defined by the linker */
	char *prev_heap_end;
	if (heap_end == 0) {
		heap_end = &_end;
	}  
	prev_heap_end = heap_end;
	if (heap_end + incr > &__cs3_heap_end) {
		/* Heap and stack collision */
		return (caddr_t)0;
	}
	heap_end += incr;
	return (caddr_t) prev_heap_end;
}
