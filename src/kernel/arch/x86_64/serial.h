#pragma once

class Serial
{
public:
    int Init();

    void WriteSerialCharcter(const char c);
    void WriteSerial(const char* str);
};