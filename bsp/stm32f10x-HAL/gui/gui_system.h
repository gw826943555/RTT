#ifndef __GUI_SYSTEM_H__
#define __GUI_SYSTEM_H__

#define GUI_DIR_VERTICAL 				0
#define GUI_DIR_HORIZONTAL			1
#define GUI_RES_X								240
#define GUI_RES_Y								320

typedef unsigned char gui_uint8;
typedef signed char gui_int8;
typedef unsigned short int gui_uint16;
typedef signed int gui_int16;
typedef unsigned int gui_uint32;
typedef signed int gui_int32;

void gui_init(void* argu);
void gui_set_pixel(gui_uint16 color, gui_uint16 x, gui_uint16 y);
gui_uint16 gui_get_pixel(gui_uint16 x, gui_uint16 y);

#endif


