//
// Created by xczhang on 17-7-12.
//

#ifndef __GUI_H
#define __GUI_H

#include "include.h"

#define VOLT_SET_MAX 30
#define CURRENT_SET_MAX 5

void GuiPageOutput(float real_v, float real_i, float set_v, float set_i);
void GuiPageMenu();
void GuiPageCalibration();


extern float volt_set;
extern float current_set;
extern float volt_real;
extern float current_real; 

#endif //__GUI_H
