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

SRC_DIR := src
BIN_DIR := bin

CPP_SOURCES=$(shell find src -name '*.cpp')
CPP_OBJECTS := $(patsubst src/%.cpp, bin/%.o, $(CPP_SOURCES))

TARGET=bin/kernel.bin

bin/bootloader.o: src/bootloader/bootloader.asm
	@$(AC) ${AFLAGS} src/bootloader/bootloader.asm -o bin/bootloader.o

bin/crti.o: src/kernel/arch/x86_64/crti.asm
	@$(AC) ${AFLAGS} src/kernel/arch/x86_64/crti.asm -o bin/crti.o

bin/crtn.o: src/kernel/arch/x86_64/crtn.asm
	@$(AC) ${AFLAGS} src/kernel/arch/x86_64/crtn.asm -o bin/crtn.o

${BIN_DIR}/%.o: ${SRC_DIR}/%.cpp
	@echo "${COLOUR_GREEN}Building Object: $< ${END_COLOUR}"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

${TARGET}: ${CPP_OBJECTS} bin/bootloader.o ${CRTI_OBJ} ${CRTN_OBJ}
	@echo "${COLOUR_GREEN}Compiling MapleOS${END_COLOUR}"
	@$(LD) $(LDFLAGS) bin/bootloader.o ${CPP_OBJECTS} $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(CRTEND_OBJ) $(CRTN_OBJ) -o ${TARGET}

run:
	@echo "${COLOUR_GREEN}Running MapleOS in QEMU${END_COLOUR}"
	@qemu-system-x86_64 -audiodev coreaudio,id=snd0 -machine pcspk-audiodev=snd0 -serial stdio -append 'console=ttyS0,38400' -kernel ${TARGET}

clean:
	@echo "${COLOUR_BLUE}Cleaning MapleOS${END_COLOUR}"
	@rm -rf bin/kernel
	# @rm -rf bin/*.o bin/*.bin bin/*.elf bin/*.iso bin/*.img bin/*.bin

all: ${TARGET} run
