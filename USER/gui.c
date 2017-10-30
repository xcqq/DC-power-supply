
#include "gui.h"
float volt_set = 0;
float current_set = 0; 
float volt_real = 0;
float current_real = 0;

uint16_t raw_volt_set;
uint16_t raw_current_set;

extern float volt_calibration_value[];
extern float current_calibration_value[]; 
static void GuiAddRawVoltSet(e_encoder_speed_t speed)
{
	int32_t temp = raw_volt_set;
	switch(speed)
	{
	case ENCODER_SPEED_FAST:
		temp += DA_SET_FAST_STEP;
		break;
	case ENCODER_SPEED_NORMAL:
		temp += DA_SET_NORMAL_STEP;
		break;
	case ENCODER_SPEED_SLOW:
		temp += DA_SET_SLOW_STEP;
		break;
	}
	if(temp > DA_SET_MAX)
	{
		temp = DA_SET_MAX;
	}
	raw_volt_set = temp;
}
static void GuiMinusRawVoltSet(e_encoder_speed_t speed)
{
	int32_t temp = raw_volt_set; 
	switch(speed)
	{
	case ENCODER_SPEED_FAST:
		temp -= DA_SET_FAST_STEP;
		break;
	case ENCODER_SPEED_NORMAL:
		temp -= DA_SET_NORMAL_STEP;
		break;
	case ENCODER_SPEED_SLOW:
		temp -= DA_SET_SLOW_STEP;
		break;
	}
	if(temp < 0)
	{
		temp = 0;
	}
	raw_volt_set = temp;
}
static void GuiAddRawCurrentSet(e_encoder_speed_t speed)
{
	switch(speed)
	{
	case ENCODER_SPEED_FAST:
		raw_current_set += DA_SET_FAST_STEP;
		break;
	case ENCODER_SPEED_NORMAL:
		raw_current_set += DA_SET_NORMAL_STEP;
		break;
	case ENCODER_SPEED_SLOW:
		raw_current_set += DA_SET_SLOW_STEP;
		break;
	}
	if(raw_current_set > DA_SET_MAX)
	{
		raw_current_set = DA_SET_MAX;
	}
}
static void GuiMinusRawCurrentSet(e_encoder_speed_t speed)
{
	switch(speed)
	{
	case ENCODER_SPEED_FAST:
		raw_current_set -= DA_SET_FAST_STEP;
		break;
	case ENCODER_SPEED_NORMAL:
		raw_current_set -= DA_SET_NORMAL_STEP;
		break;
	case ENCODER_SPEED_SLOW:
		raw_current_set -= DA_SET_SLOW_STEP;
		break;
	}
	if(raw_current_set < 0)
	{
		raw_current_set = 0;
	}
}
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
	uint16_t temp;
	CalibrationCalcValue(&calibration_real_volt, &temp, GetADCResult(ADC_VOLT));
	volt_real = (float)temp / calibration_real_volt.scaling;
	CalibrationCalcValue(&calibration_real_current, &temp, GetADCResult(ADC_CURRENT));
	current_real = (float)temp / calibration_real_current.scaling;
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
	u8g2_DrawStr(&u8g2, 3, 13, buf);
	sprintf(buf, "I:%5.3f", current_real);
	u8g2_DrawStr(&u8g2, 65, 13, buf);
	sprintf(buf, "V:%05.2f", volt_set);
	if(state == 0)
	{
		u8g2_SetDrawColor(&u8g2, 1); 
	}
	else if(state==1)
	{
		u8g2_SetDrawColor(&u8g2, 0); 
	}
	u8g2_DrawStr(&u8g2, 3, 43, buf);
	sprintf(buf, "I:%4.2f", current_set);
	if(state == 0)
	{
		u8g2_SetDrawColor(&u8g2, 0);
	}
	else if(state == 1)
	{
		u8g2_SetDrawColor(&u8g2, 1);
	}
	u8g2_DrawStr(&u8g2, 65, 43, buf);
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
		EncoderUnregistCallback(); 
		TIM_SetCompare1(TIM1, 0);
		TIM_SetCompare2(TIM1, 0); 
		break;
	}
	
	CalibrationCalcValue(&calibration_set_volt, &temp, (uint16_t)(volt_set * calibration_set_volt.scaling));
	raw_volt_set = temp; 
	CalibrationCalcValue(&calibration_set_current, &temp, (uint16_t)(current_set * calibration_set_current.scaling));
	raw_current_set = temp;
	
	TIM_SetCompare1(TIM1, raw_volt_set); 
	TIM_SetCompare2(TIM1, raw_current_set);
	
}
void GuiPageMenu(e_gui_page_t *page)
{
    u8g2_SetDrawColor(&u8g2, 1); 
	u8g2_SetFontMode(&u8g2, 1); 
	u8g2_SetFont(&u8g2, u8g2_font_6x12_tf);
	EncoderGuiEnable();
	switch(u8g2_UserInterfaceSelectionList(&u8g2, "Menu", 0, "Fast volt\r\nFast Current\r\nSetting"))
	{
	case 0:
		*page = GUI_PAGE_OUTPUT;
		break;
	case 1:
		*page = GUI_PAGE_FAST_SETTING_VOLT;
		break;
	case 2:
		*page = GUI_PAGE_FAST_SETTING_CURRENT;
		break;
	case 3:
		*page = GUI_PAGE_SETTING;
		break;

	default:
		break;
	}
}
void GuiPageCalibration(e_gui_page_t *page)
{
	uint8_t i = 0;
	int8_t ret;
	char buf[30];
	u8g2_SetDrawColor(&u8g2, 1); 
	u8g2_SetFontMode(&u8g2, 1); 
	u8g2_SetFont(&u8g2, u8g2_font_6x12_tf);
	EncoderGuiDisable();
	EncoderRegistCallback(GuiAddRawVoltSet, GuiMinusRawVoltSet);
	while(1)
	{
		sprintf(buf, "Output Volt = %.2fV", volt_calibration_value[i]);
		ret = u8g2_UserInterfaceMessage(&u8g2, "Volt Calibration\n", buf, "\n", "  Next  \n  Cancel  ");
		if(ret == 1)
		{
			if(i < CALIBRATION_POINT_NUM)
			{
				CalibrationSetPoint(& calibration_real_volt, i,  (uint16_t)(volt_calibration_value[i] * calibration_real_volt.scaling), GetADCResult(ADC_VOLT));
				CalibrationSetPoint(&calibration_set_volt, i, raw_volt_set, (uint16_t)(volt_calibration_value[i] * calibration_set_volt.scaling));
				i++;
			}
			else
			{
				CalibrationUpdateFitting(&calibration_set_volt);
				CalibrationUpdateFitting(&calibration_real_volt);
				GuiPopOut("Volt calibration", "complete!", "");
				SaveConfig();
				break;
			}
		}
		else if(ret == 2)
		{
			EncoderUnregistCallback();
		}
		TIM_SetCompare1(TIM1, raw_volt_set);
		TIM_SetCompare2(TIM1, 65535); 
	}
	i = 0;
	EncoderRegistCallback(GuiAddRawCurrentSet, GuiMinusRawCurrentSet);
	while(1)
	{
		sprintf(buf, "Output Current = %.2fA", current_calibration_value[i]);
		ret = u8g2_UserInterfaceMessage(&u8g2, "Volt Calibration\n", buf, "\n", "  Next  \n  Cancel  ");
		if(ret==1)
		{
			if(i < CALIBRATION_POINT_NUM)
			{
				CalibrationSetPoint(&calibration_real_current, i, (uint16_t)(current_calibration_value[i] * calibration_real_current.scaling), GetADCResult(ADC_CURRENT));
				CalibrationSetPoint(&calibration_set_current, i, raw_current_set, (uint16_t)(current_calibration_value[i] * calibration_set_current.scaling));
				i++;
			}
			else
			{
				CalibrationUpdateFitting(&calibration_set_current);
				CalibrationUpdateFitting(&calibration_real_current);
				GuiPopOut("Current calibration", "complete!", "");
				SaveConfig(); 
				break;
			}
		}
		else if(ret == 2)
		{
			EncoderUnregistCallback(); 
		}
		TIM_SetCompare1(TIM1, 65535); 
		TIM_SetCompare2(TIM1, raw_current_set);
	}
	*page = GUI_PAGE_SETTING;
}
void GuiPageVoltFastSetting(e_gui_page_t *page)
{
	u8g2_SetDrawColor(&u8g2, 1);
	u8g2_SetFontMode(&u8g2, 1);
	u8g2_SetFont(&u8g2, u8g2_font_6x12_tf);
	EncoderGuiEnable();
	switch(u8g2_UserInterfaceSelectionList(&u8g2, "Volt Setting", 0, "3.3V\n5V\n9V\n12V\n15V\n21V"))
	{
	case 0:
		*page = GUI_PAGE_MENU;
		break;
	case 1:
		break;
	default:
		break;
	}
}
void GuiPageCurrentFastSetting(e_gui_page_t *page)
{
	u8g2_SetDrawColor(&u8g2, 1);
	u8g2_SetFontMode(&u8g2, 1);
	u8g2_SetFont(&u8g2, u8g2_font_6x12_tf);
	EncoderGuiEnable();
	switch(u8g2_UserInterfaceSelectionList(&u8g2, "Current Setting", 0, "10mA\n50mA\n100mA\n500mA\n1A\n2A\n5A\n"))
	{
	case 0:
		*page = GUI_PAGE_MENU;
		break;
	case 1:
		*page = GUI_PAGE_FAST_SETTING_VOLT;
		break;
	default:
		break;
	}
}
void GuiPageSettings(e_gui_page_t *page)
{
	int8_t ret;
	u8g2_SetDrawColor(&u8g2, 1);
	u8g2_SetFontMode(&u8g2, 1);
	u8g2_SetFont(&u8g2, u8g2_font_6x12_tf);
	EncoderGuiEnable();
	ret = u8g2_UserInterfaceSelectionList(&u8g2, "Settings", 0, "Calibration\r\nAbout");
	switch(ret)
	{
	case 0:
		*page = GUI_PAGE_MENU;
		break;
	case 1:
		*page = GUI_PAGE_CALIBRATION;
		break;
	case 2:
		GuiPopOut("Dight", "DC power", "by xczhang");
		break;
	}
	
}
