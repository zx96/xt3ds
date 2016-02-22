#include <3ds.h>
#include <stdbool.h>
#include <string.h> //memcpy
#include "gfx2d.h"
#include "o_rgba.h"
#include "x_rgba.h"

typedef enum { EMPTY, X, O } cellState;

void renderBoard(screen, cellState[3][3][3][3], color, color, color, u32 *, u32 *);
void renderSubgrid(screen, cellState[3][3], color, u32 *, u32 *);
void renderZoomedSubgrid(screen, cellState[3][3], color, u32 *, u32 *);
void renderLargeGrid(screen, color);
void renderGridVLine(screen, u16, color);
void renderGridHLine(screen, u16, color);

void renderBoard(screen scr, cellState gameBoard[3][3][3][3], 
		color gridColor, color subgridColor, color activeSubgridColor, 
		u32* xBitmap, u32* oBitmap)
{
	//Draw the grid
	renderLargeGrid(scr, gridColor);
	
	//Draw the subgrids
	for (u8 i = 0; i < 3; i++)
	{
		for (u8 j = 0; j < 3; j++)
		{
			renderSubgrid(scr, gameBoard[i][j], subgridColor,
					xBitmap, oBitmap);
		}
	}
}

//Render the subgrid (58x58 px) in the center of the appropriate area
void renderSubgrid(screen scr, cellState subgrid[3][3], 
		color gridColor, u32 *xBitmap, u32 *oBitmap)
{
	
}

void renderZoomedSubgrid(screen scr, cellState subgrid[3][3],
		color gridColor, u32 *xBitmap, u32 *oBitmap)
{
	renderLargeGrid(scr, gridColor);
}

//Render a large (216x216 px) grid in the center of the screen
void renderLargeGrid(screen scr, color gridColor)
{
	u16 col = (0.5*scr.w) - 37;
	renderGridVLine(scr, col, gridColor);
	col += 73;
	renderGridVLine(scr, col, gridColor);
	renderGridHLine(scr, 83, gridColor);
	renderGridHLine(scr, 156, gridColor);
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
	screen scrTop, scrBot;

	gfxInitDefault();

	//Reset the game state
	memset(gameBoard, EMPTY, 81);
	player = 0;

	while (aptMainLoop())
	{
		//Clear the screens
		scrTop = getScreen(GFX_TOP);
		scrBot = getScreen(GFX_BOTTOM);
		clearScreen(scrTop);
		clearScreen(scrBot);
		
		//Check keypresses
		hidScanInput();
		u32 kDown = hidKeysDown();

		if (kDown & KEY_START) break;

		//Render the main board
		renderBoard(scrTop, gameBoard, RGBA(0x3f48ccff), RGBA(0x232b83ff), 
				WHITE, NULL, NULL);
		renderZoomedSubgrid(scrBot, gameBoard[0][0], WHITE, NULL, NULL);

		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	}
	
	gfxExit();
	return 0;
}
