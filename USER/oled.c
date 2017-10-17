
#include "oled.h"
//#define OLED_HW_SPI
static uint8_t u8x8_gpio_and_delay(u8x8_t *u8g2, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	switch(msg)
	{
	case U8X8_MSG_GPIO_AND_DELAY_INIT:
#ifdef OLED_HW_SPI
		GPIOOledHWInit();
		SPIInit();
#else
		GPIOOledSWInit();
#endif
		
		break;

	case U8X8_MSG_DELAY_MILLI:
		Delay_us(1);
		break;

	case U8X8_MSG_GPIO_DC:
		GPIO_SET(GPIO_OLED_PORT, GPIO_OLED_DC, arg_int);
		break;

	case U8X8_MSG_GPIO_CS:
		GPIO_SET(GPIO_OLED_PORT, GPIO_OLED_CS, arg_int);
		break;

	case U8X8_MSG_GPIO_RESET:
		break;

	case U8X8_MSG_GPIO_D0:
		//GPIO_SET(GPIO_OLED_PORT, GPIO_OLED_MOSI, arg_int);
		GPIO_SET(GPIO_OLED_PORT, GPIO_OLED_CLK, arg_int);
		break;
	case U8X8_MSG_GPIO_D1:
		GPIO_SET(GPIO_OLED_PORT, GPIO_OLED_MOSI, arg_int);
		//GPIO_SET(GPIO_OLED_PORT, GPIO_OLED_CLK, arg_int);
		break;
	case U8X8_MSG_DELAY_NANO:
		break;
	case U8X8_MSG_GPIO_MENU_UP:
		if(EncoderGet() > 0)
		{
			u8g2->gpio_result = 0;
		}
		break;
	case U8X8_MSG_GPIO_MENU_DOWN:
		if(EncoderGet() < 0)
		{
			u8g2->gpio_result = 0;
		}
		break;
	case U8X8_MSG_GPIO_MENU_SELECT:
		if(GPIO_GET(GPIO_ENCODER_PORT, GPIO_ENCODER_BUTTON))
		{
			u8g2->gpio_result = 1;
		}
		else
		{
			u8g2->gpio_result = 0;
		}
		break;
	default:
		u8x8_SetGPIOResult(u8g2, 1);
		break;
	}
	return 1;

}

static uint8_t u8x8_byte_hw_spi(u8x8_t *u8g2, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	uint8_t *data;

	switch(msg)
	{
	case U8X8_MSG_BYTE_SEND:
		data = (uint8_t *)arg_ptr;
		SPISendBytes(data,arg_int);
		break;
	case U8X8_MSG_BYTE_INIT:
		u8x8_gpio_SetCS(u8g2, u8g2->display_info->chip_disable_level);
		break;
	case U8X8_MSG_BYTE_SET_DC:
		u8x8_gpio_SetDC(u8g2, arg_int);
		break;
	case U8X8_MSG_BYTE_START_TRANSFER:
		u8x8_gpio_SetCS(u8g2, u8g2->display_info->chip_enable_level);
		u8g2->gpio_and_delay_cb(u8g2, U8X8_MSG_DELAY_NANO, u8g2->display_info->post_chip_enable_wait_ns, NULL);
		break;
	case U8X8_MSG_BYTE_END_TRANSFER:
		u8g2->gpio_and_delay_cb(u8g2, U8X8_MSG_DELAY_NANO, u8g2->display_info->pre_chip_disable_wait_ns, NULL);
		u8x8_gpio_SetCS(u8g2, u8g2->display_info->chip_disable_level);
		break;
	default:
		return 0;
	}
	return 1;
}

void oledInit(u8g2_t *u8g2)
{
#ifdef OLED_HW_SPI
	u8g2_Setup_sh1106_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_hw_spi, u8x8_gpio_and_delay);
#else
	u8g2_Setup_sh1106_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_4wire_sw_spi, u8x8_gpio_and_delay); 
#endif
	u8g2_InitDisplay(u8g2);
	u8g2_SetPowerSave(u8g2, 0);
	u8g2_SetContrast(u8g2, 1);
	u8g2_ClearBuffer(u8g2);
}
