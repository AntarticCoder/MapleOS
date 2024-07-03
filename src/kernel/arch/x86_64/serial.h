#pragma once

class Serial
{
private:
    int Init();
public:
    Serial();

    static void WriteSerialCharcter(const char c);
    static void WriteSerial(const char* str);
};