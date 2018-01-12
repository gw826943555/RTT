#include "gui_system.h"

struct gui_info
{
	gui_uint16 res_x;
	gui_uint16 rex_y;
	gui_uint8 dir;
};

struct gui_basic_ops
{
    void (*set_pixel) (const char *pixel, int x, int y);
    void (*get_pixel) (char *pixel, int x, int y);

    void (*draw_hline)(const char *pixel, int x1, int x2, int y);
    void (*draw_vline)(const char *pixel, int x, int y1, int y2);

    void (*blit_line) (const char *pixel, int x, int y, gui_uint32 size);
};

struct gui_basic_ops* gui_ops;

void gui_init(void* argu)
{
	if(0 != argu)
		gui_ops = (struct gui_basic_ops*) argu;
	else
		return;
}

void gui_set_pixel(gui_uint16 color, gui_uint16 x,gui_uint16 y)
{
	if(0 == gui_ops) return ;
	gui_ops->set_pixel((const char*)(&color), x, y);
}

gui_uint16 gui_get_pixel(gui_uint16 x, gui_uint16 y)
{
	if(0 == gui_ops) return 0;
	gui_uint16 temp = 0;
	gui_ops->get_pixel((char*)(&temp), x, y);
	return temp;
}

