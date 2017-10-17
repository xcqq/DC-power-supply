#include "include.h"
u8g2_t u8g2;

int main(void)
{	
    float real_value;
	e_gui_page_t gui_page = GUI_PAGE_OUTPUT;
    SysTick_Init();
	
    oledInit(&u8g2);
	ADCInit();
	EXTIEncoderConfig(); 


//    u8g2_SetFontMode(&u8g2,1);
//    u8g2_SetFontDirection(&u8g2,0);
//    u8g2_SetFont(&u8g2, u8g2_font_6x12_tf);
//    u8g2_SetFontPosTop(&u8g2);
//    u8g2_DrawStr(&u8g2, 0, 0, "hello world");
	CalibrationInit(&calibration_real_volt, 3, 10);
	CalibrationSetPoint(&calibration_real_volt,0, 0, 0);
	CalibrationSetPoint(&calibration_real_volt,1, 10, 5);
    CalibrationSetPoint(&calibration_real_volt,2, 20, 20);
	CalibrationUpdateFitting(&calibration_real_volt);
	CalibrationCalcValue(&calibration_real_volt, &real_value, 5);
	CalibrationCalcValue(&calibration_real_volt, &real_value, 20); 
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
		}
		u8g2_SendBuffer(&u8g2);
    }
}


