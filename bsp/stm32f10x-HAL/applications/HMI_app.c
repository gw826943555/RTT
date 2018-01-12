#include "HMI_app.h"
#include "ssd1289.h"
#include "uG_basic.h"

void HMI_app(void* arg)
{
	rt_hw_lcd_init();
	rt_device_t lcd_device;
	lcd_device = rt_device_find("lcd");
	struct uG_object uGui;
	if(lcd_device != RT_NULL)
	{
		rt_device_open(lcd_device, RT_DEVICE_FLAG_RDWR);
		uG_init(&uGui, (void*)rt_graphix_ops(lcd_device));
	}
	uG_set_pixel(0xFFFF, 0, 0);
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


