#include <stdint.h>

class PCSpeakerDriver
{
public:
    static void PlaySound(uint32_t frequency);
    static void NoSound();
};