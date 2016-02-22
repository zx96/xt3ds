#ifndef GFX2D_H
#define GFX2D_H

#include <3ds.h>
#include <stdbool.h>

#define RGBA(hex)   (color){(u8)(hex>>24),(u8)(hex>>16),(u8)(hex>>8),(u8)hex}
#define ARGB(hex)	(color){(u8)(hex>>16),(u8)(hex>>8),(u8)hex,(u8)(hex>>24)}
#define ABGR(hex)	(color){(u8)(hex>>24),(u8)hex,(u8)(hex>>8),(u8)(hex>>16)}
#define RGB(hex)	(color){(u8)(hex>>16),(u8)(hex>>8),(u8)hex,0xff}
#define BGR(hex)	(color){(u8)hex,(u8)(hex>>8),(u8)(hex>>16),0xff}
#define CLEAR		(color){0x00,0x00,0x00,0x00}
#define BLACK		(color){0x00,0x00,0x00,0xff}
#define WHITE		(color){0xff,0xff,0xff,0xff}

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
void clearScreen(screen);
bool isInBounds(screen, u16, u16);
void drawPixel(screen, u16, u16, color);
void drawPixelSafe(screen, u16, u16, color);
void drawLine(screen, u16, u16, u16, u16, color);
void drawLineSafe(screen, u16, u16, u16, u16, color);
void drawHLine(screen, u16, u16, u16, color);
void drawHLineSafe(screen, u16, u16, u16, color);
void drawVLine(screen, u16, u16, u16, color);
void drawVLineSafe(screen, u16, u16, u16, color);
void drawRGBABitmap(screen, u32 *, u16, u16, u16, u16);

#endif
