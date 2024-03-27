ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
	/* Begin putting sections at 1 MiB, a conventional place for kernels to be
	   loaded at by the bootloader. */
	. = 1M;
 
	/* First put the multiboot header, as it is required to be put very early
	   early in the image or the bootloader won't recognize the file format.
	   Next we'll put the .text section. */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
 
	/* Read-only data. */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}
 
	/* Read-write data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	.init_array :
	{
		bin/crti.o(.init_array)
		KEEP (*(SORT(EXCLUDE_FILE(bin/crti.o bin/crtn.o) .init_array.*)))
		KEEP (*(EXCLUDE_FILE(bin/crti.o bin/crtn.o) .init_array))
		bin/crtn.o(.init_array)
	}

	/* Include the list of termination functions sorted. */
	.fini_array :
	{
		bin/crti.o(.fini_array)
		KEEP (*(SORT(EXCLUDE_FILE(bin/crti.o bin/crtn.o) .fini_array.*)))
		KEEP (*(EXCLUDE_FILE(bin/crti.o bin/crtn.o) .fini_array))
		bin/crtn.o(.fini_array)
	}
 
	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
 
	/* The compiler may produce other sections, by default it will put them in
	   a segment with the same name. Simply add stuff here as needed. */
}