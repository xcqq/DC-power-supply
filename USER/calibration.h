//
// Created by xczhang on 17-7-12.
//

#ifndef __CALABRATION_H
#define __CALABRATION_H

#include "include.h"



typedef struct
{
	uint16_t set_value;
	uint16_t real_value;
}s_calibration_point_t;

typedef struct
{
	float k;
	float b;
}s_calibration_fitting_t;

typedef struct
{
	uint8_t point_num;
	uint8_t scaling;
	s_calibration_point_t *point;
	s_calibration_fitting_t *fitting;
}s_calibration_t;

void CalibrationInit(s_calibration_t *calibration, uint8_t point_num, uint8_t scaling);
uint8_t CalibrationGetPointSetValue(s_calibration_t *calibration, uint8_t index, uint16_t *value);
uint8_t CalibrationSetPoint(s_calibration_t *calibration, uint8_t index, uint16_t set, uint16_t real);
uint8_t CalibrationUpdateFitting(s_calibration_t *calibration);
uint8_t CalibrationCalcValue(s_calibration_t *calibration, uint16_t *real_value, uint16_t input_value);

extern s_calibration_t calibration_real_volt;
extern s_calibration_t calibration_real_current;
extern s_calibration_t calibration_set_volt;
extern s_calibration_t calibration_set_current; 

#endif //__CALABRATION_H
