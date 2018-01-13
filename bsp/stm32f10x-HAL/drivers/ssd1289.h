#ifndef SSD1289_H_INCLUDED
#define SSD1289_H_INCLUDED

#include <rtthread.h>

#include "ugui_basic.h"

// Compatible list:
// ssd1289

/************************* SSD1289显示屏8080通讯引脚定义 *********************/
#define FSMC_LCD_CS_GPIO_ClK_ENABLE()  __HAL_RCC_GPIOG_CLK_ENABLE() 
#define FSMC_LCD_CS_PORT               GPIOG
#define FSMC_LCD_CS_PIN                GPIO_PIN_12

#define FSMC_LCD_DC_GPIO_ClK_ENABLE()  __HAL_RCC_GPIOF_CLK_ENABLE()
#define FSMC_LCD_DC_PORT               GPIOF
#define FSMC_LCD_DC_PIN                GPIO_PIN_0

#define FSMC_LCD_BK_GPIO_ClK_ENABLE()  __HAL_RCC_GPIOF_CLK_ENABLE()   
#define FSMC_LCD_BK_PORT               GPIOF
#define FSMC_LCD_BK_PIN                GPIO_PIN_10
 
#define LCD_BK_ON()                    HAL_GPIO_WritePin(FSMC_LCD_BK_PORT, FSMC_LCD_BK_PIN, GPIO_PIN_SET);
#define LCD_BK_OFF()                   HAL_GPIO_WritePin(FSMC_LCD_BK_PORT, FSMC_LCD_BK_PIN, GPIO_PIN_RESET);

/* LCD color */
#define White            0xFFFF
#define Black            0x0000
#define Grey             0xF7DE
#define Blue             0x001F
#define Blue2            0x051F
#define Red              0xF800
#define Magenta          0xF81F
#define Green            0x07E0
#define Cyan             0x7FFF
#define Yellow           0xFFE0

/*---------------------- Graphic LCD size definitions ------------------------*/
#define LCD_WIDTH       240                 /* Screen Width (in pixels)           */
#define LCD_HEIGHT      320                 /* Screen Hight (in pixels)           */
#define BPP             16                  /* Bits per pixel                     */
#define BYPP            ((BPP+7)/8)         /* Bytes per pixel                    */

extern struct ugui_graphic_ops ssd1289_graphic_ops;

void ssd1289_init(void);

void rt_hw_lcd_init(void);

void ssd1289_lcd_set_pixel(uint16_t pixel, uint16_t x, uint16_t y);

void ssd1289_lcd_get_pixel(uint16_t* pixel, uint16_t x, uint16_t y);

void ssd1289_lcd_draw_hline(const char* pixel, int x1, int x2, int y);

//#define _ILI_REVERSE_DIRECTION_

rt_size_t lcd_ssd1289_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size);
rt_size_t lcd_ssd1289_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size);

#endif // SSD1289_H_INCLUDED
