#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "mcp.h"

#undef errno
extern int errno;
char *__env[1] = { 0 };
char **environ = __env;

#define FA_READ             0x01
#define FA_WRITE            0x02
#define FA_OPEN_EXISTING    0x00
#define FA_CREATE_NEW       0x04
#define FA_CREATE_ALWAYS    0x08
#define FA_OPEN_ALWAYS      0x10
#define FA_OPEN_APPEND      0x30

#define FSYS_ERR_DISK_ERR               -18 /* (1) A hard error occurred in the low level disk I/O layer */
#define FSYS_ERR_INT_ERR                -19 /* (2) Assertion failed */
#define FSYS_ERR_NOT_READY              -20 /* (3) The physical drive cannot work */
#define FSYS_ERR_NO_FILE                -21 /* (4) Could not find the file */
#define FSYS_ERR_NO_PATH                -22 /* (5) Could not find the path */
#define FSYS_ERR_INVALID_NAME           -23 /* (6) The path name format is invalid */
#define FSYS_ERR_DENIED                 -24 /* (7) Access denied due to prohibited access or directory full */
#define FSYS_ERR_EXIST                  -25 /* (8) Access denied due to prohibited access */
#define FSYS_ERR_INVALID_OBJECT         -26 /* (9) The file/directory object is invalid */
#define FSYS_ERR_WRITE_PROTECTED        -27 /* (10) The physical drive is write protected */
#define FSYS_ERR_INVALID_DRIVE          -28 /* (11) The logical drive number is invalid */
#define FSYS_ERR_NOT_ENABLED            -29 /* (12) The volume has no work area */
#define FSYS_ERR_NO_FILESYSTEM          -30 /* (13) There is no valid FAT volume */
#define FSYS_ERR_MKFS_ABORTED           -31 /* (14) The f_mkfs() aborted due to any problem */
#define FSYS_ERR_TIMEOUT                -32 /* (15) Could not get a grant to access the volume within defined period */
#define FSYS_ERR_LOCKED                 -33 /* (16) The operation is rejected according to the file sharing policy */
#define FSYS_ERR_NOT_ENOUGH_CORE        -34 /* (17) LFN working buffer could not be allocated */
#define FSYS_ERR_TOO_MANY_OPEN_FILES    -35 /* (18) Number of open files > FF_FS_LOCK */
#define FSYS_ERR_INVALID_PARAMETER      -36 /* (19) Given parameter is invalid */

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
static int _map_oflags(int oflag) {
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

static void map_errno(int result) {
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

void _exit(int status) {
    sys_exit(status);
}

int open(const char *name, int flags, ...) {
    int mode = _map_oflags(flags);
    if (mode < 0) {
        return -1;
    }

    int result = sys_fsys_open((long)name, mode);
    if (result < 0) {
        map_errno(result);
        return -1;
    } else {
        return result + FILE_TABLE_OFFSET;
    }
}

int close(int file) {
  if (file > STDERR_FILENO) {
      sys_fsys_close(file - FILE_TABLE_OFFSET);
  }
  return 0;
}

int execve(char *name, char **argv, char **env) {
  errno = ENOMEM;
  return -1;
}

int fork(void) {
  errno = EAGAIN;
  return -1;
}

int fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}

int getpid(void) {
  return 1;
}

int isatty(int file) {
  return 1;
}

int kill(int pid, int sig) {
  errno = EINVAL;
  return -1;
}

int link(char *old, char *new) {
  errno = EMLINK;
  return -1;
}

int lseek(int file, int ptr, int dir) {
  if (file > STDERR_FILENO) {
    return sys_chan_seek(file - FILE_TABLE_OFFSET, ptr, dir - 1);
  } else {
    return -1;
  }
}

int read(int file, char *ptr, int len) {
  if (file == STDIN_FILENO) {
      return sys_chan_read(CONSOLE, (long)ptr, len);
  } else if (file > STDERR_FILENO) {
      return sys_chan_read(file - FILE_TABLE_OFFSET, (long)ptr, len);
  } else {
      return -1;
  }
}

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

int stat(const char *file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}

clock_t times(struct tms *buf) {
  buf->tms_utime = 0;
  buf->tms_stime = 0;
  buf->tms_cutime = 0;
  buf->tms_cstime = 0;
  return -1;
}

int unlink(char *name) {
  errno = ENOENT;
  return -1; 
}

int wait(int *status) {
  errno = ECHILD;
  return -1;
}

int write(int file, char *ptr, int len) {
  if (file == STDOUT_FILENO || file == STDERR_FILENO) {
      return sys_chan_write(CONSOLE, (long)ptr, len);
  } else if (file == STDIN_FILENO) {
      return -1;
  } else {
      return sys_chan_write(file - FILE_TABLE_OFFSET, (long)ptr, len);
  }
}