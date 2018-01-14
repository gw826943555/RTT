#include "font.h"
#include "ugui_font_ascii16.h"

struct ugui_font* ugui_get_font(uint16_t size)
{
	return &ugui_font_ascii16;
}