#include "include.h"
u8g2_t u8g2;

int main(void)
{	
    float real_value;
	uint16_t test = 100, test1;
	e_gui_page_t gui_page = GUI_PAGE_OUTPUT;
    SysTick_Init();
	GPIOButtonInit();
    oledInit(&u8g2);
	ADCInit();
	EXTIEncoderConfig(); 
	PWMInit();
	ReadConfig();
    while(1)
    {
		u8g2_ClearBuffer(&u8g2);
		switch(gui_page)
		{
		case GUI_PAGE_CALIBRATION:
			GuiPageCalibration(&gui_page);
			break;
		case GUI_PAGE_OUTPUT:
			GuiPageOutput(&gui_page);
			break;
		case GUI_PAGE_MENU:
			GuiPageMenu(&gui_page);
			break;
		case GUI_PAGE_SETTING:
			GuiPageSettings(&gui_page);
			break;
		case GUI_PAGE_FAST_SETTING_CURRENT:
			GuiPageCurrentFastSetting(&gui_page);
			break;
		case GUI_PAGE_FAST_SETTING_VOLT:
			GuiPageVoltFastSetting(&gui_page);
			break;
		}
		u8g2_SendBuffer(&u8g2);
    }
}


