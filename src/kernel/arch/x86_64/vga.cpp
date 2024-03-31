#include <kernel/arch/x86_64/vga.h>

volatile char* VGA_MEMORY = (volatile char*)0xB8000;

void PutChar(char c, VGA_COLOR color, uint32_t x, uint32_t y) 
{
    uint32_t index = y * VGA_WIDTH + x;
    VGA_MEMORY[index * 2] = c;
    VGA_MEMORY[index * 2 + 1] = char(color);
}

void ClearScreen() 
{
    for(uint32_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        PutChar(' ', VGA_COLOR::BLACK, i % VGA_WIDTH, i / VGA_WIDTH);
    }
}