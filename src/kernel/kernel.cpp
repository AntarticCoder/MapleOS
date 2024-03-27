#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/arch/i686/global_constructors.h>

volatile char *video = (volatile char*)0xB8000;

size_t strlen(const char *string)
{
    size_t length = 0;
    while(string[length]) { length++; }
    return length;
}

void kprint(const char *string, size_t len)
{
    for(size_t i = 0; i < len; i++)
    {
        *video++ = string[i];
        *video++ = 15;
    }
}

extern "C" void kernel_main(void) 
{
    CallGlobalConstructors();
	kprint("Hello MapleOS", strlen("Hello MapleOS"));
    CallGlobalDestructors();
}