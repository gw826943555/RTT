#include "rtthread.h"
#include "./lvgl/lvgl.h"
#include "drv_ssd1289.h"
#include "./lvgl/lv_hal/lv_hal_disp.h"
void app_main(void* argu)
{
	lv_init();
	
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.disp_fill = lcd_disp_fill;
	disp_drv.disp_flush = lcd_disp_flush;
	disp_drv.disp_map = lcd_disp_map;
	lv_disp_drv_register(&disp_drv);          /*Register the driver in LittlevGL*/
	lcd_disp_fill(0, 0, 100, 100, LV_COLOR_WHITE);
//	ssd1289_lcd_set_pixel(0xffff, 200, 200);
//	/*Create a Label on the currently active screen*/
//	lv_obj_t * label1 =  lv_label_create(lv_scr_act(), NULL);

//	/*Modify the Label's text*/
//	lv_label_set_text(label1, "Hello world!");

//	/* Align the Label to the center
//	 * NULL means align on parent (which is the screen now)
//	 * 0, 0 at the end means an x, y offset after alignment*/
//	lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
	while(1)
	{
//		lv_task_handler();
		rt_thread_delay(10);
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
