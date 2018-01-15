#include "font_chs12.h"

const uint8_t chs12[12][24];

void ugui_show_chs(uint16_t chs_num, uint16_t color, uint16_t pos_x, uint16_t pos_y)
{
	for(uint16_t y = 0; y < 12; y++)
	{
		for(uint16_t x = 0;x <12; x++)
		{
			if(x < 8)
			{
				if(chs12[chs_num][2*y] & (0x80>>x))
				{
					ugui_set_pixel(color, pos_x + x, pos_y + y);
				}
			}else
			{
				if(chs12[chs_num][2*y+1] & (0x80>>(x-8)))
				{
					ugui_set_pixel(color, pos_x + x, pos_y + y);
				}
			}
		}
	}
}

const uint8_t chs12[12][24]=
{
	{0x11,0x00,0x11,0x00,0x2F,0xC0,0x22,0x00,0x62,0x00,0xBF,0xE0,0x24,0x00,0x27,0xC0,0x20,0x40,0x26,0x80,0x21,0x80,0x20,0x40},/*"��",0*/
	{0x01,0x40,0x7F,0xE0,0x41,0x00,0x5D,0x40,0x41,0x40,0x5C,0x80,0x54,0xA0,0x5D,0x60,0x82,0x20,0x54,0x40,0x52,0xA0,0x8F,0xA0},/*"��",1*/
	{0x7B,0xC0,0x4A,0x40,0x7B,0xC0,0x04,0x80,0x04,0x40,0xFF,0xE0,0x0A,0x00,0x31,0x80,0xC0,0x60,0x7B,0xC0,0x4A,0x40,0x7B,0xC0},/*"��",2*/
	{0x00,0x20,0xBE,0x20,0x62,0xA0,0x2A,0xA0,0x2A,0xA0,0xAA,0xA0,0x6A,0xA0,0x2A,0xA0,0x2A,0xA0,0x48,0x20,0x94,0x20,0x22,0x60},/*"��",3*/
	{0x80,0xA0,0x40,0x80,0x0F,0xE0,0x00,0x80,0xC0,0x80,0x4E,0x80,0x44,0x80,0x44,0x80,0x44,0x80,0x46,0xA0,0x6C,0x60,0x40,0x20},/*"��",4*/
};