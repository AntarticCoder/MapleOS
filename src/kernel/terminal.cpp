#include <kernel/terminal.h>

Terminal::Terminal()
{
    _buffer = (char*)0xB8000;
    _cursorX = 0;
    _cursorY = 0;

    ClearScreen();
}

void Terminal::Printf(const char* str, VGA_COLOR color, ...)
{
    va_list args;
    va_start(args, color);

    int length = strlen(str);

    for(int i = 0; i < length; i++)
    {
        if(_format == true)
        {
            switch(str[i])
            {
                case 'd':
                {
                    int num = va_arg(args, int);
                    char numStr[32];
                    itoa(num, numStr, 10);
                    int numLength = strlen(numStr);
                    for(int j = 0; j < numLength; j++)
                    {
                        PutChar(numStr[j], color, _cursorX, _cursorY);
                        _cursorX++;
                    }
                    break;
                }
                case 'i':
                {
                    int num = va_arg(args, int);
                    char numStr[32];
                    itoa(num, numStr, 10);
                    int numLength = strlen(numStr);
                    for(int j = 0; j < numLength; j++)
                    {
                        PutChar(numStr[j], color, _cursorX, _cursorY);
                        _cursorX++;
                    }
                    break;
                }
                case 'u':
                {
                    int num = va_arg(args, int);
                    char numStr[32];
                    itoa(num, numStr, 10);
                    int numLength = strlen(numStr);
                    for(int j = 0; j < numLength; j++)
                    {
                        PutChar(numStr[j], color, _cursorX, _cursorY);
                        _cursorX++;
                    }
                    break;
                }
                case 'c':
                {
                    char c = va_arg(args, int);
                    PutChar(c, color, _cursorX, _cursorY);
                    _cursorX++;
                    break;
                }
                case 's':
                {
                    char* str = va_arg(args, char*);
                    int strLength = strlen(str);
                    for(int j = 0; j < strLength; j++)
                    {
                        PutChar(str[j], color, _cursorX, _cursorY);
                        _cursorX++;
                    }
                    break;
                }
            }
            _format = false;
            continue;
        }

        if(str[i] == '%')
        {
            _format = true;
            continue;
        }

        if(str[i] == '\n')
        {  
            for(; _cursorX < VGA_WIDTH; _cursorX++)
            {
                PutChar(' ', VGA_COLOR::BLACK, _cursorX, _cursorY);
            }
            _cursorX = 0;
            _cursorY++;
            continue;
        }

        PutChar(str[i], color, _cursorX, _cursorY);
        _cursorX++;
    }
    va_end(args);
}