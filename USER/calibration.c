
#include "calibration.h"

s_calibration_t calibration_real_volt;
s_calibration_t calibration_real_current;
s_calibration_t calibration_set_volt;
s_calibration_t calibration_set_current;

void CalibrationInit(s_calibration_t *calibration,uint8_t point_num, uint8_t scaling)
{
	calibration->point_num = point_num;
	calibration->scaling = scaling;
	calibration->point = (s_calibration_point_t *)calloc(calibration->point_num, sizeof(s_calibration_point_t));
	calibration->fitting = (s_calibration_fitting_t *)calloc(calibration->point_num - 1, sizeof(s_calibration_fitting_t));
}

uint8_t CalibrationGetPointSetValue(s_calibration_t *calibration, uint8_t index, uint16_t *value)
{
	if(index < calibration->point_num)
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
	if(index < calibration->point_num)
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
	if(calibration->point_num!=0)
	{
		for(i = 0; i < calibration->point_num - 1; i++)
		{
			calibration->fitting[i].k = (float)(calibration->point[i + 1].set_value - calibration->point[i].set_value) /
				(float)(calibration->point[i + 1].real_value - calibration->point[i].real_value);
			calibration->fitting[i].b = calibration->point[i].set_value - calibration->fitting[i].k * calibration->point[i].real_value;
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

uint8_t CalibrationCalcValue(s_calibration_t *calibration,float *real_value,uint16_t input_value)
{
	uint8_t i;
	if(calibration->point_num != 0)
	{
		if(input_value <= calibration->point[i].real_value)
		{
			*real_value = (float)(calibration->fitting[0].k * input_value + calibration->fitting[0].b); 
			return 0;
		}
		for(i = 0; i < calibration->point_num - 1; i++)
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
	else
	{
		return -1;
	}
}
