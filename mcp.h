/* Core calls */

#ifndef __MCP_H__
#define __MCP_H__

#define STDIN_FILENO        0
#define STDOUT_FILENO       1
#define STDERR_FILENO       2
#define FILE_TABLE_OFFSET   -3
#define CONSOLE             0

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

#define KFN_EXIT                0x00    /* Quick the current program and return to the command line */
#define KFN_WARMBOOT            0x01    /* Do a soft re-initialization */
#define KFN_INT_REGISTER        0x02    /* Set a handler for an exception / interrupt */
#define KFN_INT_ENABLE          0x03    /* Enable an interrupt */
#define KFN_INT_DISABLE         0x04    /* Disable an interrupt */
#define KFN_INT_ENABLE_ALL      0x05    /* Enable all interrupts */
#define KFN_INT_DISABLE_ALL     0x06    /* Disable all interrupts */
#define KFN_INT_CLEAR           0x07    /* Clear (acknowledge) an interrupt */
#define KFN_INT_PENDING         0x08    /* Return true if the interrupt is pending */
#define KFN_SYS_GET_INFO        0x09    /* Get information about the computer */

#define sys_exit(a) mcp_syscall(KFN_EXIT,a,0,0,0)
#define sys_warmboot() mcp_syscall(KFN_EXIT,0,0,0,0)
#define sys_int_register(a,b) mcp_syscall(KFN_INT_REGISTER,a,b,0,0)
#define sys_int_enable(a) mcp_syscall(KFN_INT_ENABLE,a,0,0,0)
#define sys_int_disable(a) mcp_syscall(KFN_INT_DISABLE,a,0,0,0)
#define sys_int_enable_all() mcp_syscall(KFN_INT_ENABLE_ALL,0,0,0,0)
#define sys_int_disable_all() mcp_syscall(KFN_INT_DISABLE_ALL,0,0,0,0)
#define sys_int_clear(a) mcp_syscall(KFN_INT_CLEAR,a,0,0,0)
#define sys_int_pending(a) mcp_syscall(KFN_INT_PENDING,a,0,0,0)
#define sys_get_information(a) mcp_syscall(KFN_SYS_GET_INFO,a,0,0,0)

/* Channel system calls */

#define KFN_CHAN_READ           0x10    /* Read bytes from an input channel */
#define KFN_CHAN_READ_B         0x11    /* Read a byte from an input channel */
#define KFN_CHAN_READ_LINE      0x12    /* Read a line from an input channel */
#define KFN_CHAN_WRITE          0x13    /* Write bytes to an output channel */
#define KFN_CHAN_WRITE_B        0x14    /* Write a byte to an output channel */
#define KFN_CHAN_FLUSH          0x15    /* Ensure that any pending write on a channel is committed */
#define KFN_CHAN_SEEK           0x16    /* Set the input/output cursor on a channel to a given position */
#define KFN_CHAN_STATUS         0x17    /* Get the status of a channel */
#define KFN_CHAN_IOCTRL         0x18    /* Send a command to a channel (channel dependent functionality) */
#define KFN_CHAN_REGISTER       0x19    /* Register a channel device driver */
#define KFN_CHAN_OPEN           0x1A    /* Open a channel device */
#define KFN_CHAN_CLOSE          0x1B    /* Close an open channel (not for files) */
#define KFN_CHAN_DEVICE         0x1C    /* Get the number of the device associated with the channel */


#define sys_chan_read(a,b,c) mcp_syscall(KFN_CHAN_READ,a,b,c,0)
#define sys_chan_read_b(a) mcp_syscall(KFN_CHAN_READ_B,a,0,0,0)
#define sys_chan_read_line(a,b,c) mcp_syscall(KFN_CHAN_READ_LINE,a,b,c,0)
#define sys_chan_write(a,b,c) mcp_syscall(KFN_CHAN_WRITE,a,b,c,0)
#define sys_chan_write_b(a,b) mcp_syscall(KFN_CHAN_WRITE_B,a,b,0,0)
#define sys_chan_flush(a) mcp_syscall(KFN_CHAN_FLUSH,a,0,0,0)
#define sys_chan_seek(a,b,c) mcp_syscall(KFN_CHAN_SEEK,a,b,c,0)
#define sys_chan_status(a) mcp_syscall(KFN_CHAN_STATUS,a,0,0,0)
#define sys_chan_ioctrl(a,b,c,d) mcp_syscall(KFN_CHAN_IOCTRL,a,b,c,d)
#define sys_chan_register(a) mcp_syscall(KFN_CHAN_REGISTER,a,0,0,0)
#define sys_chan_open(a,b) mcp_syscall(KFN_CHAN_OPEN,a,b,0,0)
#define sys_chan_close(a) mcp_syscall(KFN_CHAN_CLOSE,a,0,0,0)

/* Block device system calls */

#define KFN_BDEV_GETBLOCK       0x20    /* Read a block from a block device */
#define KFN_BDEV_PUTBLOCK       0x21    /* Write a block to a block device */
#define KFN_BDEV_FLUSH          0x22    /* Ensure that any pending write on a block device is committed */
#define KFN_BDEV_STATUS         0x23    /* Get the status of a block device */
#define KFN_BDEV_IOCTRL         0x24    /* Send a command to a block device (device dependent functionality) */
#define KFN_BDEV_REGISTER       0x25    /* Register a block device driver */
#define KFN_STAT                0x2F    /* Check for file existance and return file information */

#define sys_bdev_register(a) mcp_syscall(KFN_BDEV_REGISTER,a,0,0,0)
#define sys_bdev_read(a,b,c,d) mcp_syscall(KFN_BDEV_GETBLOCK,a,b,c,d)
#define sys_bdev_write(a,b,c,d) mcp_syscall(KFN_BDEV_PUTBLOCK,a,b,c,d)
#define sys_bdev_status(a) mcp_syscall(KFN_BDEV_STATUS,a,0,0,0)
#define sys_bdev_flush(a) mcp_syscall(KFN_BDEV_FLUSH,a,0,0,0)
#define sys_bdev_ioctrl(a,b,c,d) mcp_syscall(KFN_BDEV_IOCTRL,a,b,c,d)
#define sys_fsys_stat(a,b) mcp_syscall(KFN_STAT, a, b)

/* File/Directory system calls */

#define KFN_OPEN                0x30    /* Open a file as a channel */
#define KFN_CLOSE               0x31    /* Close a file channel */
#define KFN_OPENDIR             0x32    /* Open a directory for reading */
#define KFN_CLOSEDIR            0x33    /* Close an open directory */
#define KFN_READDIR             0x34    /* Read the next directory entry in an open directory */
#define KFN_FINDFIRST           0x35    /* Find the first entry in a directory that matches a pattern */
#define KFN_FINDNEXT            0x36    /* Find the next entry in a directory that matches a pattern */
#define KFN_DELETE              0x37    /* Delete a file */
#define KFN_RENAME              0x38    /* Rename a file */
#define KFN_MKDIR               0x39    /* Create a directory */
#define KFN_LOAD                0x3A    /* Load a file into memory */
#define KFN_GET_LABEL           0x3B    /* Read the label of a volume */
#define KFN_SET_LABEL           0x3C    /* Set the label of a volume */
#define KFN_SET_CWD             0x3D    /* Set the current working directory */
#define KFN_GET_CWD             0x3E    /* Get the current working directory */
#define KFN_LOAD_REGISTER       0x3F    /* Register a file type handler for executable binaries */

#define sys_fsys_open(a,b) mcp_syscall(KFN_OPEN,a,b,0,0)
#define sys_fsys_close(a) mcp_syscall(KFN_CLOSE,a,0,0,0)
#define sys_fsys_opendir(a) mcp_syscall(KFN_OPENDIR,a,0,0,0)
#define sys_fsys_closedir(a) mcp_syscall(KFN_CLOSEDIR,a,0,0,0)
#define sys_fsys_readdir(a,b) mcp_syscall(KFN_READDIR,a,b,0,0)
#define sys_fsys_findfirst(a,b,c) mcp_syscall(KFN_FINDFIRST,(long)a,(long)b,(long)c,0)
#define sys_fsys_findnext(a,b) mcp_syscall(KFN_FINDNEXT,a,b,0,0)
#define sys_fsys_delete(a) mcp_syscall(KFN_DELETE,a,0,0,0)
#define sys_fsys_rename(a,b) mcp_syscall(KFN_RENAME,a,b,0,0)
#define sys_fsys_mkdir(a) mcp_syscall(KFN_MKDIR,a,0,0,0)
#define sys_fsys_load(a,b,c) mcp_syscall(KFN_LOAD,a,b,c,0)
#define sys_fsys_setcwd(a) mcp_syscall(KFN_SET_CWD,a,0,0,0)
#define sys_fsys_getcwd(a,b) mcp_syscall(KFN_GET_CWD,a,b,0,0)
#define sys_fsys_get_label(a,b) mcp_syscall(KFN_GET_LABEL,a,b,0,0)
#define sys_fsys_set_label(a,b) mcp_syscall(KFN_SET_LABEL,a,b,0,0)
#define sys_fsys_register_loader(a,b) mcp_syscall(KFN_LOAD_REGISTER,a,b,0,0)

/* Process and memory calls */

#define KFN_RUN                 0x40    /* Load an execute a binary file */
#define KFN_MEM_GET_RAMTOP      0x41    /* Get the upper limit of the top of system RAM */
#define KFN_MEM_RESERVE         0x42    /* Reserve a block of memory at the top of system RAM */
//#define KFN_ELEVATE             0x43    /* Switch the user process to a full privilege */
#define KFN_VAR_SET             0x44    /* Set the value of a system variable */
#define KFN_VAR_GET             0x45    /* Get the value of a system variable */

#define sys_proc_run(a,b,c) mcp_syscall(KFN_RUN,a,b,c,0)
#define sys_mem_get_ramtop() mcp_syscall(KFN_MEM_GET_RAMTOP,0,0,0,0)
#define sys_mem_reserve(a) mcp_syscall(KFN_MEM_RESERVE,a,0,0,0)
#define sys_var_set(a,b) mcp_syscall(KFN_VAR_SET,a,b,0,0)
#define sys_var_get(a) mcp_syscall(KFN_VAR_GET,a,0,0,0)

/* Misc calls */

#define KFN_TIME_JIFFIES        0x50    /* Gets the current time code (increments since boot) */
#define KFN_TIME_SETRTC         0x51    /* Set the real time clock date-time */
#define KFN_TIME_GETRTC         0x52    /* Get the real time clock date-time */
#define KFN_KBD_SCANCODE        0x53    /* Get the next scan code from the keyboard */
#define KFN_KBD_LAYOUT          0x54    /* Set the translation tables for the keyboard */
#define KFN_ERR_MESSAGE         0x55    /* Return an error description, given an error number */

#define sys_rtc_get_jiffies() mcp_syscall(KFN_TIME_JIFFIES,0,0,0,0)
#define sys_rtc_set_time(a) mcp_syscall(KFN_TIME_SETRTC,a,0,0,0)
#define sys_rtc_get_time(a) mcp_syscall(KFN_TIME_GETRTC,(long)a,0,0,0)
#define sys_kbd_scancode() mcp_syscall(KFN_KBD_SCANCODE,0,0,0,0)
#define sys_err_message(a) mcp_syscall(KFN_ERR_MESSAGE,a,0,0,0)

/* Text Device Calls */

#define KFN_TXT_INIT_SCREEN    0x60    /* Reset a screen to its default mode */
#define KFN_TXT_GET_CAPS        0x61    /* Get the capabilities of a screen */
#define KFN_TXT_SET_MODE        0x62    /* Set the display mode of a screen */
#define KFN_TXT_SETSIZES       0x63    /* Adjusts the screen size based on the current graphics mode */
#define KFN_TXT_SET_RESOLUTION  0x64    /* Set the base display resolution for a screen */
#define KFN_TXT_SET_BORDER      0x65    /* Set the size of the border */
#define KFN_TXT_SET_BORDERCOLOR 0x66    /* Set the border color */
#define KFN_TXT_SET_FONT        0x67    /* Set the font for the screen's text mode (if applicable) */
#define KFN_TXT_SET_CURSOR      0x68    /* Set the text-mode cursor look */
#define KFN_TXT_SET_REGION      0x69    /* Sets the clipping/scrolling region for further text operations */
#define KFN_TXT_GET_REGION      0x6A    /* Gets the current clipping/scrolling region */
#define KFN_TXT_SET_COLOR       0x6B    /* Sets the foreground and background text colors */
#define KFN_TXT_GET_COLOR       0x6C    /* Gets the foreground and background text colors */
#define KFN_TXT_SET_XY          0x6D    /* Sets the cursor's position */
#define KFN_TXT_GET_XY          0x6E    /* Gets the cursor's position */
#define KFN_TXT_SCROLL          0x6F    /* Scroll the current region */
//#define KFN_TXT_FILL            0x70    /* Fill the current region */
#define KFN_TXT_SET_CURSOR_VIS  0x71    /* Set cursor visibility */
#define KFN_TXT_GET_SIZES       0x72    /* Get the screen size (visible text cells and total pixel resolution) */

#define sys_txt_init_screen(a) mcp_syscall(KFN_TXT_INIT_SCREEN,a,0,0,0)
#define sys_txt_set_resolution(a,b,c) mcp_syscall(KFN_TXT_SET_RESOLUTION,a,b,c,0)
#define sys_txt_get_capabilities(a) mcp_syscall(KFN_TXT_GET_CAPS,a,0,0,0)
#define sys_txt_set_mode(a,b) mcp_syscall(KFN_TXT_SET_MODE,a,b,0,0)
#define sys_text_setsizes(a) mcp_syscall(KFN_TXT_SETSIZES,a,0,0,0)
#define sys_txt_set_border(a,b,c) mcp_syscall(KFN_TXT_SET_BORDER,a,b,c,0)
#define sys_txt_set_border_color(a,b,c,d) mcp_syscall(KFN_TXT_SET_BORDERCOLOR,a,b,c,d)
#define sys_txt_set_font(a,b,c,d) mcp_syscall(KFN_TXT_SET_FONT,a,b,c,d)
#define sys_txt_set_cursor(a,b,c,d) mcp_syscall(KFN_TXT_SET_CURSOR,a,b,c,d)
#define sys_txt_set_region(a,b) mcp_syscall(KFN_TXT_SET_REGION,a,b,0,0)
#define sys_txt_get_region(a,b) mcp_syscall(KFN_TXT_GET_REGION,a,b,0,0)
#define sys_txt_set_color(a,b,c) mcp_syscall(KFN_TXT_SET_COLOR,a,b,c,0)
#define sys_txt_get_color(a,b,c) mcp_syscall(KFN_TXT_GET_COLOR,a,b,c,0)
#define sys_txt_set_xy(a,b,c) mcp_syscall(KFN_TXT_SET_XY,a,b,c,0)
#define sys_txt_get_xy(a,b) mcp_syscall(KFN_TXT_GET_XY,a,b,0,0)
#define sys_txt_scroll(a,b,c) mcp_syscall(KFN_TXT_SCROLL,a,b,c,0)
#define sys_txt_set_cursor_visible(a,b) mcp_syscall(KFN_TXT_SET_CURSOR_VIS,a,b,0,0)
#define sys_txt_get_sizes(a,b,c) mcp_syscall(KFN_TXT_GET_SIZES,a,b,c,0)


extern long mcp_syscall(long d0, long  d1, long d2, long d3, long d4);

int mcp_map_oflags(int oflag);

void mcp_map_errno(int result);


struct s_time {
    short year;
    short month;
    short day;
    short hour;
    short minute;
    short second;
    short is_pm;
    short is_24hours;
};

struct s_file_info {
    long size;
    unsigned short date;
    unsigned short time;
    unsigned char attributes;
    char name[256];
}; 

#endif