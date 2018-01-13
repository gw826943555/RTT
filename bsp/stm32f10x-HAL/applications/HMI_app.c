#include "HMI_app.h"
#include "ssd1289.h"
#include "ugui_basic.h"
#include "ugui_font_ascii16.h"

void HMI_app(void* arg)
{
	rt_hw_lcd_init();
	rt_device_t lcd_device;
	lcd_device = rt_device_find("lcd");
	
	ugui_object_p ugui;
	ugui = rt_malloc(sizeof(struct ugui_object));
	ugui->dim_x = 240;
	ugui->dim_y = 320;
	if(lcd_device != RT_NULL)
	{
		rt_device_open(lcd_device, RT_DEVICE_FLAG_RDWR);
		ugui_init(ugui, &ssd1289_graphic_ops);
	}
	ugui_set_pixel(0x5555, 0, 0);
	ugui_draw_mesh(C_BLACK, 50, 50, 100, 100);
	ugui_font_ascii16_put_char('B',C_BLUE, 0, 0);
	while(1)
	{
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



