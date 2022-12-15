CC=/opt/m68k-toolchain/bin/m68k-elf-gcc
AR=/opt/m68k-toolchain/bin/m68k-elf-ar
BUILD=/opt/m68k-toolchain/m68k-elf/lib

ALL: liba2560k.a

liba2560k.a: newlib.o mcp_syscall.o
	$(AR) rcs liba2560k.a newlib.o mcp_syscall.o

newlib.o: newlib.c
	$(CC) -c newlib.c -o newlib.o

mcp_syscall.o: mcp_syscall.s
	$(CC) -c mcp_syscall.s -o mcp_syscall.o

clean:
	rm liba2560k.a newlib.o mcp_syscall.o

install:
	cp liba2560k.a $(BUILD)
	cp a2560k.ld $(BUILD)
