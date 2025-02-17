#include <kernel/arch/x86_64/idt.h>

extern "C" void isr_no_err_stub_0();
extern "C" void isr_no_err_stub_1();
extern "C" void isr_no_err_stub_2();
extern "C" void isr_no_err_stub_3();
extern "C" void isr_no_err_stub_4();
extern "C" void isr_no_err_stub_5();
extern "C" void isr_no_err_stub_6();
extern "C" void isr_no_err_stub_7();
extern "C" void isr_err_stub_8();
extern "C" void isr_no_err_stub_9();
extern "C" void isr_err_stub_10();
extern "C" void isr_err_stub_11();
extern "C" void isr_err_stub_12();
extern "C" void isr_err_stub_13();
extern "C" void isr_err_stub_14();
extern "C" void isr_no_err_stub_15();
extern "C" void isr_no_err_stub_16();
extern "C" void isr_err_stub_17();
extern "C" void isr_no_err_stub_18();
extern "C" void isr_no_err_stub_19();
extern "C" void isr_no_err_stub_20();
extern "C" void isr_no_err_stub_21();
extern "C" void isr_no_err_stub_22();
extern "C" void isr_no_err_stub_23();
extern "C" void isr_no_err_stub_24();
extern "C" void isr_no_err_stub_25();
extern "C" void isr_no_err_stub_26();
extern "C" void isr_no_err_stub_27();
extern "C" void isr_no_err_stub_28();
extern "C" void isr_no_err_stub_29();
extern "C" void isr_err_stub_30();
extern "C" void isr_no_err_stub_31();

void (*isr_table[])() = {
    isr_no_err_stub_0,
	isr_no_err_stub_1,
	isr_no_err_stub_2,
	isr_no_err_stub_3,
	isr_no_err_stub_4,
	isr_no_err_stub_5,
	isr_no_err_stub_6,
	isr_no_err_stub_7,
	isr_err_stub_8,
	isr_no_err_stub_9,
	isr_err_stub_10,
	isr_err_stub_11,
	isr_err_stub_12,
	isr_err_stub_13,
	isr_err_stub_14,
	isr_no_err_stub_15,
	isr_no_err_stub_16,
	isr_err_stub_17,
	isr_no_err_stub_18,
	isr_no_err_stub_19,
	isr_no_err_stub_20,
	isr_no_err_stub_21,
	isr_no_err_stub_22,
	isr_no_err_stub_23,
	isr_no_err_stub_24,
	isr_no_err_stub_25,
	isr_no_err_stub_26,
	isr_no_err_stub_27,
	isr_no_err_stub_28,
	isr_no_err_stub_29,
	isr_err_stub_30,
	isr_no_err_stub_31
};

__attribute__((noreturn))
extern  "C" void exception_handler(void) {
    __asm__ volatile ("cli");
    __asm__ volatile ("hlt");
}

void IDTConstructor::SetEntry(uint8_t vector, void* isr, uint8_t flags)
{
    IDTEntry* descriptor = &idt[vector];

    descriptor->isrLow = (uint32_t)isr & 0xFFFF;
    descriptor->kernelCS = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
    descriptor->attributes = flags;
    descriptor->isrHigh = (uint32_t)isr >> 16;
    descriptor->reserved = 0;
}

void IDTConstructor::Init()
{
    idtPointer.base = (uintptr_t)&idt[0];
    idtPointer.limit = (uint16_t)sizeof(IDTEntry) * 256;

    for (uint8_t vector = 0; vector < 32; vector++) 
    {
        SetEntry(vector, (void*)isr_table[vector], 0x8E);
    }

    __asm__ volatile ("lidt %0" : : "m"(idtPointer)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}
