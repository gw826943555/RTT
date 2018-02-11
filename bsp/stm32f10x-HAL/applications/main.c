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
#include "app_main.h"

int main(void)
{
	rt_thread_idle_sethook(idle_thread);
	
  /* user app entry */
	app_led_init(RT_NULL);
	app_main_init();
  return 0;
}
