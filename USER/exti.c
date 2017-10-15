#include "exti.h"
static void (*encoder_up_callback)();
static void (*encoder_down_callback)();
static unsigned char up_cnt = 0, down_cnt = 0;//for encoder pulse counter
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
	if(EXTI_GetITStatus(EXTI_Line14) != RESET)
	{
		
		if(GPIO_GET(GPIO_ENCODER_PORT, GPIO_ENCODER_C))
		{
			up_cnt+=10;
			if(encoder_up_callback!=NULL)
			{
				encoder_up_callback();
			}
		}
		else
		{
			down_cnt+=10;
			if(encoder_down_callback != NULL)
			{
				encoder_down_callback();
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

int EncoderRegistCallback(void (*upCallback)(),void (*downCallback)())
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
