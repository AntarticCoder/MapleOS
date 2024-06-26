#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/arch/x86_64/global_constructors.h>
#include <kernel/arch/x86_64/serial.h>
#include <kernel/arch/x86_64/io_ports.h>
#include <kernel/arch/x86_64/gdt.h>
#include <kernel/terminal.h>

#include <drivers/audio/pc_speaker_driver.h>

extern uint32_t endkernel;

extern "C" void kernel_main(void) 
{
    CallGlobalConstructors();

    Terminal terminal;
    terminal.Init();
    terminal.Printf("Hello, kernel!\n", VGA_COLOR::GREEN);
    terminal.Printf("Testing Printf d: %d\n", VGA_COLOR::GREEN, 128);
    terminal.Printf("Testing Printf i: %i\n", VGA_COLOR::GREEN, 256);
    terminal.Printf("Testing Printf u: %u\n", VGA_COLOR::GREEN, 512);
    terminal.Printf("Testing Printf c: %c\n", VGA_COLOR::GREEN, 'A');
    terminal.Printf("Testing Printf s: %s\n", VGA_COLOR::RED, "Printf String");

    terminal.Printf("Sizeof GDT Entry: %d\n", VGA_COLOR::GREEN, sizeof(GDTEntry));
    terminal.Printf("Sizeof GDT Pointer: %d\n", VGA_COLOR::GREEN, sizeof(GDTPointer));

    LoadGDT();
    terminal.Printf("GDT Loaded\n", VGA_COLOR::GREEN);

    Serial serial;
    serial.Init();
    serial.WriteSerial("Hello\n");

    // PCSpeakerDriver::PlaySound(10);
    while(true)
    {
       // Hang
    }

    CallGlobalDestructors();
}