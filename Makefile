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

SRC_DIR := src
BIN_DIR := bin

ASM_SOURCES=$(shell find src -name '*.asm')
ASM_OBJECTS = $(patsubst src/%.asm, bin/%.o, $(ASM_SOURCES))

CPP_SOURCES=$(shell find src -name '*.cpp')
CPP_OBJECTS := $(patsubst src/%.cpp, bin/%.o, $(CPP_SOURCES))

TARGET=bin/mapleos.bin

${BIN_DIR}/%.o: ${SRC_DIR}/%.asm
	@echo "${COLOUR_GREEN}Building ASM Object: $< ${END_COLOUR}"
	@mkdir -p $(dir $@)
	@$(AC) ${AFLAGS} $< -o $@

${BIN_DIR}/%.o: ${SRC_DIR}/%.cpp
	@echo "${COLOUR_GREEN}Building CPP Object: $< ${END_COLOUR}"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

${TARGET}: ${ASM_OBJECTS} ${CPP_OBJECTS}
	@echo "${COLOUR_GREEN}Compiling MapleOS${END_COLOUR}"
	@$(LD) $(LDFLAGS) ${ASM_OBJECTS} ${CPP_OBJECTS} $(CRTBEGIN_OBJ) $(CRTEND_OBJ) -o ${TARGET}

iso:
	@mkdir -p isodir/boot/grub
	@cp grub.cfg isodir/boot/grub/
	@cp bin/mapleos.bin isodir/boot/
	@grub-mkrescue -o mapleos.iso isodir/

run:
	@mkdir -p bin
	@echo "${COLOUR_GREEN}Running MapleOS in QEMU${END_COLOUR}"
	@qemu-system-x86_64 -audiodev coreaudio,id=snd0 -machine pcspk-audiodev=snd0 -serial stdio -append 'console=ttyS0,38400' -kernel ${TARGET}

clean:
	@echo "${COLOUR_BLUE}Cleaning MapleOS${END_COLOUR}"
	@rm -rf bin

all: ${TARGET} run
