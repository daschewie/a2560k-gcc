#include <sys/fcntl.h>
#include "mcp.h"

int lseek(int file, int ptr, int dir) {
  if (file > STDERR_FILENO) {
    return sys_chan_seek(file - FILE_TABLE_OFFSET, ptr, dir - 1);
  } else {
    return -1;
  }
}