#pragma once
#include <stdarg.h>

#include <kernel/arch/i686/vga.h>
#include <kernel/string.h>

class Terminal
{
private:
    char* _buffer;
    int _cursorX;
    int _cursorY;
    bool _format = false;
public:
    Terminal();

    void Printf(char* str, VGA_COLOR color, ...);
};