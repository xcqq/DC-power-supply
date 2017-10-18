#ifndef __EXTI_H
#define	__EXTI_H

#include "include.h"

#define EXTI_ENCODER_PORT 	GPIO_PortSourceGPIOC
#define EXTI_ENCODER_PIN 	GPIO_PinSource14
#define ENCODER_THRESHOLD_FAST 20
#define ENCODER_THRESHOLD_SLOW 200

typedef void (*encoder_callback)(uint8_t speed); 

typedef enum
{
	ENCODER_SPEED_FAST,
	ENCODER_SPEED_NORMAL,
	ENCODER_SPEED_SLOW,
}e_encoder_speed_t;

void EXTIEncoderConfig(void);
int EncoderGet();
int EncoderRegistCallback(encoder_callback upCallback, encoder_callback downCallback);
int EncoderUnregistCallback();
uint8_t EncoderGetSpeed();

#endif /* __XXX_H */
