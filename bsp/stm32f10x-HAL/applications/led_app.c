#include "led_app.h"
#include "idle_app.h"

#define LED_SYS				18
#define LED_CPU				22

void led_cpu_toggle(void* parameters)
{
	rt_pin_write(LED_CPU,!(_Bool)rt_pin_read(LED_CPU));
}

void led_thread(void* parameter)
{
	rt_base_t cpu_usage;
	rt_timer_t t_cpu_led;																	//注意：rt_timer_t 为指针类型
	t_cpu_led = rt_timer_create("t_cpu",
															led_cpu_toggle,
															RT_NULL,
															100,
															RT_TIMER_FLAG_PERIODIC);
	rt_timer_start(t_cpu_led);
	rt_pin_mode(LED_SYS,PIN_MODE_OUTPUT);
	rt_pin_mode(LED_CPU,PIN_MODE_OUTPUT);
	while(1)
	{
		rt_pin_write(LED_SYS,!(_Bool)rt_pin_read(LED_SYS));
		cpu_usage = (rt_get_cpu_usage() / 10 + 1) * 100;
		rt_timer_control(t_cpu_led, RT_TIMER_CTRL_SET_TIME, &cpu_usage);
//		rt_kprintf( "CPU Usage: %d %\n",rt_get_cpu_usage());
		rt_thread_delay(500);
	}
}

