#pragma once
#include <stdint.h>

struct IDTEntry 
{
	uint16_t    isrLow;      // The lower 16 bits of the ISR's address
	uint16_t    kernelCS;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     reserved;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isrHigh;     // The higher 16 bits of the ISR's address
} __attribute__((packed));

struct IDTPointer
{
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed));

class IDTConstructor
{
public: 
    void SetEntry(uint8_t vector, void* isr, uint8_t flags);
    void Init();
};

__attribute__((aligned(0x10))) 
static IDTEntry idt[256];
static IDTPointer idtPointer;

extern  "C" void exception_handler(void);

// #define GET_ISR(x) (void*)(&isr_no_err_stub_##x)
// #define CALL_ISR(x) (uint32_t)(&isr_no_err_stub_##x)