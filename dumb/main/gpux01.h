#include <stdio.h>
#include <stdint.h>
#include "winlib.h"
#include "symmap.h"

#define WIDTH 640
#define HEIGHT 480

uint8_t VRAM[4800];


int cursor = 0;

char draw_sym(uint8_t symbol, int x, int y);

void vraminit()
{
    for (int x = 0; x < 4800; x ++)
    {
        VRAM[x] = 0x00;
    }
}

void gpu_tick()
{

    for (int y = 0; y < 60; y ++)
    {
        for (int x = 0; x < 80; x ++)
        {
            draw_sym(VRAM[y*80 + x], x*8, y*8);
        }
    }

    wupdate();
}

char draw_sym(uint8_t symbol, int x, int y)
{
    if (symbol == 0x00) return 1;

    int map_index = (symbol-1) * 64;
    int pixel_index = y*WIDTH + x;

    for (int my = 0; my < 8; my ++)
    {
        for (int mx = 0; mx < 8; mx ++)
        {
            pixels[((pixel_index + mx) * 4)+1] = symmap[map_index + my*8 + mx]*255;
        }
        pixel_index += WIDTH;
    }
    return 0;
}

