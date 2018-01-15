#ifndef __UGUI_WINDOW_H__
#define __UGUI_WINDOW_H__

#include "ugui_basic.h"

typedef enum
{
	none = 0,
	button,
	title,
	textbox,
	checkbox,
} ugui_widget_type_t;

typedef enum
{
	hide = 0,
	show,
} ugui_state_t;

typedef struct
{
	ugui_widget_type_t type;
	uint8_t id;
	ugui_state_t state;
	int16_t pos_x;
	int16_t pos_y;
	uint16_t size_x;
	uint16_t size_y;
} ugui_widget_t;
typedef struct ugui_widget_t* ugui_widget_p;

typedef struct
{
	uint8_t widget_count;
	ugui_widget_p widget_list;
	ugui_state_t state;
	ugui_color fore_color;
	ugui_color back_color;
	int16_t pos_x;
	int16_t pos_y;
	uint16_t size_x;
	uint16_t size_y;
} ugui_window_t;
typedef struct ugui_window_t *ugui_window_p;

#endif

