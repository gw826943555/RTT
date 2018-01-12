#ifndef __IDLE_APP_H__
#define __IDLE_APP_H__

#include "rtthread.h"

void idle_thread(void);
rt_base_t rt_get_cpu_usage(void);

#endif
