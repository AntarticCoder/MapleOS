#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <bootloader/multiboot.h>

#include <kernel/arch/x86_64/global_constructors.h>
#include <kernel/arch/x86_64/serial.h>
#include <kernel/arch/x86_64/io_ports.h>
#include <kernel/arch/x86_64/gdt.h>
#include <kernel/terminal.h>

#include <drivers/audio/pc_speaker_driver.h>

extern uint32_t endkernel;

struct framebuffer_info {
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;
};

struct framebuffer_info fb_info;

void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR)
{
    unsigned char* location = (unsigned char*)0xA0000 + 320 * pos_y + pos_x;
    *location = VGA_COLOR;
}

extern "C" void kernel_main(uint32_t magic, uint32_t address) 
{
    CallGlobalConstructors();

    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        Serial::WriteSerial("Invalid magic number\n");
        return;
    }

    struct multiboot_tag *tag;

    for (tag = (struct multiboot_tag *) (address + 8); tag->type != MULTIBOOT_TAG_TYPE_END; tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag + ((tag->size + 7) & ~7))) {
        if (tag->type == MULTIBOOT_TAG_TYPE_FRAMEBUFFER) {
            multiboot_tag_framebuffer *fb_tag = (multiboot_tag_framebuffer *) tag;
            fb_info.framebuffer_addr = fb_tag->common.framebuffer_addr;
            fb_info.framebuffer_pitch = fb_tag->common.framebuffer_pitch;
            fb_info.framebuffer_width = fb_tag->common.framebuffer_width;
            fb_info.framebuffer_height = fb_tag->common.framebuffer_height;
            fb_info.framebuffer_bpp = fb_tag->common.framebuffer_bpp;
        }
    }
    

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

    // Serial serial;
    Serial::WriteSerial("Hello\n");

    if (fb_info.framebuffer_addr) {
        terminal.Printf("Framebuffer Address found : %x\n", VGA_COLOR::GREEN, fb_info.framebuffer_addr);
        Serial::WriteSerial("Framebuffer Address found\n");
    }   
    else {
        terminal.Printf("Framebuffer Address not found: %x\n", VGA_COLOR::RED, fb_info.framebuffer_addr);
        Serial::WriteSerial("Framebuffer Address not found\n");
    }

    

    // PCSpeakerDriver::PlaySound(10);
    while(true)
    {
       // Hang
    }

    CallGlobalDestructors();
}