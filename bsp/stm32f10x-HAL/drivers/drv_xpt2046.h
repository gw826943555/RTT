#ifndef __DRV_XPT2046_H__
#define __DRV_XPT2046_H__

#include "rtthread.h"
#include <drivers/spi.h>

struct spi_device_xpt2046
{
	struct rt_device misc_device;
	struct rt_spi_device* rt_spi_device;
};

rt_err_t xpt2046_init(const char* misc_device_name, const char * spi_device_name);
#endif

