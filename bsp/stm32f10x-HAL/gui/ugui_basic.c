/*****************************************************************************
*  uGUI(Micro Graphic User Interface)                                        *
*  Copyright (C) 2014 William Kwok  gw826943555@qq.com                       *
*                                                                            *
*  This file is part of uGUI.                                                *
*                                                                            *
*  This program is free software; you can redistribute it and/or modify      *
*  it under the terms of the GNU General Public License version 3 as         *
*  published by the Free Software Foundation.                                *
*                                                                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*  @file     	ugui_basic.c                                                   *
*  @brief    	This file provides basic functions for the uGUI like init,     *
*						  set_pixel,etc.                                                 *
*  @author   	William Kwok                                                   *
*  @email    	gw826943555@qq.com                                             *
*  @version   0.0.1                                                          *
*  @date     	2018/01/12                                                     *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2018/01/12 | 0.0.1     | William        | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#include "ugui_basic.h"

static ugui_object_p ugui;

int ugui_init(ugui_object_p object, struct ugui_graphic_ops* argu)
{
	ugui = object;
	if(argu == 0)
	{
		return -1;
	}
//	ugui->font.p = font_8x12;
	ugui->ugui_ops = argu;
	ugui->font = ugui_get_font(16);
	return 0;
}

void ugui_set_pixel(ugui_color color, uint16_t pos_x, uint16_t pos_y)
{
	ugui->pos_x = pos_x;
	ugui->pos_y = pos_y;
	ugui->ugui_ops->set_pixel(color, pos_x, pos_y);
}

uint16_t ugui_get_pixel(uint16_t pos_x, uint16_t pos_y)
{
	uint16_t val;
	ugui->ugui_ops->get_pixel(&val, pos_x, pos_y);
	return val;
}

void ugui_fill_screen(ugui_color color)
{
	uint16_t x,y;
	for(y = 0;y < ugui->dim_y; y++)
	{
		for(x = 0; x < ugui->dim_x; x++)
		{
			ugui->ugui_ops->set_pixel(color, x, y);
		}
	}
}

void ugui_fill_frame(ugui_color color, uint16_t pos_x1, uint16_t pos_y1, uint16_t pos_x2, uint16_t pos_y2)
{
	uint16_t n,m;

	if ( pos_x2 < pos_x1 )
	{
		n = pos_x2;
		pos_x2 = pos_x1;
		pos_x1 = n;
	}
	if ( pos_y2 < pos_y1 )
	{
		n = pos_y2;
		pos_y2 = pos_y1;
		pos_y1 = n;
	}
	for( m = pos_y1; m <= pos_y2; m++ )
	{
		for( n = pos_x1; n <= pos_x2; n++ )
		{
			ugui->ugui_ops->set_pixel(color,n,m);
		}
	}
}

void ugui_fill_round_frame(ugui_color color, uint16_t pos_x1, uint16_t pos_y1, uint16_t pos_x2, uint16_t pos_y2, uint16_t r)
{
	int16_t n;
	if ( pos_x2 < pos_x1 )
	{
		n = pos_x2;
		pos_x2 = pos_x1;
		pos_x1 = n;
	}
	if ( pos_y2 < pos_y1 )
	{
		n = pos_y2;
		pos_y2 = pos_y1;
		pos_y1 = n;
	}

	if ( r > pos_x2 ) return;
	if ( r > pos_y2 ) return;

	ugui_draw_line(color, pos_x1+r, pos_y1, pos_x2-r, pos_y1);
	ugui_draw_line(color, pos_x1+r, pos_y2, pos_x2-r, pos_y2);
	ugui_draw_line(color, pos_x1, pos_y1+r, pos_x1, pos_y2-r);
	ugui_draw_line(color, pos_x2, pos_y1+r, pos_x2, pos_y2-r);
	ugui_draw_arc(color, pos_x1+r, pos_y1+r, r, 0x0C);
	ugui_draw_arc(color, pos_x2-r, pos_y1+r, r, 0x03);
	ugui_draw_arc(color, pos_x1+r, pos_y2-r, r, 0x30);
	ugui_draw_arc(color, pos_x2-r, pos_y2-r, r, 0xC0);
}

void ugui_draw_line(ugui_color color, uint16_t pos_x1, uint16_t pos_y1, uint16_t pos_x2, uint16_t pos_y2)
{
	uint16_t n, dx, dy, sgndx, sgndy, dxabs, dyabs, x, y, drawx, drawy;
	dx = pos_x2 - pos_x1;
	dy = pos_y2 - pos_y1;
	dxabs = (dx>0)?dx:-dx;
	dyabs = (dy>0)?dy:-dy;
	sgndx = (dx>0)?1:-1;
	sgndy = (dy>0)?1:-1;
	x = dyabs >> 1;
	y = dxabs >> 1;
	drawx = pos_x1;
	drawy = pos_y1;

	ugui->ugui_ops->set_pixel(color, drawx,drawy);

	if( dxabs >= dyabs )
	{
		for( n=0; n<dxabs; n++ )
		{
			y += dyabs;
			if( y >= dxabs )
			{
				y -= dxabs;
				drawy += sgndy;
			}
			drawx += sgndx;
			ugui->ugui_ops->set_pixel(color, drawx,drawy);
		}
	}
  else
  {
		for( n=0; n<dyabs; n++ )
		{
			 x += dxabs;
			 if( x >= dyabs )
			 {
					x -= dyabs;
					drawx += sgndx;
			 }
			 drawy += sgndy;
			 ugui->ugui_ops->set_pixel(color, drawx,drawy);
		}
  }
}

void ugui_draw_arc(ugui_color color, uint16_t pos_x, uint16_t pos_y, uint16_t r, uint8_t sector)
{
	int16_t x,y,xd,yd,e;

	xd = 1 - (r << 1);
	yd = 0;
	e = 0;
	x = r;
	y = 0;

	while ( x >= y )
	{
		// Q1
		if ( sector & 0x01 ) ugui->ugui_ops->set_pixel(color, pos_x + x, pos_y - y);
		if ( sector & 0x02 ) ugui->ugui_ops->set_pixel(color, pos_x + y, pos_y - x);

		// Q2
		if ( sector & 0x04 ) ugui->ugui_ops->set_pixel(color, pos_x - y, pos_y - x);
		if ( sector & 0x08 ) ugui->ugui_ops->set_pixel(color, pos_x - x, pos_y - y);

		// Q3
		if ( sector & 0x10 ) ugui->ugui_ops->set_pixel(color, pos_x - x, pos_y + y);
		if ( sector & 0x20 ) ugui->ugui_ops->set_pixel(color, pos_x - y, pos_y + x);

		// Q4
		if ( sector & 0x40 ) ugui->ugui_ops->set_pixel(color, pos_x + y, pos_y + x);
		if ( sector & 0x80 ) ugui->ugui_ops->set_pixel(color, pos_x + x, pos_y + y);

		y++;
		e += yd;
		yd += 2;
		if ( ((e << 1) + xd) > 0 )
		{
			x--;
			e += xd;
			xd += 2;
		}
	}
}

void ugui_draw_circle(ugui_color color, uint16_t pos_x, uint16_t pos_y, uint16_t r)
{
	int16_t x,y,xd,yd,e;

	xd = 1 - (r << 1);
	yd = 0;
	e = 0;
	x = r;
	y = 0;

	while ( x >= y )
	{
		ugui->ugui_ops->set_pixel(color, pos_x - x, pos_y + y);
		ugui->ugui_ops->set_pixel(color, pos_x - x, pos_y - y);
		ugui->ugui_ops->set_pixel(color, pos_x + x, pos_y + y);
		ugui->ugui_ops->set_pixel(color, pos_x + x, pos_y - y);
		ugui->ugui_ops->set_pixel(color, pos_x - y, pos_y + x);
		ugui->ugui_ops->set_pixel(color, pos_x - y, pos_y - x);
		ugui->ugui_ops->set_pixel(color, pos_x + y, pos_y + x);
		ugui->ugui_ops->set_pixel(color, pos_x + y, pos_y - x);

		y++;
		e += yd;
		yd += 2;
		if ( ((e << 1) + xd) > 0 )
		{
			 x--;
			 e += xd;
			 xd += 2;
		}
	}
}

void ugui_fill_circle(ugui_color color, uint16_t pos_x, uint16_t pos_y, uint16_t r)
{
	int16_t  x,y,xd;

	xd = 3 - (r << 1);
	x = 0;
	y = r;

	while ( x <= y )
	{
	 if( y > 0 )
	 {
			ugui_draw_line(color, pos_x - x, pos_y - y,pos_x - x, pos_y + y);
			ugui_draw_line(color, pos_x + x, pos_y - y,pos_x + x, pos_y + y);
	 }
	 if( x > 0 )
	 {
			ugui_draw_line(color, pos_x - y, pos_y - x,pos_x - y, pos_y + x);
			ugui_draw_line(color, pos_x + y, pos_y - x,pos_x + y, pos_y + x);
	 }
	 if ( xd < 0 )
	 {
			xd += (x << 2) + 6;
	 }
	 else
	 {
			xd += ((x - y) << 2) + 10;
			y--;
	 }
	 x++;
	}
	ugui_draw_circle(color, pos_x, pos_y, r);
}

void ugui_draw_mesh(ugui_color color, uint16_t pos_x1, uint16_t pos_y1, uint16_t pos_x2, uint16_t pos_y2)
{
	int16_t n,m;

	if ( pos_x2 < pos_x1 )
	{
		n = pos_x2;
		pos_x2 = pos_x1;
		pos_x1 = n;
	}
	if ( pos_y2 < pos_y1 )
	{
		n = pos_y2;
		pos_y2 = pos_y1;
		pos_y1 = n;
	}

	for( m=pos_y1; m<=pos_y2; m+=2 )
	{
		for( n=pos_x1; n<=pos_x2; n+=2 )
		{
			ugui->ugui_ops->set_pixel(color,n,m);
		}
	}
}

void ugui_put_char(char c, ugui_color color,int16_t pos_x, int16_t pos_y)
{
	ugui->font->ugui_put_char(c, color, pos_x, pos_y);
}
