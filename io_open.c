#include <sys/fcntl.h>
#include "mcp.h"

int open(const char *name, int flags, ...) {
    int mode = mcp_map_oflags(flags);
    if (mode < 0) {
        return -1;
    }

    int result = sys_fsys_open((long)name, mode);
    if (result < 0) {
        mcp_map_errno(result);
        return -1;
    } else {
        return result + FILE_TABLE_OFFSET;
    }
}