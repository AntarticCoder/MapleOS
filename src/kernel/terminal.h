#pragma once
#include <stdarg.h>

#include <kernel/arch/x86_64/vga.h>
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

    void Init();
    void Printf(const char* str, VGA_COLOR color, ...);
};