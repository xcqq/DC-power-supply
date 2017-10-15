
#include "gui.h"
float volt_set = 0;
float current_set = 0; 
float volt_real = 0;
float current_real = 0;
static void GuiAddVoltSet()
{
	if(volt_set < VOLT_SET_MAX)
	{
		volt_set += 0.05;
	}
}
static void GuiMinusVoltSet()
{
	if(volt_set>0.00001)
	{
		volt_set -= 0.05;
	}
}
static void GuiAddCurrentSet()
{
	if(current_set < CURRENT_SET_MAX)
	{
		current_set += 0.05;
	}
}
static void GuiMinusCurrentSet()
{
	if(current_set > 0.00001)
	{
		current_set -= 0.05;
	}
}

void GuiPageOutput(float real_v, float real_i, float set_v, float set_i)
{
	static uint8_t state = 0;
	char buf[20];
	u8g2_SetDrawColor(&u8g2, 1);
	u8g2_DrawBox(&u8g2, 0, 0, 128, 10);
	u8g2_DrawBox(&u8g2, 0, 30, 128, 10);
	u8g2_SetFontMode(&u8g2, 0);
	u8g2_SetFont(&u8g2, u8g2_font_6x12_tf);
	u8g2_SetFontPosTop(&u8g2);
	u8g2_SetDrawColor(&u8g2, 0);
	u8g2_DrawStr(&u8g2, 55, 0, "real");
	u8g2_DrawStr(&u8g2, 58, 30, "set");
	u8g2_SetDrawColor(&u8g2, 1);
	u8g2_SetFont(&u8g2, u8g2_font_8x13_mf);
	sprintf(buf, "V:%05.2f", real_v);
	u8g2_DrawStr(&u8g2, 5, 13, buf);
	sprintf(buf, "I:%4.2f", real_i);
	u8g2_DrawStr(&u8g2, 68, 13, buf);
	sprintf(buf, "V:%05.2f", set_v);
	if(state == 0)
	{
		u8g2_SetDrawColor(&u8g2, 1); 
	}
	else if(state==1)
	{
		u8g2_SetDrawColor(&u8g2, 0); 
	}
	u8g2_DrawStr(&u8g2, 5, 43, buf);
	sprintf(buf, "I:%4.2f", set_i);
	if(state == 0)
	{
		u8g2_SetDrawColor(&u8g2, 0);
	}
	else if(state == 1)
	{
		u8g2_SetDrawColor(&u8g2, 1);
	}
	u8g2_DrawStr(&u8g2, 68, 43, buf);
	if(GPIO_GET(GPIO_ENCODER_PORT, GPIO_ENCODER_BUTTON) == 0)
	{
		while(GPIO_GET(GPIO_ENCODER_PORT, GPIO_ENCODER_BUTTON) == 0);
		if(state == 0)
		{
			state = 1;
			EncoderUnregistCallback();
			EncoderRegistCallback(GuiAddVoltSet, GuiMinusVoltSet);
		}
		else if(state == 1)
		{
			state = 0;
			EncoderUnregistCallback();
			EncoderRegistCallback(GuiAddCurrentSet, GuiMinusCurrentSet);
		}
	}
}
void GuiPageMenu()
{

}
void GuiPageCalibration()
{

}
