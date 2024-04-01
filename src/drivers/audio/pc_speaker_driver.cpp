#include <drivers/audio/pc_speaker_driver.h>
#include <kernel/arch/x86_64/io_ports.h>

void PCSpeakerDriver::PlaySound(uint32_t frequency)
{
    uint32_t Div;
 	uint8_t tmp;
 
 	Div = 1193180 / frequency;
 	outportb(0x43, 0xb6);
 	outportb(0x42, (uint8_t) (Div) );
 	outportb(0x42, (uint8_t) (Div >> 8));
 
 	tmp = inportb(0x61);
  	if (tmp != (tmp | 3)) {
 		outportb(0x61, tmp | 3);
 	}
}

void PCSpeakerDriver::NoSound()
{
    uint8_t tmp = inportb(0x61) & 0xFC;
 	outportb(0x61, tmp);
}