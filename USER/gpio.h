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
#define GPIO_ENCODER_ALL		GPIO_ENCODER_BUTTON | GPIO_ENCODER_A | GPIO_ENCODER_C

/*for voltage and current adc*/
#define GPIO_ADC_PORT			GPIOB
#define GPIO_ADC_VOLT			GPIO_Pin_0
#define GPIO_ADC_CURRENT		GPIO_Pin_1
#define GPIO_ADC_ALL			GPIO_ADC_VOLT | GPIO_ADC_CURRENT

#define Is_ShortPress_Threshold   500 
typedef struct
{  
    u32 last_time;  
    enum  
    {  
        key_state_press,  
        key_state_release,  
    }private_state;  
    enum  
    {  
        key_no_press,  
        key_short_press,  
        key_long_press,  
    }state;  
}s_key_state_t;

typedef enum
{
	KEY_ID_ENCODER,
	KEY_ID_END,
}e_key_id_t;

typedef struct
{
	e_key_id_t key_id;
	GPIO_TypeDef *key_port;
	uint16_t key_pin;
	s_key_state_t key_state;
}s_key_t;



void GPIOOledSWInit(void);
void GPIOEncoderInit(void);
void GPIOADCConfig(void);
int8_t KeyPressCheck(e_key_id_t key_id);

#endif /* __GPIO_H */
