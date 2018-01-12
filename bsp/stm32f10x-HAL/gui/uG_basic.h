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
*  @file     	uG_basic.h                                                     *
*  @brief    	This file is the head file of uG_basic.c									     *
*						  							                                                 *
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
#ifndef __UG_BASIC_H__
#define __UG_BASIC_H__
#include "stdint.h"

struct uG_object
{
	uint16_t dim_x;
	uint16_t dim_y;
	
	uint16_t pos_x;
	uint16_t pos_y;
	
	uint16_t fore_color;
	uint16_t back_color;
	
	void (*set_pixel) (const char *pixel, int x, int y);
};

typedef struct uG_object* uG_object_p;

int8_t uG_init(uG_object_p object, void* argu);
void uG_set_pixel(uint16_t color, uint16_t pos_x, uint16_t pos_y);

#endif
