#include "common.h" 
#include "minefield.h"


void game_over(minefield* mf) {
	mf->state = GAME_OVER;

	// show all bomb locations
	for (uint8_t x = 0; x < mf->width; x++)
		for (uint8_t y = 0; y < mf->height; y++)
			if (CELL(mf, x, y) & HASBOMB)
				CELL(mf, x, y) |= ISOPEN;
}


#ifndef RESET_MINEFIELD
void fill_minefield(minefield* mf, uint8_t num_bombs)
{
	// Clear the minefield:
	for (uint8_t x = 0; x < mf->width; x++) {
		for (uint8_t y = 0; y < mf->height; y++) {
			CELL(mf, x, y) = 0;
		}
	}

	// Place bombs:
	while (num_bombs--) {
		uint8_t x = random_number(0, mf->width - 1);
		uint8_t y = random_number(0, mf->height - 1);
		CELL(mf, x, y) |= HASBOMB;
	}

	// Compute neighbouring bombs:
	for (uint8_t x = 0; x < mf->width; x++){
		for (uint8_t y = 0; y < mf->height; y++){
			if ((CELL(mf, x, y) & HASBOMB)) continue;

			uint8_t count = 0;
			if (x > 0 && y > 0 && (CELL(mf, x-1, y-1) & HASBOMB)) count++;
			if (x > 0 && (CELL(mf, x-1, y) & HASBOMB)) count++;
			if (x > 0 && y < mf->height-1 && (CELL(mf, x-1, y+1) & HASBOMB)) count++;

			if (y > 0 && (CELL(mf, x, y-1) & HASBOMB)) count++;
			if (y < mf->height-1 && (CELL(mf, x, y+1) & HASBOMB)) count++;

			if (x < mf->width-1 && y > 0 && (CELL(mf, x+1, y-1) & HASBOMB)) count++;
			if (x < mf->width-1 && (CELL(mf, x+1, y) & HASBOMB)) count++;
			if (x < mf->width-1 && y < mf->height-1 && (CELL(mf, x+1, y+1) & HASBOMB)) count++;

			// Store the count in the 4 lowest bits:
			CELL(mf, x, y) |= count;
		}
	}
}
#endif /* RESET_MINEFIELD */


#ifndef MINEFIELD_ALLOCATION
minefield* init_minefield()
{
	minefield* mf = calloc(1, sizeof(minefield));
	mf->width = 10;
	mf->height = 10;
	mf->cells = calloc(mf->width * mf->height, sizeof(uint8_t));

	return mf;
}


void free_minefield(minefield* mf)
{
	free(mf->cells);
	free(mf);
}
#endif /* MINEFIELD_ALLOCATION */


#ifndef RESET_MINEFIELD
void reset_minefield(minefield* mf)
{
    uint8_t num_bombs = random_number(10, 30);
    debug("num_bombs = ", num_bombs);
    fill_minefield(mf, num_bombs);
}
#endif /* RESET_MINEFIELD */


void open_cell(minefield* mf, uint8_t x, uint8_t y) {
	if (CELL(mf, x, y) & (HASQUESTIONMARK | HASFLAG | ISOPEN)){
		return;
	} else {
		CELL(mf, x, y) |= ISOPEN;
		if (CELL(mf, x, y) & HASBOMB){
			game_over(mf);
			return;
		}
	}

	if ((CELL(mf, x, y) & 0x0F) > 0)
		return;

	if (x-1 >= 0 && y-1 >= 0) open_cell(mf, x-1, y-1); // top-left
	if (y-1 >= 0) open_cell(mf, x, y-1); // top
	if (x+1 < mf->width && y-1 >= 0) open_cell(mf, x+1, y-1); // top-right

	if (x-1 >= 0) open_cell(mf, x-1, y); // left
	if (x+1 < mf->width) open_cell(mf, x+1, y); // right

	if (x-1 >= 0 && y+1 < mf->height) open_cell(mf, x-1, y+1); // bottom-left
	if (y+1 < mf->height) open_cell(mf, x, y+1); // bottom
	if (x+1 < mf->width && y+1 < mf->height) open_cell(mf, x+1, y+1); // bottom-right
}

