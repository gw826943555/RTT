#include <rtthread.h>
#include <drivers/pin.h>

rt_base_t period = 0;									//CPU¿ÕÏĞÂÊ

void idle_thread(void)
{
	static rt_base_t _last_tick;
	period = rt_tick_get() - _last_tick;
	_last_tick = rt_tick_get();
}

rt_base_t rt_get_cpu_usage(void)
{
	return period / 10;
}

