#include "ugui.h"

static struct 
{
	ugui_window_p obj[UGUI_MAX_WINDOWS];
	uint8_t count;
} ugui_container;

void ugui_window_update(ugui_window_p window)
{
}

void ugui_update()
{
	for(uint8_t i=0;i < ugui_container.count;++i)
	{
		ugui_window_update(ugui_container.obj[i]);
	}
}

void ugui_window_register(ugui_window_p window)
{
	if(ugui_container.count <UGUI_MAX_WINDOWS)
	{
		ugui_container.obj[ugui_container.count] = window;
		++ugui_container.count;
	}
}
