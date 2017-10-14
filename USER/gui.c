
#include "gui.h"

void GuiPageOutput(float real_v,float real_i,float set_v,float set_i)
{
	char buf[20];
	u8g2_SetDrawColor(&u8g2, 1); 
	u8g2_DrawBox(&u8g2, 0, 0, 128, 10);
	u8g2_DrawBox(&u8g2, 0, 30, 128, 10); 
    u8g2_SetFont(&u8g2, u8g2_font_6x12_tf);
    u8g2_SetFontPosTop(&u8g2);
	u8g2_SetDrawColor(&u8g2, 0);
    u8g2_DrawStr(&u8g2, 55, 0, "real");
	u8g2_DrawStr(&u8g2, 58, 30, "set"); 
	u8g2_SetDrawColor(&u8g2, 1); 
	u8g2_SetFont(&u8g2, u8g2_font_8x13_tf);
	sprintf(buf, "V:%02.2f", real_v);
	u8g2_DrawStr(&u8g2, 5, 13, buf);
	sprintf(buf, "I:%.2f", real_i); 
	u8g2_DrawStr(&u8g2, 68, 13, buf);
	sprintf(buf, "V:%02.2f", set_v); 
	u8g2_DrawStr(&u8g2, 5, 43, buf);
	sprintf(buf, "I:%.2f", set_v); 
	u8g2_DrawStr(&u8g2, 68, 43, buf);
}
void GuiPageMenu()
{

}
void GuiPageCalibration()
{

}
