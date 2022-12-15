# a2560k-gcc
Newlib syscalls and linker script for Foenix A2560K computer

## Setup
- Compile and install elf2pgz from https://github.com/csoren/elf2pgz
- Compile and install m68k-elf GCC from https://github.com/kentosama/m68k-elf-gcc
- Update CC and BUILD variables in Makefile to use gcc install location
- Run the following commands to install:
```
make
make install
```

## Usage
- Sample Makefile for building hello.c
```
CC=/opt/m68k-toolchain/bin/m68k-elf-gcc

ALL: hello.pgz

hello.pgz: hello.elf
	elf2pgz hello.elf hello.pgz

hello.elf:
	$(CC) -T a2560k.ld -o hello.elf hello.c

clean:
	rm hello.elf hello.pgz
```

