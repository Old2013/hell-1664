#include "gpux01.h"

int main()
{
    winit(WIDTH, HEIGHT);
    vraminit();

    VRAM[0] = 0x0A;
    VRAM[80] = 0x05;

    while (1)
    {
    gpu_tick();
    }
    return 0;
}
