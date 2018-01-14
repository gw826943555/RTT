#ifndef __FONT_H__
#define __FONT_H__

#include "stdint.h"
#include "color.h"
#define USE_FONT_8X12

typedef enum
{
	FONT_TYPE_1BPP,
	FONT_TYPE_8BPP
} FONT_TYPE;

struct ugui_font
{
	uint16_t size_x;
	uint16_t size_y;
	uint16_t num;
	uint16_t offset;
//	uint16_t* buffer;
	
	void (*init)();
	void (*ugui_get_font_pixel)(char*, char);
	void (*ugui_put_char)(char , ugui_color , int16_t , int16_t);
};

struct ugui_font* ugui_get_font(uint16_t size);

typedef struct ugui_font* ugui_font_p;


#endif

