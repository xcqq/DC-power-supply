#ifndef __EXTI_H
#define	__EXTI_H

#include "include.h"

#define EXTI_ENCODER_PORT 	GPIO_PortSourceGPIOC
#define EXTI_ENCODER_PIN 	GPIO_PinSource14

void EXTIEncoderConfig(void);
int EncoderGet();


#endif /* __XXX_H */
