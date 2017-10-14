#ifndef __GPIO_H
#define	__GPIO_H

#include "stm32f10x.h"

#define HIGH  1
#define LOW 0


#define GPIO_SET(port,pin,level) 	if( level )\
										GPIO_SetBits( port, pin );\
									else\
										GPIO_ResetBits(port, pin);

#define GPIO_GET(port,pin )			GPIO_ReadInputDataBit( port, pin )

/*for oled*/
#define GPIO_OLED_PORT 			GPIOA
#define GPIO_OLED_DC 			GPIO_Pin_3
#define GPIO_OLED_CS 			GPIO_Pin_4
#define GPIO_OLED_MOSI 			GPIO_Pin_7
#define GPIO_OLED_CLK 			GPIO_Pin_5
#define GPIO_OLED_ALL 			GPIO_OLED_DC|GPIO_OLED_CS|GPIO_OLED_MOSI|GPIO_OLED_CLK

/*for encoder*/
#define GPIO_ENCODER_PORT 		GPIOC
#define GPIO_ENCODER_BUTTON		GPIO_Pin_15
#define GPIO_ENCODER_A			GPIO_Pin_14
#define GPIO_ENCODER_C			GPIO_Pin_13


void GPIOOledSWInit(void);


#endif /* __GPIO_H */
