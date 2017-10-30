
#include "calibration.h"

s_calibration_t calibration_real_volt=
{
	100,
	0
}; 
s_calibration_t calibration_real_current=
{
	100,
	0
}; 
s_calibration_t calibration_set_volt =
{
	100,
	0
};
s_calibration_t calibration_set_current =
{
	100,
	0
};

float volt_calibration_value[] = {0,1.0,5.0,10.0,20.0,30.0};
float current_calibration_value[] = { 0, 0.05, 0.1, 1, 3, 5 }; 

uint8_t CalibrationGetPointSetValue(s_calibration_t *calibration, uint8_t index, uint16_t *value)
{
	if(index < CALIBRATION_POINT_NUM)
	{
		*value = calibration->point[index].set_value;
		return 0;
	}
	else
	{
		return -1;
	}
}

uint8_t CalibrationSetPoint(s_calibration_t *calibration, uint8_t index, uint16_t set, uint16_t real)
{
	if(index < CALIBRATION_POINT_NUM)
	{
		calibration->point[index].set_value = set;
		calibration->point[index].real_value = real;
		return 0;
	}
	else
	{
		return -1;
	}
}

uint8_t CalibrationUpdateFitting(s_calibration_t *calibration)
{
	uint8_t i;
	for(i = 0; i < CALIBRATION_POINT_NUM - 1; i++)
	{
		calibration->fitting[i].k = (float)(calibration->point[i + 1].set_value - calibration->point[i].set_value) /
			(float)(calibration->point[i + 1].real_value - calibration->point[i].real_value);
		calibration->fitting[i].b = calibration->point[i].set_value - calibration->fitting[i].k * calibration->point[i].real_value;
	}
	calibration->fitting_flag = 1;
	return 0;
}

uint8_t CalibrationCalcValue(s_calibration_t *calibration,uint16_t *real_value,uint16_t input_value)
{
	uint8_t i=0;
	if(calibration->fitting_flag != 0)
	{
		if(input_value <= calibration->point[i].real_value)
		{
			*real_value = (float)(calibration->fitting[0].k * input_value + calibration->fitting[0].b); 
			return 0;
		}
		for(i = 0; i < CALIBRATION_POINT_NUM - 1; i++)
		{
			if((input_value <= calibration->point[i + 1].real_value)
				&& (input_value > calibration->point[i].real_value)) {
				*real_value = (float)(calibration->fitting[i].k * input_value + calibration->fitting[i].b);
				return 0;
			}

		}
		if(input_value > calibration->point[i].real_value)
		{
			*real_value = (float)(calibration->fitting[i-1].k * input_value + calibration->fitting[i-1].b); 
			return 0;
		}
	}
}
