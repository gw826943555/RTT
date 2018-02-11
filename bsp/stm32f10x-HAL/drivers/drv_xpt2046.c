#include "drv_xpt2046.h"
#include "drv_spi.h"


rt_err_t xpt2046_init(const char* misc_device_name, const char * spi_device_name)
{
	return stm32_spi_bus_attach_device(73, spi_device_name, misc_device_name);
}