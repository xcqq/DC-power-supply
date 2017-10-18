#include "exti.h"

static encoder_callback encoder_up_callback;
static encoder_callback encoder_down_callback;
static unsigned long up_cnt = 0, down_cnt = 0;//for encoder pulse counter
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTIEncoderConfig(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;

	GPIOEncoderInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	NVIC_Configuration();

	GPIO_EXTILineConfig(EXTI_ENCODER_PORT, EXTI_ENCODER_PIN);
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure); 
}
void EXTI15_10_IRQHandler(void)
{
	static unsigned long last_time = 0;
	uint32_t diff_time = 0;
	static e_encoder_speed_t encoder_speed = ENCODER_SPEED_SLOW;
	if(EXTI_GetITStatus(EXTI_Line14) != RESET)
	{
		diff_time = SystickGetMs() - last_time;
		if(diff_time < ENCODER_THRESHOLD_FAST)
		{
			encoder_speed = ENCODER_SPEED_FAST;
		}
		else if(diff_time > ENCODER_THRESHOLD_SLOW)
		{
			encoder_speed = ENCODER_SPEED_SLOW;
		}
		else
		{
			encoder_speed = ENCODER_SPEED_NORMAL;
		}
		last_time = SystickGetMs();

		if(GPIO_GET(GPIO_ENCODER_PORT, GPIO_ENCODER_C))
		{
			up_cnt+=10;
			if(encoder_up_callback!=NULL)
			{
				encoder_up_callback(encoder_speed);
			}
		}
		else
		{
			down_cnt+=10;
			if(encoder_down_callback != NULL)
			{
				encoder_down_callback(encoder_speed);
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}
int EncoderGet()
{
	if(up_cnt > 0)
	{
		up_cnt--;
		return 1;
	}
	else if(down_cnt > 0)
	{
		down_cnt--;
		return -1;
	}
	return 0;
}

int EncoderRegistCallback(encoder_callback upCallback, encoder_callback downCallback)
{
	encoder_up_callback = upCallback;
	encoder_down_callback = downCallback;
	return 0;
}
int EncoderUnregistCallback()
{
	encoder_up_callback = NULL;
	encoder_down_callback = NULL;
	return 0;
}
