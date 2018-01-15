#include "ugui_window.h"

void ugui_window_init(ugui_window_p wnd)
{
	wnd->back_color = UGUI_WINDOW_DEFAULT_BACK_COLOR;
	wnd->fore_color = 0xFFFF;
}

void ugui_window_set_size(ugui_window_p wnd, uint16_t size_x, uint16_t size_y)
{
	wnd->size_x = size_x;
	wnd->size_y = size_y;
	wnd->state = changed;
}

void ugui_window_set_pos(ugui_window_p wnd, uint16_t pos_x, uint16_t pos_y)
{
	wnd->pos_x = pos_x;
	wnd->pos_y = pos_y;
	wnd->state = changed;
}

void ugui_window_set_color(ugui_window_p wnd, uint16_t bc, uint16_t fc)
{
	wnd->back_color = bc;
	wnd->fore_color = fc;
	wnd->state = changed;
}

void ugui_window_update(ugui_window_p wnd)
{
	if((wnd->state == hide)||(wnd->state == updated)) return;
	
	ugui_fill_frame(wnd->back_color, wnd->pos_x, wnd->pos_y, 
									wnd->pos_x+wnd->size_x, wnd->pos_y+wnd->size_y);
	
	wnd->state = updated;
}

void ugui_widget_register(ugui_window_p wnd, ugui_widget_p widget)
{
	wnd->widget_list[wnd->widget_count++] = widget;
}

void ugui_widget_update(ugui_window_p wnd)
{
	for(uint16_t c=0; c<wnd->widget_count; c++)
	{
		switch(wnd->widget_list[c]->type)
		{
			case none:										;break;
			case button:									;break;
			case title:										;break;
			case textbox:									;break;
			case checkbox:								;break;
			default:											break;
		}
	}
}

