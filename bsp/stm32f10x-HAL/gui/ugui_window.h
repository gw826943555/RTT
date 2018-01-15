#ifndef __UGUI_WINDOW_H__
#define __UGUI_WINDOW_H__

#include "ugui_basic.h"

#define UGUI_MAX_WIDGETS											16
#define UGUI_WINDOW_DEFAULT_BACK_COLOR				0x0000

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
	changed,
	updated
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
typedef ugui_widget_t* ugui_widget_p;

typedef struct
{
	uint8_t widget_count;
	ugui_widget_p widget_list[16];
	ugui_state_t state;
	ugui_color fore_color;
	ugui_color back_color;
	int16_t pos_x;
	int16_t pos_y;
	uint16_t size_x;
	uint16_t size_y;
} ugui_window_t;
typedef ugui_window_t *ugui_window_p;

void ugui_window_set_size(ugui_window_p wnd, uint16_t size_x, uint16_t size_y);
void ugui_window_set_pos(ugui_window_p wnd, uint16_t pos_x, uint16_t pos_y);
void ugui_window_update(ugui_window_p wnd);
void ugui_widget_register(ugui_window_p wnd, ugui_widget_p widget);
void ugui_window_set_color(ugui_window_p wnd, uint16_t bc, uint16_t fc);

#endif

