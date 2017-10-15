#include "include.h"
u8g2_t u8g2;
int main(void)
{
    SysTick_Init();
	EXTIEncoderConfig();
    oledInit(&u8g2);
	ADCInit();
	float real_value;
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
		GuiPageOutput(0,0,0,0);
		u8g2_SendBuffer(&u8g2);
    }
}


