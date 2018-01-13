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

typedef struct
{
   unsigned char* p;
   FONT_TYPE font_type;
   int16_t char_width;
   int16_t char_height;
   uint16_t start_char;
   uint16_t end_char;
   uint8_t  *widths;
} ugui_font_t;

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

typedef struct ugui_font* ugui_font_p;



#ifdef USE_FONT_4X6
extern const unsigned char font_4x6[256][6];
#endif

#ifdef USE_FONT_8X12
extern const unsigned char font_8x12[256][12];
#endif

#endif

