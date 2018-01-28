#include "gui.h"
#include "rtthread.h"
#include "GUIDEMO.h"

void app_main(void* argu)
{
	GUI_Init();
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
