ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
	. = 1M;
 
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
		end_kernel = .;
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
		bin/kernel/arch/x86_64/crti.o(.init_array)
		KEEP (*(SORT(EXCLUDE_FILE(bin/kernel/arch/x86_64/crti.o bin/kernel/arch/x86_64/crtn.o) .init_array.*)))
		KEEP (*(EXCLUDE_FILE(bin/kernel/arch/x86_64/crti.o bin/kernel/arch/x86_64/crtn.o) .init_array))
		bin/kernel/arch/x86_64/crtn.o(.init_array)
	}

	.fini_array :
	{
		bin/kernel/arch/x86_64/crti.o(.fini_array)
		KEEP (*(SORT(EXCLUDE_FILE(bin/kernel/arch/x86_64/crti.o bin/kernel/arch/x86_64/crtn.o) .fini_array.*)))
		KEEP (*(EXCLUDE_FILE(bin/kernel/arch/x86_64/crti.o bin/kernel/arch/x86_64/crtn.o) .fini_array))
		bin/kernel/arch/x86_64/crtn.o(.fini_array)
	}
	
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}