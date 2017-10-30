#ifndef __ADC_H
#define	__ADC_H

#include "include.h"

typedef enum
{
	ADC_VOLT,
	ADC_CURRENT,
}e_adc_channel_t;

void ADCInit(void);
uint16_t GetADCResult(e_adc_channel_t channel);

#endif /* __ADC_H */

