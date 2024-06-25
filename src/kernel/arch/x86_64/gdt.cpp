#include "kernel/arch/x86_64/gdt.h"

GDTEntry gdtEntries[6];
GDTPointer gdtPointer;

static void EncodeGDTEntry(GDTEntry* entry, unsigned long base, unsigned long limit, unsigned char access, unsigned char granularity)
{
    // Set limit and base
    entry->limitLow = limit & 0xFFFF;
    entry->baseLow = base & 0xFFFF;
    entry->baseMiddle = (base >> 16) & 0xFF;
    entry->baseHigh = (base >> 24) & 0xFF;

    // Set access
    entry->access = access;

    // Set granularity
    entry->granularity = (limit >> 16) & 0x0F;
    entry->granularity |= granularity & 0xF0;
}

void LoadGDT()
{
    // Disable interrupts
    asm("cli");

    gdtPointer.limit = (sizeof(GDTEntry) * 6) - 1;
    gdtPointer.base = (unsigned int)&gdtEntries;

    EncodeGDTEntry(&gdtEntries[0], 0, 0, 0, 0);

    EncodeGDTEntry(&gdtEntries[1], 0, 0xFFFFFFFF, 0x9A, 0xCF);
    EncodeGDTEntry(&gdtEntries[2], 0, 0xFFFFFFFF, 0x92, 0xCF);

    EncodeGDTEntry(&gdtEntries[3], 0, 0xFFFFFFFF, 0xFA, 0xCF);
    EncodeGDTEntry(&gdtEntries[4], 0, 0xFFFFFFFF, 0xF2, 0xCF);

    EncodeGDTEntry(&gdtEntries[5], 0, 0xFFFFFFFF, 0xF2, 0xCF); // Encoding null TSS because we don't use it

    asm("lgdt %0" : : "m" (gdtPointer));
}