#ifndef __UGUI_FONT_ASIIC12_H__
#define __UGUI_FONT_ASIIC12_H__
#include "font.h"

#define UGUI_FONT_ASIIC12_BUFFER_SIZE				(12*8)

extern struct ugui_font ugui_font_asiic12;

void ugui_font_asiic12_put_char(char c, ugui_color color, int16_t pos_x, int16_t pos_y);
#endif

