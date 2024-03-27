/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text

.global _start
.type _start, @function

/*
; gdt_start:
; 	null_descriptor:
; 		dd 0
; 		dd 0
; 	code_descriptor:
; 		dw 0xffff
; 		dw 0
; 		db 0
; 		db 10011010
; 		db 11001111
; 		db 0
; 	data_descriptor:
; 		dw 0xffff
; 		dw 0
; 		db 0
; 		db 10010010
; 		db 11001111
; 		db 0
; 	gdt_end:

; gdt_descriptor:
; 	dw gdt_end - gdt_start - 1 ; size
; 	dd gdt_start ; start

; 	CODE_SEG equ code_descriptor - gdt_start
; 	DATA_SEG equ data_descriptor - gdt_start
*/
_start:
	mov $stack_top, %esp

	/*
	; cli 
	; lgdt [gdt_descriptor]
	*/
	

	call _init
	call kernel_main

	cli
1:	hlt
	jmp 1b

.size _start, . - _start
