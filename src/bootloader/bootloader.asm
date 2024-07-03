/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC, 0x36d76289
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

/* .section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.long 0, 0, 0, 0, 0
.long 0 # 0 = set graphics mode
.long 1024, 768, 32 # Width, height, depth
*/

.set MBOOT2_MAGIC, 0xE85250D6
.set MBOOT2_ARCH, 0
.set MBOOT2_LENGTH, (Multiboot2HeaderEnd - Multiboot2Header)
.set MBOOT2_CHECKSUM, -(MBOOT2_MAGIC + MBOOT2_ARCH + MBOOT2_LENGTH)

.section .multiboot

.align 0x8
Multiboot2Header:
.long MBOOT2_MAGIC
.long MBOOT2_ARCH
.long MBOOT2_LENGTH
.long MBOOT2_CHECKSUM
.long 0, 0, 0, 0, 0
.long 0 # 0 = set graphics mode
.long 1024, 768, 32 # Width, height, depth

/* .short 0
.short 0
.long 8*/
Multiboot2HeaderEnd:

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text

.global _start
.global kernel_main
.type _start, @function

_start:
	mov $stack_top, %esp

	pushl %ebx
	pushl %eax
	call _init
	call kernel_main

	cli
1:	hlt
	jmp 1b

.size _start, . - _start
