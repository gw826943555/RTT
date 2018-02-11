#include "gui.h"
#include "rtthread.h"
#include "GUIDEMO.h"
#include "drv_xpt2046.h"

void app_main(void* argu)
{
	GUI_Init();
	xpt2046_init("xpt2046", "spi2");
	while(1)
	{
		GUIDEMO_main();
	}
}

void app_main_init(void)
{
	rt_thread_t tid;
	tid = rt_thread_create("lcd",
													app_main,
													RT_NULL,
													2048,
													0,
													50);
	if(tid != RT_NULL)
	{
		rt_thread_startup(tid);
	}
}
