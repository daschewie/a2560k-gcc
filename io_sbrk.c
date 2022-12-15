#include <sys/types.h>

caddr_t sbrk(int incr) {
  static unsigned char *heap = NULL;
  unsigned char *prev_heap;
  extern int _end;

  if (heap == NULL) {
    heap = (unsigned char *)&_end;
  }
  prev_heap = heap;

  heap += incr;

  return prev_heap;
}
