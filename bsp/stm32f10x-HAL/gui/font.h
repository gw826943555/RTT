#ifndef __FONT_H__
#define __FONT_H__

#include "gui_config.h"

#ifdef USE_FONT_4X6
extern __UG_FONT_DATA unsigned char font_4x6[256][6];
#endif

#ifdef USE_FONT_8X12
extern __UG_FONT_DATA unsigned char font_8x12[256][12];
#endif

#endif

