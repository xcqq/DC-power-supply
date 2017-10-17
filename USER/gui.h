//
// Created by xczhang on 17-7-12.
//

#ifndef __GUI_H
#define __GUI_H

#include "include.h"

#define VOLT_SET_MAX 30
#define CURRENT_SET_MAX 5

typedef enum
{
	GUI_PAGE_WELCOME,
	GUI_PAGE_OUTPUT,
	GUI_PAGE_CALIBRATION,
	GUI_PAGE_MENU,
}e_gui_page_t;


void GuiPageOutput(e_gui_page_t *page);
void GuiPageMenu(e_gui_page_t *page);
void GuiPageCalibration(e_gui_page_t *page);


extern float volt_set;
extern float current_set;
extern float volt_real;
extern float current_real; 

#endif //__GUI_H
