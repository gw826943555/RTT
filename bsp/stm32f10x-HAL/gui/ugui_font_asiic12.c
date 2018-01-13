#include "ugui_font_asiic12.h"
#include "ugui_basic.h"

static char ascii12_pixel[256][12] = 
{
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/
	{0x00,0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x00,0x20,0x00,0x00},/*"!",1*/
	{0x00,0x00,0x00,0x50,0x50,0x50,0x00,0x00,0x00,0x00,0x00,0x00},/*""",2*/
	{0x00,0x00,0x00,0x11,0x11,0xFF,0x22,0xFF,0x44,0x44,0x00,0x00},/*"#",3*/
	{0x00,0x00,0x00,0x3E,0x49,0x68,0x1C,0x0B,0x49,0x3E,0x08,0x00},/*"$",4*/
	{0x00,0x00,0x00,0xF0,0x90,0xF1,0x02,0x0C,0x10,0x20,0x00,0x00},/*"%",5*/
	{0x00,0x00,0x00,0x07,0x08,0x07,0x3A,0x42,0x61,0x3E,0x00,0x00},/*"&",6*/
	{0x00,0x00,0x00,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00},/*"'",7*/
	{0x00,0x00,0x00,0x0C,0x10,0x20,0x40,0x40,0x40,0x20,0x10,0x0C},/*"(",8*/
	{0x00,0x00,0x00,0xC0,0x20,0x10,0x08,0x08,0x08,0x10,0x20,0xC0},/*")",9*/
	{0x00,0x00,0x00,0x08,0x6B,0x7F,0x08,0x00,0x00,0x00,0x00,0x00},/*"*",10*/
	{0x00,0x00,0x00,0x00,0x08,0x08,0xFF,0x08,0x08,0x00,0x00,0x00},/*"+",11*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x20,0x00},/*",",12*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x00,0x00,0x00,0x00},/*"-",13*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00},/*".",14*/
	{0x00,0x00,0x00,0x08,0x10,0x10,0x20,0x40,0x40,0x80,0x00,0x00},/*"/",15*/
	{0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x22,0x1C,0x00,0x00},/*"0",16*/
	{0x00,0x00,0x00,0x38,0x08,0x08,0x08,0x08,0x08,0x1C,0x00,0x00},/*"1",17*/
	{0x00,0x00,0x00,0x3C,0x46,0x02,0x02,0x0C,0x11,0x7F,0x00,0x00},/*"2",18*/
	{0x00,0x00,0x00,0x3C,0x02,0x04,0x1C,0x02,0x02,0x7C,0x00,0x00},/*"3",19*/
	{0x00,0x00,0x00,0x1E,0x20,0x38,0x04,0x02,0x02,0x7C,0x00,0x00},/*"5",20*/
	{0x00,0x00,0x00,0x7E,0x82,0x04,0x04,0x08,0x08,0x10,0x00,0x00},/*"7",21*/
	{0x00,0x00,0x00,0x1C,0x63,0x62,0x1C,0x62,0x41,0x3E,0x00,0x00},/*"8",22*/
	{0x00,0x00,0x00,0x3E,0x43,0x41,0x61,0x3E,0x04,0x78,0x00,0x00},/*"9",23*/
	{0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00},/*":",24*/
	{0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x60,0x20,0x00},/*";",25*/
	{0x00,0x00,0x00,0x00,0x01,0x1E,0x60,0x1E,0x01,0x00,0x00,0x00},/*"<",26*/
	{0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0xFF,0x00,0x00,0x00,0x00},/*"=",27*/
	{0x00,0x00,0x00,0x00,0x60,0x1E,0x01,0x1E,0x60,0x00,0x00,0x00},/*">",28*/
	{0x00,0x00,0x00,0x78,0x44,0x08,0x10,0x10,0x00,0x10,0x00,0x00},/*"?",29*/
	{0x00,0x00,0x00,0x07,0x18,0x23,0x46,0x48,0x48,0x2F,0x18,0x07},/*"@",30*/
	{0x00,0x00,0x00,0x0C,0x0A,0x0A,0x11,0x1F,0x20,0xF0,0x00,0x00},/*"A",31*/
	{0x00,0x00,0x00,0xFF,0x20,0x20,0x3F,0x20,0x20,0xFF,0x00,0x00},/*"B",32*/
	{0x00,0x00,0x00,0x1F,0x20,0x40,0x40,0x40,0x20,0x1F,0x00,0x00},/*"C",33*/
	{0x00,0x00,0x00,0xFF,0x20,0x20,0x20,0x20,0x20,0xFF,0x00,0x00},/*"D",34*/
	{0x00,0x00,0x00,0xFF,0x20,0x22,0x3E,0x22,0x20,0xFF,0x00,0x00},/*"E",35*/
	{0x00,0x00,0x00,0xFF,0x20,0x22,0x3E,0x22,0x20,0xF8,0x00,0x00},/*"F",36*/
	{0x00,0x00,0x00,0x1F,0x20,0x40,0x41,0x40,0x30,0x1F,0x00,0x00},/*"G",37*/
	{0x00,0x00,0x00,0xF9,0x20,0x20,0x3F,0x20,0x20,0xF9,0x00,0x00},/*"H",38*/
	{0x00,0x00,0x00,0xF8,0x20,0x20,0x20,0x20,0x20,0xF8,0x00,0x00},/*"I",39*/
	{0x00,0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0xF0,0x00,0x00},/*"J",40*/
	{0x00,0x00,0x00,0xF9,0x21,0x2E,0x3C,0x23,0x20,0xF9,0x00,0x00},/*"K",41*/
	{0x00,0x00,0x00,0xF8,0x20,0x20,0x20,0x20,0x20,0xFF,0x00,0x00},/*"L",42*/
	{0x00,0x00,0x00,0xF0,0x38,0x28,0x24,0x22,0x23,0xF9,0x00,0x00},/*"M",43*/
	{0x00,0x00,0x00,0xE1,0x30,0x28,0x26,0x23,0x20,0xF8,0x00,0x00},/*"N",44*/
	{0x00,0x00,0x00,0x1F,0x20,0x40,0x40,0x40,0x20,0x1F,0x00,0x00},/*"O",45*/
	{0x00,0x00,0x00,0xFF,0x21,0x20,0x21,0x3F,0x20,0xF8,0x00,0x00},/*"P",46*/
	{0x00,0x00,0x00,0x1F,0x20,0x40,0x40,0x40,0x20,0x1F,0x03,0x00},/*"Q",47*/
	{0x00,0x00,0x00,0xFF,0x20,0x20,0x3F,0x22,0x21,0xF8,0x00,0x00},/*"R",48*/
	{0x00,0x00,0x00,0x3F,0x41,0x60,0x1E,0x03,0x41,0x7E,0x00,0x00},/*"S",49*/
	{0x00,0x00,0x00,0xFF,0x88,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},/*"T",50*/
	{0x00,0x00,0x00,0xF9,0x20,0x20,0x20,0x20,0x30,0x1F,0x00,0x00},/*"U",51*/
	{0x00,0x00,0x00,0xF1,0x60,0x20,0x11,0x11,0x0A,0x0C,0x00,0x00},/*"V",52*/
	{0x00,0x00,0x00,0xF3,0x21,0x21,0x21,0x11,0x12,0x0A,0x04,0x04},/*"W",53*/
	{0x00,0x00,0x00,0xF8,0x30,0x11,0x0E,0x06,0x19,0xF1,0x00,0x00},/*"X",54*/
	{0x00,0x00,0x00,0x79,0x11,0x0B,0x0A,0x04,0x04,0x1F,0x00,0x00},/*"Y",55*/
	{0x00,0x00,0x00,0x7F,0x41,0x06,0x08,0x10,0x60,0xFF,0x00,0x00},/*"Z",56*/
	{0x00,0x00,0x00,0x70,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x70},/*"[",57*/
	{0x00,0x00,0x00,0x80,0x40,0x40,0x20,0x10,0x10,0x08,0x00,0x00},/*"\",58*/
	{0x00,0x00,0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x70},/*"]",59*/
	{0x00,0x00,0x00,0x3C,0x42,0x81,0x00,0x00,0x00,0x00,0x00,0x00},/*"^",60*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},/*"_",61*/
	{0x00,0x00,0x00,0x40,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"`",62*/
	{0x00,0x00,0x00,0x00,0x00,0x7C,0x04,0x3C,0x44,0x7E,0x00,0x00},/*"a",63*/
	{0x00,0x00,0x00,0xC0,0x40,0x5C,0x62,0x42,0x46,0x3C,0x00,0x00},/*"b",64*/
	{0x00,0x00,0x00,0x00,0x00,0x3E,0x40,0x40,0x60,0x3E,0x00,0x00},/*"c",65*/
	{0x00,0x00,0x00,0x06,0x02,0x3A,0x46,0x42,0x62,0x3F,0x00,0x00},/*"d",66*/
	{0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x7E,0x40,0x3C,0x00,0x00},/*"e",67*/
	{0x00,0x00,0x00,0x1E,0x20,0x78,0x20,0x20,0x20,0x78,0x00,0x00},/*"f",68*/
	{0x00,0x00,0x00,0x00,0x00,0x3F,0x42,0x3C,0x40,0x7F,0x41,0x7E},/*"g",69*/
	{0x00,0x00,0x00,0xC0,0x40,0x5C,0x62,0x42,0x42,0xE7,0x00,0x00},/*"h",70*/
	{0x00,0x00,0x00,0x20,0x00,0x60,0x20,0x20,0x20,0x70,0x00,0x00},/*"i",71*/
	{0x00,0x00,0x00,0x20,0x00,0x60,0x20,0x20,0x20,0x20,0x20,0xC0},/*"j",72*/
	{0x00,0x00,0x00,0xC0,0x40,0x4E,0x58,0x70,0x4C,0xE7,0x00,0x00},/*"k",73*/
	{0x00,0x00,0x00,0x60,0x20,0x20,0x20,0x20,0x20,0x70,0x00,0x00},/*"l",74*/
	{0x00,0x00,0x00,0x00,0x00,0xDC,0x63,0x42,0x42,0xE7,0x00,0x00},/*"m",75*/
	{0x00,0x00,0x00,0x00,0x00,0xDC,0x62,0x42,0x42,0xE7,0x00,0x00},/*"n",76*/
	{0x00,0x00,0x00,0x00,0x00,0x3E,0x43,0x41,0x61,0x3E,0x00,0x00},/*"o",77*/
	{0x00,0x00,0x00,0x00,0x00,0xDC,0x66,0x42,0x42,0x7C,0x40,0xE0},/*"p",78*/
	{0x00,0x00,0x00,0x00,0x00,0x3E,0x42,0x42,0x62,0x1E,0x02,0x07},/*"q",79*/
	{0x00,0x00,0x00,0x00,0x00,0xDC,0x60,0x40,0x40,0xE0,0x00,0x00},/*"r",80*/
	{0x00,0x00,0x00,0x00,0x00,0x74,0x48,0x38,0x04,0x7C,0x00,0x00},/*"s",81*/
	{0x00,0x00,0x00,0x00,0x40,0xF0,0x40,0x40,0x40,0x78,0x00,0x00},/*"t",82*/
	{0x00,0x00,0x00,0x00,0x00,0xC6,0x42,0x42,0x42,0x7F,0x00,0x00},/*"u",83*/
	{0x00,0x00,0x00,0x00,0x00,0xEE,0x44,0x44,0x28,0x10,0x00,0x00},/*"v",84*/
	{0x00,0x00,0x00,0x00,0x00,0xEE,0x44,0x2A,0x2A,0x11,0x00,0x00},/*"w",85*/
	{0x00,0x00,0x00,0x00,0x00,0xEF,0x24,0x18,0x3C,0xE7,0x00,0x00},/*"x",86*/
	{0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x18,0x10,0x10,0xE0},/*"y",87*/
	{0x00,0x00,0x00,0x00,0x00,0x7E,0x4C,0x10,0x62,0xFE,0x00,0x00},/*"z",88*/
	{0x00,0x00,0x00,0x0C,0x10,0x10,0x10,0x60,0x10,0x10,0x10,0x0C},/*"{",89*/
	{0x00,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00},/*"|",90*/
	{0x00,0x00,0x00,0x30,0x08,0x08,0x08,0x06,0x08,0x08,0x08,0x30},/*"}",91*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x8F,0x00,0x00,0x00},/*"~",92*/
};

void ugui_font_asiic12_pixel(char* pixel,char c)
{
	pixel = ascii12_pixel[c];
}

void ugui_font_asiic12_put_char(char c, ugui_color color, int16_t pos_x, int16_t pos_y)
{
	int16_t x,y;
	for(y = 0;y < ugui_font_asiic12.size_y; y++)
	{
		for(x = 0;x < ugui_font_asiic12.size_x;x++)
		{
			if((ascii12_pixel[c-ugui_font_asiic12.offset][y] << x)&0x80)
				ugui_set_pixel(color, pos_x+x, pos_y+y);
		}
	}
}

struct ugui_font ugui_font_asiic12=
{
	8,
	12,
	256,
//	buffer,
	0x22,
	0,
	ugui_font_asiic12_pixel,
	ugui_font_asiic12_put_char
};



