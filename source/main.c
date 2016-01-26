#include <3ds.h>
#include <stdbool.h>
#include <string.h> //memcpy
#include "gfx.h"

typedef enum { EMPTY, X, O } cellState;

void renderBoard(screen, cellState[3][3][3][3], color, color, color, color);
void renderSubgrid(screen, cellState[3][3], u8, u8, color, color, color);
void renderZoomedSubgrid(screen, cellState[3][3], color, color, color);
void renderGridVLine(screen, u16, color);
void renderGridHLine(screen, u16, color);

void renderBoard(screen scr, cellState gameBoard[3][3][3][3], 
		color gridColor, color subgridColor, color xColor, color oColor)
{
	//Draw the grid
	u16 col = (0.5*scr.w) - 37;
	renderGridVLine(scr, col, gridColor);
	col += 73;
	renderGridVLine(scr, col, gridColor);
	renderGridHLine(scr, 83, gridColor);
	renderGridHLine(scr, 156, gridColor);
	
	//Draw the subgrids
	for (u8 i = 0; i < 3; i++)
	{
		for (u8 j = 0; j < 3; j++)
		{
			renderSubgrid(scr, gameBoard[i][j], i, j, subgridColor,
					xColor, oColor);
		}
	}
}

void renderSubgrid(screen scr, cellState subgrid[3][3], u8 row, u8 col, 
		color gridColor, color xColor, color oColor)
{

}

void renderZoomedSubgrid(screen scr, cellState subgrid[3][3],
		color gridColor, color xColor, color oColor)
{

}

void renderGridVLine(screen scr, u16 col, color clr)
{
	drawVLine(scr, col, 12, 227, clr);
	drawVLine(scr, col+1, 13, 226, clr);
	drawVLine(scr, col-1, 13, 226, clr);
}

void renderGridHLine(screen scr, u16 row, color clr)
{
	u16 rowStart = (0.5 * scr.w) - 107;
	u16 rowEnd = (0.5 * scr.w) + 107;
	drawHLine(scr, row, rowStart, rowEnd, clr);
	drawHLine(scr, row+1, rowStart+1, rowEnd-1, clr);
	drawHLine(scr, row-1, rowStart+1, rowEnd-1, clr);
}

int main(int argc, char *argv[])
{
	cellState gameBoard[3][3][3][3];
	u8 player;

	gfxInitDefault();

	//Blank the screens
	screen scrTop = getScreen(GFX_TOP);
	screen scrBot = getScreen(GFX_BOTTOM);
	clearScreen(scrTop);
	clearScreen(scrBot);

	//Reset the game state
	memset(gameBoard, EMPTY, 81);
	player = 0;

	while (aptMainLoop())
	{
		scrTop = getScreen(GFX_TOP);
		scrBot = getScreen(GFX_BOTTOM);
		memset(scrTop.fb, 0, 3 * scrTop.w * scrTop.h);
		memset(scrBot.fb, 0, 3 * scrBot.w * scrBot.h);
		
		hidScanInput();
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break;

		renderBoard(scrBot, gameBoard, RGBA(0x3f48ccff), RGBA(0x232b83ff), 
				WHITE, WHITE);

		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	}
	
	gfxExit();
	return 0;
}
