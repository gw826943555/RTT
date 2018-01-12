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
*  @file     	uG_basic.c                                                     *
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

#include "uG_basic.h"

static uG_object_p uGui;

int8_t uG_init(uG_object_p object, void* argu)
{
	uGui = object;
	if(argu == 0)
	{
		return -1;
	}
	uGui->set_pixel = argu;
	return 0;
}

void uG_set_pixel(uint16_t color, uint16_t pos_x, uint16_t pos_y)
{
	uGui->set_pixel((const char*)(&color), pos_x, pos_y);
}
