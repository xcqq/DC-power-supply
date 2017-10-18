
#include "gui.h"
float volt_set = 0;
float current_set = 0; 
float volt_real = 0;
float current_real = 0;
static void GuiAddVoltSet(e_encoder_speed_t speed)
{

	switch(speed)
	{
	case ENCODER_SPEED_FAST:
		volt_set += VOLT_SET_FAST_STEP;
		break;
	case ENCODER_SPEED_NORMAL:
		volt_set += VOLT_SET_NORMAL_STEP;
		break;
	case ENCODER_SPEED_SLOW:
		volt_set += VOLT_SET_SLOW_STEP;
		break;
	}
	if(volt_set > VOLT_SET_MAX)
	{
		volt_set = VOLT_SET_MAX;
	}
}
static void GuiMinusVoltSet(e_encoder_speed_t speed)
{

	switch(speed)
	{
	case ENCODER_SPEED_FAST:
		volt_set -= VOLT_SET_FAST_STEP;
		break;
	case ENCODER_SPEED_NORMAL:
		volt_set -= VOLT_SET_NORMAL_STEP;
		break;
	case ENCODER_SPEED_SLOW:
		volt_set -= VOLT_SET_SLOW_STEP;
		break;
	}
	if(volt_set<0)
	{
		volt_set = 0;
	}
}
static void GuiAddCurrentSet(e_encoder_speed_t speed)
{
	switch(speed)
	{
	case ENCODER_SPEED_FAST:
		current_set += CURRENT_SET_FAST_STEP;
		break;
	case ENCODER_SPEED_NORMAL:
		current_set += CURRENT_SET_NORMAL_STEP;
		break;
	case ENCODER_SPEED_SLOW:
		current_set += CURRENT_SET_SLOW_STEP;
		break;
	}
	if(current_set > CURRENT_SET_MAX)
	{
		current_set = CURRENT_SET_MAX;
	}
}
static void GuiMinusCurrentSet(e_encoder_speed_t speed)
{
	switch(speed)
	{
	case ENCODER_SPEED_FAST:
		current_set -= CURRENT_SET_FAST_STEP;
		break;
	case ENCODER_SPEED_NORMAL:
		current_set -= CURRENT_SET_NORMAL_STEP;
		break;
	case ENCODER_SPEED_SLOW:
		current_set -= CURRENT_SET_SLOW_STEP;
		break;
	}
	if(current_set < 0)
	{
		current_set = 0;
	}
}
static void GuiPopOut(char *title1, char *title2, char *title3)
{
	int i;
	for(i = 0; i < 1000; i++)
	{
		if(u8g2_UserInterfaceMessage(&u8g2, title1, title2, title3, " Ok ") == 1)
		{
			return;
		}
		Delay_us(100);
	}
}
void GuiPageOutput(e_gui_page_t *page)
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
	sprintf(buf, "V:%05.2f", volt_real);
	u8g2_DrawStr(&u8g2, 5, 13, buf);
	sprintf(buf, "I:%4.2f", current_real);
	u8g2_DrawStr(&u8g2, 68, 13, buf);
	sprintf(buf, "V:%05.2f", volt_set);
	if(state == 0)
	{
		u8g2_SetDrawColor(&u8g2, 1); 
	}
	else if(state==1)
	{
		u8g2_SetDrawColor(&u8g2, 0); 
	}
	u8g2_DrawStr(&u8g2, 5, 43, buf);
	sprintf(buf, "I:%4.2f", current_set);
	if(state == 0)
	{
		u8g2_SetDrawColor(&u8g2, 0);
	}
	else if(state == 1)
	{
		u8g2_SetDrawColor(&u8g2, 1);
	}
	u8g2_DrawStr(&u8g2, 68, 43, buf);
	switch(KeyPressCheck(KEY_ID_ENCODER))
	{
	case key_short_press:
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
		break;
	case key_long_press:
		*page = GUI_PAGE_MENU;
		break;
	}
	
}
void GuiPageMenu(e_gui_page_t *page)
{
    u8g2_SetDrawColor(&u8g2, 1); 
	u8g2_SetFontMode(&u8g2, 1); 
	u8g2_SetFont(&u8g2, u8g2_font_8x13_tr);
	switch(u8g2_UserInterfaceSelectionList(&u8g2, "Menu", 0, "Calibration\nAbout"))
	{
	case 1:
		*page = GUI_PAGE_CALIBRATION;
		break;
	default:
		break;
	}
}
void GuiPageCalibration(e_gui_page_t *page)
{
	u8g2_SetDrawColor(&u8g2, 1); 
	u8g2_SetFontMode(&u8g2, 1); 
	u8g2_SetFont(&u8g2, u8g2_font_6x12_tf);
	if(u8g2_UserInterfaceMessage(&u8g2, "Volt Calibration\n", "Output Volt = 1V", "\n", "Ok\nCancel") == 2)
	{
		*page = GUI_PAGE_OUTPUT;
	}
}

