CC = /opt/m68k-toolchain/bin/m68k-elf-gcc
AR = /opt/m68k-toolchain/bin/m68k-elf-ar
BUILD = /opt/m68k-toolchain/m68k-elf/lib
OBJ = mcp_syscall.o \
	  mcp_mapping.o \
	  no_ops.o \
	  io_gettimeofday.o \
	  io_open.o \
	  io_close.o \
	  io_write.o \
	  io_read.o \
	  io_lseek.o \
	  io_sbrk.o \
	  io_exit.o

ALL: liba2560k.a mcp-crt0.o


liba2560k.a: $(OBJ)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) -c $< -o $@

%.o: %.s
	$(CC) -c $< -o $@

%.o: %.S
	$(CC) -c $< -o $@

clean:
	rm *.o *.a

install:
	cp liba2560k.a $(BUILD)
	cp a2560k.ld $(BUILD)
	cp mcp-crt0.o $(BUILD)
