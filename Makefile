CC = /opt/m68k-toolchain/bin/m68k-elf-gcc
AR = /opt/m68k-toolchain/bin/m68k-elf-ar
BUILD = /opt/m68k-toolchain/m68k-elf/lib
OBJ = mcp-syscall.o \
	  mcp-mapping.o \
	  no-ops.o \
	  io-gettimeofday.o \
	  io-open.o \
	  io-close.o \
	  io-write.o \
	  io-read.o \
	  io-lseek.o \
	  io-sbrk.o \
	  io-exit.o

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
