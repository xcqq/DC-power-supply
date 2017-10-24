#ifndef __PWM_H
#define	__PWM_H

#include "include.h"

#define GPIO_PWM_PORT			GPIOA
#define GPIO_PWM_PIN_VOLT		GPIO_Pin_8
#define GPIO_PWM_PIN_CURRENT	GPIO_Pin_9
#define GPIO_PWM_ALL			GPIO_PWM_PIN_VOLT | GPIO_PWM_PIN_CURRENT

void PWMInit(void);

#endif /* __PWM_H */

