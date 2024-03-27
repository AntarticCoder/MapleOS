#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/arch/i686/global_constructors.h>
#include <kernel/terminal.h>

extern "C" void kernel_main(void) 
{
    CallGlobalConstructors();

    Terminal terminal;
    terminal.Printf("Hello, kernel!\n", VGA_COLOR::GREEN);
    terminal.Printf("Testing Printf d: %d\n", VGA_COLOR::GREEN, 128);
    terminal.Printf("Testing Printf i: %i\n", VGA_COLOR::GREEN, 256);
    terminal.Printf("Testing Printf u: %u\n", VGA_COLOR::GREEN, 512);
    terminal.Printf("Testing Printf c: %c\n", VGA_COLOR::GREEN, 'A');
    terminal.Printf("Testing Printf s: %s\n", VGA_COLOR::GREEN, "Printf String");

    CallGlobalDestructors();
}