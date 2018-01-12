#include "ssd1289.h"
// Compatible list:
// ssd1289

//内联函数定义,用以提高性能
#ifdef __CC_ARM                			 /* ARM Compiler 	*/
#define lcd_inline   				static __inline
#elif defined (__ICCARM__)        		/* for IAR Compiler */
#define lcd_inline 					inline
#elif defined (__GNUC__)        		/* GNU GCC Compiler */
#define lcd_inline 					static __inline
#else
#define lcd_inline                  static
#endif

#define rw_data_prepare()               write_cmd(34)


/********* control ***********/
#include "board.h"


//输出重定向.当不进行重定向时.
#define printf               rt_kprintf //使用rt_kprintf来输出
//#define printf(...)                       //无输出

/* LCD is connected to the FSMC_Bank1_NOR/SRAM2 and NE4 is used as ship select signal */
/* RS <==> F0 */
//TO DO...
#define LCD_REG              (*((volatile unsigned short *) 0x6C000000)) /* RS = 0 */
#define LCD_RAM              (*((volatile unsigned short *) 0x6C000002)) /* RS = 1 */
	
SRAM_HandleTypeDef lcd;

static void LCD_FSMCConfig(void)
{
	/* FSMC GPIO configure */
	{
		GPIO_InitTypeDef GPIO_InitStruct;	
		
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		__HAL_RCC_GPIOE_CLK_ENABLE();
		__HAL_RCC_GPIOF_CLK_ENABLE();
		__HAL_RCC_GPIOG_CLK_ENABLE();
		
		/** FSMC GPIO Configuration  
		PF0   ------> FSMC_A0
		PE7   ------> FSMC_D4
		PE8   ------> FSMC_D5
		PE9   ------> FSMC_D6
		PE10   ------> FSMC_D7
		PE11   ------> FSMC_D8
		PE12   ------> FSMC_D9
		PE13   ------> FSMC_D10
		PE14   ------> FSMC_D11
		PE15   ------> FSMC_D12
		PD8   ------> FSMC_D13
		PD9   ------> FSMC_D14
		PD10   ------> FSMC_D15
		PD14   ------> FSMC_D0
		PD15   ------> FSMC_D1
		PD0   ------> FSMC_D2
		PD1   ------> FSMC_D3
		PD4   ------> FSMC_NOE
		PD5   ------> FSMC_NWE
		PG12   ------> FSMC_NE4
		*/
		
		GPIO_InitStruct.Pin = FSMC_LCD_DC_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(FSMC_LCD_DC_PORT, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = FSMC_LCD_CS_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(FSMC_LCD_CS_PORT, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
												|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
												|GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_14 
												|GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4 
												|GPIO_PIN_5;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		//TO:DO
		/* 输出低电平：背光不亮 */
//			HAL_GPIO_WritePin(FSMC_LCD_BK_PORT, FSMC_LCD_BK_PIN, GPIO_PIN_SET);

//			/* 液晶背光控制引脚初始化 */
//			GPIO_InitStruct.Pin = FSMC_LCD_BK_PIN;
//			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//			HAL_GPIO_Init(FSMC_LCD_BK_PORT, &GPIO_InitStruct);
	}
	{
		__HAL_RCC_FSMC_CLK_ENABLE();
		
		FSMC_NORSRAM_TimingTypeDef Timing;

		/* 配置FSMC参数 */
		lcd.Instance = FSMC_NORSRAM_DEVICE;
		lcd.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;

		lcd.Init.NSBank = FSMC_NORSRAM_BANK4;
		lcd.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
		lcd.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
		lcd.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
		lcd.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
		lcd.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
		lcd.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
		lcd.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
		lcd.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
		lcd.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
		lcd.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
		lcd.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
		lcd.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;

		Timing.AddressSetupTime      = 0x02; //地址建立时间
		Timing.AddressHoldTime       = 0x00; //地址保持时间
		Timing.DataSetupTime         = 0x01; //数据建立时间
		Timing.BusTurnAroundDuration = 0x00;
		Timing.CLKDivision           = 0x00;
		Timing.DataLatency           = 0x00;
		Timing.AccessMode = FSMC_ACCESS_MODE_A;
		HAL_SRAM_Init(&lcd, &Timing, &Timing);

		/* Disconnect NADV */
		__HAL_AFIO_FSMCNADV_DISCONNECTED();
	}
}

//static void delay(int cnt)
//{
//    volatile unsigned int dl;
//    while(cnt--)
//    {
//        for(dl=0; dl<500; dl++);
//    }
//}

static void lcd_port_init(void)
{
    LCD_FSMCConfig();
}

lcd_inline void write_cmd(unsigned short cmd)
{
    LCD_REG = cmd;
}

lcd_inline unsigned short read_data(void)
{
    return LCD_RAM;
}

lcd_inline void write_data(unsigned short data_code )
{
    LCD_RAM = data_code;
}

lcd_inline void write_reg(unsigned char reg_addr,unsigned short reg_val)
{
    write_cmd(reg_addr);
    write_data(reg_val);
}

lcd_inline unsigned short read_reg(unsigned char reg_addr)
{
    unsigned short val=0;
    write_cmd(reg_addr);
    val = read_data();
    return (val);
}

/********* control <只移植以上函数即可> ***********/

static unsigned short deviceid=0;//设置一个静态变量用来保存LCD的ID

//static unsigned short BGR2RGB(unsigned short c)
//{
//    u16  r, g, b, rgb;
//
//    b = (c>>0)  & 0x1f;
//    g = (c>>5)  & 0x3f;
//    r = (c>>11) & 0x1f;
//
//    rgb =  (b<<11) + (g<<5) + (r<<0);
//
//    return( rgb );
//}

static void lcd_SetCursor(unsigned int x,unsigned int y)
{
    write_reg(0x004e,x);    /* 0-239 */
    write_reg(0x004f,y);    /* 0-319 */
}

/* 读取指定地址的GRAM */
static unsigned short lcd_read_gram(unsigned int x,unsigned int y)
{
    unsigned short temp;
    lcd_SetCursor(x,y);
    rw_data_prepare();
    /* dummy read */
    temp = read_data();
    temp = read_data();
    return temp;
}

static void lcd_clear(unsigned short Color)
{
    unsigned int index=0;
    lcd_SetCursor(0,0);
    rw_data_prepare();                      /* Prepare to write GRAM */
    for (index=0; index<(LCD_WIDTH*LCD_HEIGHT); index++)
    {
        write_data(Color);
    }
}

static void lcd_data_bus_test(void)
{
    unsigned short temp1;
    unsigned short temp2;
//    /* [5:4]-ID~ID0 [3]-AM-1垂直-0水平 */
//    write_reg(0x0003,(1<<12)|(1<<5)|(1<<4) | (0<<3) );

    /* wirte */
    lcd_SetCursor(0,0);
    rw_data_prepare();
    write_data(0x5555);

    lcd_SetCursor(1,0);
    rw_data_prepare();
    write_data(0xAAAA);

    /* read */
    lcd_SetCursor(0,0);
    temp1 = lcd_read_gram(0,0);
    temp2 = lcd_read_gram(1,0);

    if( (temp1 == 0x5555) && (temp2 == 0xAAAA) )
    {
        printf(" data bus test pass!\r\n");
    }
    else
    {
        printf(" data bus test error: %04X %04X\r\n",temp1,temp2);
    }
}

void ssd1289_init(void)
{
    lcd_port_init();
    deviceid = read_reg(0x00);

    /* deviceid check */
    if( deviceid != 0x8999 )
    {
        printf("Invalid LCD ID:%08X\r\n",deviceid);
        printf("Please check you hardware and configure.\r\n");
    }
    else
    {
        printf("\r\nLCD Device ID : %04X ",deviceid);
    }

    //************* Start Initial Sequence **********//
		write_reg(0x00, 0x0001); // Start internal OSC.
		write_reg(0x01, 0x3B3F); // Driver output control, RL=1;REV=1;GD=1;BGR=0;SM=0;TB=0
		write_reg(0x02, 0x0600); // set 1 line inversion
		//************* Power control setup ************/
		write_reg(0x0C, 0x0007); // Adjust VCIX2 output voltage
		write_reg(0x0D, 0x0006); // Set amplitude magnification of VLCD63
		write_reg(0x0E, 0x3200); // Set alternating amplitude of VCOM
		write_reg(0x1E, 0x00BB); // Set VcomH voltage
		write_reg(0x03, 0x6A64); // Step-up factor/cycle setting
		//************ RAM position control **********/
		write_reg(0x0F, 0x0000); // Gate scan position start at G0.
		write_reg(0x44, 0xEF00); // Horizontal RAM address position
		write_reg(0x45, 0x0000); // Vertical RAM address start position
		write_reg(0x46, 0x013F); // Vertical RAM address end position
		// ----------- Adjust the Gamma Curve ----------//
		write_reg(0x30, 0x0000);
		write_reg(0x31, 0x0706);
		write_reg(0x32, 0x0206);
		write_reg(0x33, 0x0300);
		write_reg(0x34, 0x0002);
		write_reg(0x35, 0x0000);
		write_reg(0x36, 0x0707);
		write_reg(0x37, 0x0200);
		write_reg(0x3A, 0x0908);
		write_reg(0x3B, 0x0F0D);
		//************* Special command **************/
		write_reg(0x28, 0x0006); // Enable test command
		write_reg(0x2F, 0x12EB); // RAM speed tuning
		write_reg(0x26, 0x7000); // Internal Bandgap strength
		write_reg(0x20, 0xB0E3); // Internal Vcom strength
		write_reg(0x27, 0x0044); // Internal Vcomh/VcomL timing
		write_reg(0x2E, 0x7E45); // VCOM charge sharing time  
		//************* Turn On display ******************/
		write_reg(0x10, 0x0000); // Sleep mode off.
//		delay(30); // Wait 30mS
		write_reg(0x11, 0x6870); // Entry mode setup. 262K type B, take care on the data bus with 16it only
		write_reg(0x07, 0x0033); // Display ON	*/

    //数据总线测试,用于测试硬件连接是否正常.
    lcd_data_bus_test();
    //GRAM测试,此测试可以测试LCD控制器内部GRAM.测试通过保证硬件正常
//    lcd_gram_test();

    //清屏
    lcd_clear( Red );
}

/*  设置像素点 颜色,X,Y */
void ssd1289_lcd_set_pixel(const char* pixel, int x, int y)
{
    lcd_SetCursor(x,y);

    rw_data_prepare();
    write_data(*(rt_uint16_t*)pixel);
}

/* 获取像素点颜色 */
void ssd1289_lcd_get_pixel(char* pixel, int x, int y)
{
	*(rt_uint16_t*)pixel = lcd_read_gram(x, y);
}

/* 画水平线 */
void ssd1289_lcd_draw_hline(const char* pixel, int x1, int x2, int y)
{
    /* [5:4]-ID~ID0 [3]-AM-1垂直-0水平 */
    write_reg(0x0011,0x6030 | (0<<3)); // AM=0 hline

    lcd_SetCursor(x1, y);
    rw_data_prepare(); /* Prepare to write GRAM */
    while (x1 < x2)
    {
        write_data(*(rt_uint16_t*)pixel);
        x1++;
    }
}

/* 垂直线 */
void ssd1289_lcd_draw_vline(const char* pixel, int x, int y1, int y2)
{
    /* [5:4]-ID~ID0 [3]-AM-1垂直-0水平 */
    write_reg(0x0011,0x6070 | (1<<3)); // AM=0 vline

    lcd_SetCursor(x, y1);
    rw_data_prepare(); /* Prepare to write GRAM */
    while (y1 < y2)
    {
        write_data(*(rt_uint16_t*)pixel);
        y1++;
    }
}

/* blit a line */
void ssd1289_lcd_blit_line(const char* pixels, int x, int y, rt_size_t size)
{
	rt_uint16_t *ptr;

	ptr = (rt_uint16_t*)pixels;

    /* [5:4]-ID~ID0 [3]-AM-1垂直-0水平 */
    write_reg(0x0011,0x6070 | (0<<3)); // AM=0 hline

    lcd_SetCursor(x, y);
    rw_data_prepare(); /* Prepare to write GRAM */
    while (size)
    {
        write_data(*ptr ++);
		size --;
    }
}

struct rt_device_graphic_ops ssd1289_ops =
{
	ssd1289_lcd_set_pixel,
	ssd1289_lcd_get_pixel,
	ssd1289_lcd_draw_hline,
	ssd1289_lcd_draw_vline,
	ssd1289_lcd_blit_line
};

struct rt_device _lcd_device;
static rt_err_t lcd_init(rt_device_t dev)
{
	return RT_EOK;
}

static rt_err_t lcd_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t lcd_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_err_t lcd_control(rt_device_t dev, int cmd, void *args)
{
	switch (cmd)
	{
	case RTGRAPHIC_CTRL_GET_INFO:
		{
			struct rt_device_graphic_info *info;

			info = (struct rt_device_graphic_info*) args;
			RT_ASSERT(info != RT_NULL);

			info->bits_per_pixel = 16;
			info->pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565P;
			info->framebuffer = RT_NULL;
			info->width = 240;
			info->height = 320;
		}
		break;

	case RTGRAPHIC_CTRL_RECT_UPDATE:
		/* nothong to be done */
		break;

	default:
		break;
	}

	return RT_EOK;
}

void rt_hw_lcd_init(void)
{
	/* register lcd device */
	_lcd_device.type  = RT_Device_Class_Graphic;
	_lcd_device.init  = lcd_init;
	_lcd_device.open  = lcd_open;
	_lcd_device.close = lcd_close;
	_lcd_device.control = lcd_control;
	_lcd_device.read  = RT_NULL;
	_lcd_device.write = RT_NULL;

	_lcd_device.user_data = &ssd1289_ops;
    ssd1289_init();

    /* register graphic device driver */
	rt_device_register(&_lcd_device, "lcd",
		RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
}

