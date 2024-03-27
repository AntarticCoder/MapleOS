#pragma once
#include <stdint.h>

const uint32_t VGA_WIDTH = 80;
const uint32_t VGA_HEIGHT = 25;
extern volatile char* VGA_MEMORY;

enum VGA_COLOR : char
{
    BLACK = 0x00,
    BLUE = 0x01,
    GREEN = 0x02,
    CYAN = 0x03,
    RED = 0x04,
    MAGENTA = 0x05,
    BROWN = 0x06,
    LIGHT_GREY = 0x07,
    DARK_GREY = 0x08,
    LIGHT_BLUE = 0x09,
    LIGHT_GREEN = 0x0A,
    LIGHT_CYAN = 0x0B,
    LIGHT_RED = 0x0C,
    LIGHT_MAGENTA = 0x0D,
    LIGHT_BROWN = 0x0E,
    WHITE = 0x0F
};

void PutChar(char c, VGA_COLOR color, uint32_t x, uint32_t y);
void ClearScreen();