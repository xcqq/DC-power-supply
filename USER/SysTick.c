
#include "SysTick.h"

static __IO u32 TimingDelay;
static volatile uint32_t tick_ms;
extern unsigned long pulse_cnt; 
extern unsigned long encoder_speed; 
void SysTick_Init(void)
{
	/*10us one break*/
//	if (SysTick_Config(SystemFrequency / 100000))
	if (SysTick_Config(SystemCoreClock / 100000))
	{ 
		while (1);
	}
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}



void Delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}
void TimingDelay_Decrement(void)
{
	static volatile uint16_t tick_10us = 0;
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
	tick_10us++;
	if (tick_10us==100)
	{
		tick_ms++;
		tick_10us = 0;
	}
}

uint32_t SystickGetMs()
{
	return tick_ms;
}
