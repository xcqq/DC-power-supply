#include "include.h"
u8g2_t u8g2;
int main(void)
{
    SysTick_Init();
	EXTIEncoderConfig();
    oledInit(&u8g2);
    u8g2_SetFontMode(&u8g2,1);
    u8g2_SetFontDirection(&u8g2,0);
    u8g2_SetFont(&u8g2, u8g2_font_6x12_tf);
    u8g2_SetFontPosTop(&u8g2);
    u8g2_DrawStr(&u8g2, 0, 0, "hello world");
    u8g2_SendBuffer(&u8g2);
    while(1)
    {
		if(u8g2_UserInterfaceSelectionList(&u8g2, "Select Mode", 0, "Basic CC Mode\nBattery Mode\nCelebration") > 0)
		{
			u8g2_DrawStr(&u8g2, 0, 12, "button pressed"); 
		}
		u8g2_SendBuffer(&u8g2);
    }
}


