#include <sys/fcntl.h>
#include "mcp.h"

int write(int file, char *ptr, int len) {
  if (file == STDOUT_FILENO || file == STDERR_FILENO) {
      return sys_chan_write(CONSOLE, (long)ptr, len);
  } else if (file == STDIN_FILENO) {
      return -1;
  } else {
      return sys_chan_write(file - FILE_TABLE_OFFSET, (long)ptr, len);
  }
}