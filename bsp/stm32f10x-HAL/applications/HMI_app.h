#ifndef __HMI_APP_H__
#define __HMI_APP_H__
#include "rtthread.h"

#define HMI_APP_STACK_SIZE 		4096
#define HMI_APP_PRIORITY			30
#define HMI_APP_TICK					500

void HMI_app_init(void);

#endif

