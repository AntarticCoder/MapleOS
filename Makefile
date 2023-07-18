CC=i686-elf-g++
CFLAGS=-ffreestanding -m32 -g

LD=i686-elf-ld
LDFLAGS=-T linker.ld -m elf_i386

AC=i686-elf-as
AFLAGS= 

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
END_COLOUR=\033[0m

bin/bootloader.o: src/bootloader/bootloader.asm
	@$(AC) ${AFLAGS} src/bootloader/bootloader.asm -o bin/bootloader.o

bin/kernel.o: src/kernel/kernel.cpp
	@$(CC) ${CFLAGS} -c src/kernel/kernel.cpp -o bin/kernel.o

build: bin/kernel.o bin/bootloader.o
	@echo "${COLOUR_GREEN}Compiling MapleOS${END_COLOUR}"
	@$(LD) $(LDFLAGS) bin/bootloader.o bin/kernel.o -o bin/kernel.bin

run:
	@echo "${COLOUR_GREEN}Running MapleOS in QEMU${END_COLOUR}"
	@qemu-system-i386 -kernel bin/kernel.bin

clean:
	@echo "${COLOUR_BLUE}Cleaning MapleOS${BLUE_COLOUR}"
	@rm -rf bin/*.o bin/*.bin bin/*.elf bin/*.iso bin/*.img bin/*.bin

all: build run
