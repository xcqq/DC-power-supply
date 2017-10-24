
#include "include.h"
#include "gpio.h"

s_key_t key_list[] =
{
	{ KEY_ID_ENCODER, GPIO_ENCODER_PORT, GPIO_ENCODER_BUTTON },
	{ KEY_ID_END },
};

void GPIOButtonInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_BUTTON_ALL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_BUTTON_PORT, &GPIO_InitStructure);
}

void GPIOEncoderInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_ENCODER_ALL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_ENCODER_PORT, &GPIO_InitStructure);
}

void GPIOOledSWInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_OLED_ALL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_OLED_PORT, &GPIO_InitStructure);

	GPIO_SetBits(GPIO_OLED_PORT, GPIO_OLED_ALL);

}

void GPIOOledHWInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_OLED_MOSI | GPIO_OLED_CLK;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_OLED_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_OLED_CS | GPIO_OLED_DC;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_OLED_PORT, &GPIO_InitStructure);
}

void GPIOADCConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_ADC_ALL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIO_ADC_PORT, &GPIO_InitStructure);
}

int8_t KeyPressCheck(e_key_id_t key_id)
{
	uint8_t i = 0, key_result = 0;
	int8_t ret = 0;
	for (i = 0; i<KEY_ID_END; i++)
	{
		key_result = GPIO_GET(key_list->key_port, key_list->key_pin);
		if (key_list[i].key_state.private_state == key_state_release)
		{
			if (key_result == 0)
			{
				key_list[i].key_state.private_state = key_state_press;
				key_list[i].key_state.last_time = SystickGetMs();
			}
		}
		else if (key_list[i].key_state.private_state == key_state_press)
		{
			if (key_result == 1)
			{
				if ((SystickGetMs() - key_list[i].key_state.last_time > 10) && (SystickGetMs() - key_list[i].key_state.last_time < Is_ShortPress_Threshold))
				{
					key_list[i].key_state.state = key_short_press;
					key_list[i].key_state.private_state = key_state_release;
				}
				else if (SystickGetMs() - key_list[i].key_state.last_time > Is_ShortPress_Threshold)
				{
					key_list[i].key_state.state = key_long_press;
					key_list[i].key_state.private_state = key_state_release;
				}
				else
				{
					key_list[i].key_state.private_state = key_state_release;
				}
			}
		}
	}
	for (i = 0; i<KEY_ID_END; i++)
	{
		if (key_list->key_id==key_id)
		{
			ret = key_list->key_state.state;
			key_list->key_state.state = key_no_press;
			return ret;
		}
	}
	return -1;
}
