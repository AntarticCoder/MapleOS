#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

volatile char *video = (volatile char*)0xB8000;

void kprint(const char *string)
{
    while(*string != 0)
    {
        *video++ = *string++;
        *video++ = 15;
    }
}

extern "C" void kernel_main(void) 
{
	kprint("Hello MapleOS");
}