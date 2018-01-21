#ifndef __LED_APP_H__
#define __LED_APP_H__

#include <rtthread.h>
#include <drivers/pin.h>

#define LED_THREAD_PRIORITY 10
#define LED_THREAD_STACK_SIZE 1024
#define LED_THREAD_TIMESLICE 10

void app_led_init(void* argu);

#endif



