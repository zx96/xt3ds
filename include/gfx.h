#ifndef GFX_H
#define GFX_H

#include <3ds.h>
#include <stdbool.h>

typedef struct
{
	u8* fb;
	u16 w;
	u16 h;
}
screen;

typedef struct
{
	u8 r;
	u8 g;
	u8 b;
	u8 a;
}
color;

screen getScreen(gfxScreen_t);
bool isInBounds(screen, u16, u16);
void drawPixel(screen, u16, u16, color);
void drawLine(screen, u16, u16, u16, u16, color);
void drawHLine(screen, u16, u16, u16, color);
void drawVLine(screen, u16, u16, u16, color);

#endif
