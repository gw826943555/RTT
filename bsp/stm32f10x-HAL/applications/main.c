/*
 * File      : main.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-07-29     Arda.Fu      first implementation
 */
#include <rtthread.h>
#include "led_app.h"
#include "idle_app.h"
#include "HMI_app.h"

int main(void)
{
	rt_thread_idle_sethook(idle_thread);
	
  /* user app entry */
	rt_thread_t tid1;
	tid1 = rt_thread_create("Led Thread",
													led_thread,
													RT_NULL,
													LED_THREAD_STACK_SIZE,
													LED_THREAD_PRIORITY,
													LED_THREAD_TIMESLICE);
	
	if(tid1 !=RT_NULL)
	{
		rt_thread_startup(tid1);
	}
	
	HMI_app_init();
	
  return 0;
}
