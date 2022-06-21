#ifndef VIDEO_TILES_H
#define VIDEO_TILES_H

#include <stdint.h>
#include "minefield.h"

void set_tile(uint8_t dst_x, uint8_t dst_y, uint8_t tile);
void draw_scenario();
void highlight_cell(minefield* mf, int x, int y);

enum {
	/*	NOTE:
		The tile codes for the number
		of bombs *MUST* be sequential
		because the video code assumes
		that to be the case.	*/
    ONE_BOMB,
    TWO_BOMBS,
    THREE_BOMBS,
    FOUR_BOMBS,
    FIVE_BOMBS,
    SIX_BOMBS,
    SEVEN_BOMBS,
    EIGHT_BOMBS,
    
    BLANK,
    CURSOR,
    BOMB,
    FLAG,
    QUESTION_MARK,
    EXPLOSION,
    GROUND,
    MINEFIELD_CORNER_TOP_LEFT,
    MINEFIELD_TOP_TEE,
    MINEFIELD_HORIZONTAL_TOP,
    MINEFIELD_CORNER_TOP_RIGHT,

    CORNER_TOP_LEFT,
    TOP_BORDER__LEFT,
    TOP_BORDER__RIGHT,
    CORNER_TOP_RIGHT,
    LEFT_BORDER__TOP,
    RIGHT_BORDER__TOP,
    LEFT_BORDER__BOTTOM,
    RIGHT_BORDER__BOTTOM,
    CORNER_BOTTOM_LEFT,
    BOTTOM_BORDER__LEFT,
    BOTTOM_BORDER__RIGHT,
    CORNER_BOTTOM_RIGHT,

    MINEFIELD_LEFT_TEE,
    MINEFIELD_CROSS,
    MINEFIELD_HORIZONTAL_MIDDLE,
    MINEFIELD_VERTICAL_MIDDLE,
    MINEFIELD_RIGHT_TEE,
    MINEFIELD_VERTICAL_LEFT,
    CLOSED_CELL,
    MINEFIELD_VERTICAL_RIGHT,
    MINEFIELD_CORNER_BOTTOM_LEFT,
    MINEFIELD_BOTTOM_TEE,
    MINEFIELD_HORIZONTAL_BOTTOM,
    MINEFIELD_CORNER_BOTTOM_RIGHT,

    /* Insert new tiles here */

    MAX_VIDEO_TILES,
};

#endif /* VIDEO_TILES_H */
