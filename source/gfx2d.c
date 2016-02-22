#include <math.h>
#include <stdbool.h>
#include <string.h> //memset
#include "gfx2d.h"
#include "minlib.h"

screen getScreen(gfxScreen_t scr)
{
	screen s;
	s.fb = gfxGetFramebuffer(scr, GFX_LEFT, &(s.h), &(s.w));
	return s;
}

void clearScreen(screen scr)
{
	memset(scr.fb, 0, 3*scr.w *scr.h);
}

bool isInBounds(screen scr, u16 x, u16 y) {
	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= scr.w) return false;
	if (y >= scr.h) return false;
	return true;
}

void drawPixel(screen scr, u16 x, u16 y, color clr)
{
	//Transparent pixel
	if (clr.a == 0) return;
	
	u32 index = 3 * ((x + 1) * 240 - y - 1); //Get the address of the pixel
	if (clr.a == 255) //Solid pixel
	{
		scr.fb[index] = clr.b;
		scr.fb[index + 1] = clr.g;
		scr.fb[index + 2] = clr.r;
	}
	else //Alpha blending
	{
		float alpha_ratio = clr.a/255.0f;
		scr.fb[index] = scr.fb[index] * (1 - alpha_ratio) 
				+ clr.b * alpha_ratio;
		scr.fb[index + 1] = scr.fb[index + 1] * (1 - alpha_ratio) 
				+ clr.g * alpha_ratio;
		scr.fb[index + 2] = scr.fb[index + 2] * (1 - alpha_ratio) 
				+ clr.r * alpha_ratio;
	}
}

void drawPixelSafe(screen scr, u16 x, u16 y, color clr)
{
	if (!isInBounds(scr, x, y)) return;

	drawPixel(scr, x, y, clr);
}

//Wu's Line Algorithm
//Optimized with integer endpoints
void drawLine(screen scr, u16 x1, u16 y1, u16 x2, u16 y2, color clr)
{
	bool steep = absVal(y2 - y1) > absVal(x2 - x1);
	if (steep)
	{
		swap_u16(&x1, &y1);
		swap_u16(&x2, &y2);
	}
	if (x1 > x2)
	{
		swap_u16(&x1, &x2);
		swap_u16(&y1, &y2);
	}
	
	s16 dx = x2 - x1;
	s16 dy = y2 - y1;
	float m = (float)dy / (float)dx;
	
	s16 i;
	float fPart, inter = y1;
	for (i = x1; i < x2; i++)
	{
		fPart = inter - (int)inter;
		if (steep)
		{
			drawPixel(scr, inter, i, 
					(color){clr.r, clr.g, clr.b, (1 - fPart)*(float)clr.a});
			drawPixel(scr, inter+1, i, 
					(color){clr.r, clr.g, clr.b, fPart*(float)clr.a});
		}
		else
		{
			drawPixel(scr, i, inter, 
					(color){clr.r, clr.g, clr.b, (1 - fPart)*(float)clr.a});
			drawPixel(scr, i, inter+1, 
					(color){clr.r, clr.g, clr.b, fPart*(float)clr.a});
		}
		inter += m;
	}
}

void drawLineSafe(screen scr, u16 x1, u16 y1, u16 x2, u16 y2, color clr)
{
	bool steep = absVal(y2 - y1) > absVal(x2 - x1);
	if (steep)
	{
		swap_u16(&x1, &y1);
		swap_u16(&x2, &y2);
	}
	if (x1 > x2)
	{
		swap_u16(&x1, &x2);
		swap_u16(&y1, &y2);
	}
	
	s16 dx = x2 - x1;
	s16 dy = y2 - y1;
	float m = (float)dy / (float)dx;
	
	s16 i;
	float fPart, inter = y1;
	for (i = x1; i < x2; i++)
	{
		fPart = inter - (int)inter;
		if (steep)
		{
			drawPixelSafe(scr, inter, i, 
					(color){clr.r, clr.g, clr.b, (1 - fPart)*(float)clr.a});
			drawPixelSafe(scr, inter+1, i, 
					(color){clr.r, clr.g, clr.b, fPart*(float)clr.a});
		}
		else
		{
			drawPixelSafe(scr, i, inter, 
					(color){clr.r, clr.g, clr.b, (1 - fPart)*(float)clr.a});
			drawPixelSafe(scr, i, inter+1, 
					(color){clr.r, clr.g, clr.b, fPart*(float)clr.a});
		}
		inter += m;
	}
}

void drawHLine(screen scr, u16 row, u16 x1, u16 x2, color clr)
{
	if (x1 > x2) swap_u16(&x1, &x2);
	
	u16 i;
	for (i = x1; i <= x2; i++) drawPixel(scr, i, row, clr);
}

void drawHLineSafe(screen scr, u16 row, u16 x1, u16 x2, color clr)
{
	if (x1 > x2) swap_u16(&x1, &x2);
	
	u16 i;
	for (i = x1; i <= x2; i++) drawPixelSafe(scr, i, row, clr);
}

void drawVLine(screen scr, u16 col, u16 y1, u16 y2, color clr)
{
	if (y1 > y2) swap_u16(&y1, &y2);
	
	u16 i;
	for (i = y1; i <= y2; i++) drawPixel(scr, col, i, clr);
}

void drawVLineSafe(screen scr, u16 col, u16 y1, u16 y2, color clr)
{
	if (y1 > y2) swap_u16(&y1, &y2);
	
	u16 i;
	for (i = y1; i <= y2; i++) drawPixelSafe(scr, col, i, clr);
}

void drawRGBABitmap(screen scr, u32 *bitmap, u16 width, u16 height, u16 x, u16 y)
{
	for (u16 i = x; i - x < width; i++)
	{
		for (u16 j = y; j - y < height; j++)
		{
			drawPixel(scr, i, j, RGBA(*bitmap));
			bitmap++;
		}
	}
}
