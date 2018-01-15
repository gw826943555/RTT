#include "HMI_app.h"
#include "ssd1289.h"
#include "ugui_basic.h"
#include "ugui_font_ascii16.h"
#include "font_chs12.h"
#include "ugui.h"

void HMI_app(void* arg)
{
	rt_hw_lcd_init();
	rt_device_t lcd_device;
	lcd_device = rt_device_find("lcd");
	
	ugui_object_p ugui;
	ugui = rt_malloc(sizeof(struct ugui_object));
	ugui->dim_x = 129;
	ugui->dim_y = 65;
	if(lcd_device != RT_NULL)
	{
		rt_device_open(lcd_device, RT_DEVICE_FLAG_RDWR);
		ugui_init(ugui, &ssd1289_graphic_ops);
	}
	
	ugui_fill_screen(Black);
	ugui_draw_line(C_WHITE, 128, 0, 128, 64);
	ugui_draw_line(C_WHITE, 0, 64, 128, 64);
	
	ugui_window_t windows;
	
	ugui_window_set_pos(&windows, 0, 0);
	ugui_window_set_size(&windows, 128, 64);
	ugui_window_set_color(&windows, C_WHITE, C_WHITE);
	
	ugui_WM_init();
	ugui_register_window(&windows);

	while(1)
	{
		ugui_update();
		rt_thread_delay(20);
	}
}

void HMI_app_init(void)
{
	rt_thread_t tid;
	tid = rt_thread_create("HMI_thread",
													HMI_app,
													RT_NULL,
													HMI_APP_STACK_SIZE,
													HMI_APP_PRIORITY,
													HMI_APP_TICK);
	if( RT_NULL != tid)
	{
		rt_thread_startup(tid);
	}
}



