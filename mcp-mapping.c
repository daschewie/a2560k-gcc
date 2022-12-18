#include <sys/errno.h>
#include <sys/fcntl.h>
#include "mcp.h"

/*
File mode mappings.
https://man7.org/linux/man-pages/man3/fopen.3.html
http://elm-chan.org/fsw/ff/doc/open.html
│ fopen()     │ open() flags                  │ FatFS
├─────────────┼───────────────────────────────┼───────────────────────────────────────┤
│     r       │ O_RDONLY                      │ FA_READ                               │
├─────────────┼───────────────────────────────┼───────────────────────────────────────┤
│     w       │ O_WRONLY | O_CREAT | O_TRUNC  │ FA_CREATE_ALWAYS | FA_WRITE           │
├─────────────┼───────────────────────────────┼───────────────────────────────────────┤
│     a       │ O_WRONLY | O_CREAT | O_APPEND │ FA_OPEN_APPEND | FA_WRITE             │
├─────────────┼───────────────────────────────┼───────────────────────────────────────┤
│     r+      │ O_RDWR                        │ FA_READ | FA_WRITE                    │
├─────────────┼───────────────────────────────┼───────────────────────────────────────┤
│     w+      │ O_RDWR | O_CREAT | O_TRUNC    │ FA_CREATE_ALWAYS | FA_WRITE | FA_READ │
├─────────────┼───────────────────────────────┼───────────────────────────────────────┤
│     a+      │ O_RDWR | O_CREAT | O_APPEND   | FA_OPEN_APPEND | FA_WRITE | FA_READ   │
├─────────────┼───────────────────────────────┼───────────────────────────────────────┤
*/
int mcp_map_oflags(int oflag) {
    int result = 0;

    switch (oflag) {
        // r
        case O_RDONLY:
            result = FA_READ;
            break;
        // w
        case (O_WRONLY | O_CREAT | O_TRUNC):
            result = FA_CREATE_ALWAYS | FA_WRITE;
            break;
        // a
        case (O_WRONLY | O_CREAT | O_APPEND ):
            result = FA_OPEN_APPEND | FA_WRITE;
            break;
        // r+
        case (O_RDWR ):
            result = FA_READ | FA_WRITE;
            break;
        // w+
        case (O_RDWR | O_CREAT | O_TRUNC):
            result = FA_CREATE_ALWAYS | FA_WRITE | FA_READ;
            break;
        // a+
        case (O_RDWR | O_CREAT | O_APPEND):
            result = FA_OPEN_APPEND | FA_WRITE | FA_READ;
            break;
        default:
            errno = EINVAL;
            result = -1;
            break;
    }

    return result;
}

void mcp_map_errno(int result) {
    switch (result) {
        case FSYS_ERR_DISK_ERR:
        case FSYS_ERR_INT_ERR:
        case FSYS_ERR_NOT_READY:
        case FSYS_ERR_NOT_ENABLED:
        case FSYS_ERR_NO_FILESYSTEM:
            errno = ENODEV;
            break;
        case FSYS_ERR_NO_FILE:
        case FSYS_ERR_NO_PATH:
            errno = ENOENT;
            break;
        case FSYS_ERR_INVALID_NAME:
        case FSYS_ERR_INVALID_OBJECT:
        case FSYS_ERR_INVALID_DRIVE:
        case FSYS_ERR_INVALID_PARAMETER:
            errno = EINVAL;
            break;
        case FSYS_ERR_DENIED:
        case FSYS_ERR_WRITE_PROTECTED:
            errno = EACCES;
            break;
        case FSYS_ERR_EXIST:
            errno = EEXIST;
            break;
        case FSYS_ERR_TOO_MANY_OPEN_FILES:
            errno = ENFILE;
            break;
        case FSYS_ERR_LOCKED:
            errno = ETXTBSY;
            break;
        case FSYS_ERR_MKFS_ABORTED:
        case FSYS_ERR_TIMEOUT:
        case FSYS_ERR_NOT_ENOUGH_CORE:
            errno = EFAULT;
            break;
        default:
            errno = EIO;
            break;
    }
}