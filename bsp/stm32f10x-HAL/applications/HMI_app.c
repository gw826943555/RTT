#include "HMI_app.h"
#include "ssd1289.h"
#include "gui_system.h"
#include "gui.h"

void HMI_app(void* arg)
{
	rt_hw_lcd_init();
	rt_device_t lcd;
	lcd = rt_device_find("lcd");
	if(lcd != RT_NULL)
	{
		rt_device_open(lcd, RT_DEVICE_FLAG_RDWR);
		UG_GUI _gui;
		_gui.x_dim = 240;
		_gui.y_dim = 320;
	}
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


