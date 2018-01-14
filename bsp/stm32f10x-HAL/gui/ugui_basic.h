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
*  @file     	ugui_basic.h                                                   *
*  @brief    	This file is the head file of ugui_basic.c									   *
*						  							                                                 *
*  @author   	William Kwok                                                   *
*  @email    	gw826943555@qq.com                                             *
*  @version   0.0.1                                                          *
*  @date     	2018/01/12                                                     *
*  @license   GNU General Public License (GPL)                                *
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
#ifndef __UGUI_BASIC_H__
#define __UGUI_BASIC_H__
#include "stdint.h"
#include "color.h"
#include "font.h"

struct ugui_graphic_ops
{
    void (*set_pixel) (uint16_t , uint16_t , uint16_t );
    void (*get_pixel) (uint16_t *pixel, uint16_t x, uint16_t y);

    void (*draw_hline)(const char *pixel, int x1, int x2, int y);
    void (*draw_vline)(const char *pixel, int x, int y1, int y2);

    void (*blit_line) (const char *pixel, int x, int y, int size);
};
#define ugui_graphix_ops(device)          ((struct ugui_graphic_ops *)(device->user_data))

struct ugui_object
{
	uint16_t dim_x;
	uint16_t dim_y;
	
	uint16_t pos_x;
	uint16_t pos_y;
	
	uint16_t fore_color;
	uint16_t back_color;
	
	struct ugui_font* font;
	
	struct ugui_graphic_ops* ugui_ops;
};

typedef struct ugui_object* ugui_object_p;

int ugui_init(ugui_object_p object, struct ugui_graphic_ops* argu);
void ugui_set_pixel(ugui_color color, uint16_t pos_x, uint16_t pos_y);
uint16_t ugui_get_pixel(uint16_t pos_x, uint16_t pos_y);
int ugui_select_gui(ugui_object_p gui_p);
int ugui_select_font(const unsigned char* font);
void ugui_fill_screen(ugui_color color);
void ugui_fill_frame(ugui_color color, uint16_t pos_x1, uint16_t pos_y1, uint16_t pos_x2, uint16_t pos_y2);
void ugui_fill_round_frame(ugui_color color, uint16_t pos_x1, uint16_t pos_y1, uint16_t pos_x2, uint16_t pos_y2, uint16_t r);
void ugui_draw_line(ugui_color color, uint16_t pos_x1, uint16_t pos_y1, uint16_t pos_x2, uint16_t pos_y2);
void ugui_draw_arc(ugui_color color, uint16_t pos_x, uint16_t pos_y, uint16_t r, uint8_t sector);
void ugui_draw_circle(ugui_color color, uint16_t pos_x, uint16_t pos_y, uint16_t r);
void ugui_fill_circle(ugui_color color, uint16_t pos_x, uint16_t pos_y, uint16_t r);
void ugui_draw_mesh(ugui_color color, uint16_t pos_x1, uint16_t pos_y1, uint16_t pos_x2, uint16_t pos_y2);
void ugui_draw_frame(ugui_color color, int16_t pos_x1, int16_t pos_y1, int16_t pos_x2, int16_t pos_y2);
void ugui_draw_round_frame(ugui_color color, int16_t pos_x1, int16_t pos_y1, int16_t pos_x2, int16_t pos_y2, int16_t r);
void ugui_put_char(char c, ugui_color color,int16_t pos_x, int16_t pos_y);


#endif
