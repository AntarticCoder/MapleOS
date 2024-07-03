#include <kernel/arch/x86_64/serial.h>
#include <kernel/arch/x86_64/io_ports.h>

#include <stdint.h>

const uint16_t PORT = 0x3f8; /* COM1 */

int Serial::Init()
{
    outportb(PORT + 1, 0x00);    // Disable all interrupts
    outportb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outportb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outportb(PORT + 1, 0x00);    //                  (hi byte)
    outportb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    outportb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outportb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    outportb(PORT + 4, 0x1E);    // Set in loopback mode, test the serial chip
    outportb(PORT + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)
    
    if(inportb(PORT + 0) != 0xAE) {
        return 1;
    }
    
    outportb(PORT + 4, 0x0F);

    WriteSerial("MapleOS: Serial initialized\n");
    return 0;
}

Serial::Serial()
{
    Init();
}

void Serial::WriteSerialCharcter(char c) 
{
    while(inportb(PORT + 5) & 0x20 == 0);
    outportb(PORT, c);
}

void Serial::WriteSerial(const char* str)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        WriteSerialCharcter(str[i]);
    }
} 