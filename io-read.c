#include <sys/fcntl.h>
#include "mcp.h"

int read(int file, char *ptr, int len) {
  if (file == STDIN_FILENO) {
      return sys_chan_read(CONSOLE, (long)ptr, len);
  } else if (file > STDERR_FILENO) {
      return sys_chan_read(file - FILE_TABLE_OFFSET, (long)ptr, len);
  } else {
      return -1;
  }
}