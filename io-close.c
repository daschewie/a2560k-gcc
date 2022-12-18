#include <sys/fcntl.h>
#include "mcp.h"

int close(int file) {
  if (file > STDERR_FILENO) {
      sys_fsys_close(file - FILE_TABLE_OFFSET);
  }
  return 0;
}