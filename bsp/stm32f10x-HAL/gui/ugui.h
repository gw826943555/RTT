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
#include "ugui_window.h"

#define			UGUI_MAX_WINDOWS								8

void ugui_update(void);
void ugui_register_window(ugui_window_p window);


#endif
