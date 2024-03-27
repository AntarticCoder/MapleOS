CC=i686-elf-g++
CFLAGS=-ffreestanding -m32 -g -fno-use-cxa-atexit -I src

LD=i686-elf-ld
LDFLAGS=-T linker.ld -m elf_i386

AC=i686-elf-as
AFLAGS= 

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
END_COLOUR=\033[0m

CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTI_OBJ=bin/crti.o
CRTN_OBJ=bin/crtn.o

bin/crti.o: src/kernel/arch/i686/crti.asm
	@$(AC) ${AFLAGS} src/kernel/arch/i686/crti.asm -o bin/crti.o

bin/crtn.o: src/kernel/arch/i686/crtn.asm
	@$(AC) ${AFLAGS} src/kernel/arch/i686/crtn.asm -o bin/crtn.o

bin/bootloader.o: src/bootloader/bootloader.asm
	@$(AC) ${AFLAGS} src/bootloader/bootloader.asm -o bin/bootloader.o

bin/global_constructors.o: src/kernel/arch/i686/global_constructors.cpp
	@$(CC) ${CFLAGS} -c src/kernel/arch/i686/global_constructors.cpp -o bin/global_constructors.o

bin/vga.o: src/kernel/arch/i686/vga.cpp
	@$(CC) ${CFLAGS} -c src/kernel/arch/i686/vga.cpp -o bin/vga.o

bin/string.o: src/kernel/string.cpp
	@$(CC) ${CFLAGS} -c src/kernel/string.cpp -o bin/string.o

bin/terminal.o: src/kernel/terminal.cpp
	@$(CC) ${CFLAGS} -c src/kernel/terminal.cpp -o bin/terminal.o

bin/kernel.o: src/kernel/kernel.cpp
	@$(CC) ${CFLAGS} -c src/kernel/kernel.cpp -o bin/kernel.o

build: bin/kernel.o bin/terminal.o bin/string.o bin/vga.o bin/global_constructors.o bin/bootloader.o ${CRTI_OBJ} ${CRTN_OBJ}
	@echo "${COLOUR_GREEN}Compiling MapleOS${END_COLOUR}"
	@$(LD) $(LDFLAGS) bin/bootloader.o bin/kernel.o bin/terminal.o bin/string.o bin/vga.o bin/global_constructors.o $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(CRTEND_OBJ) $(CRTN_OBJ) -o bin/kernel.bin

run:
	@echo "${COLOUR_GREEN}Running MapleOS in QEMU${END_COLOUR}"
	@qemu-system-i386 -kernel bin/kernel.bin

clean:
	@echo "${COLOUR_BLUE}Cleaning MapleOS${BLUE_COLOUR}"
	@rm -rf bin/*.o bin/*.bin bin/*.elf bin/*.iso bin/*.img bin/*.bin

all: build run
