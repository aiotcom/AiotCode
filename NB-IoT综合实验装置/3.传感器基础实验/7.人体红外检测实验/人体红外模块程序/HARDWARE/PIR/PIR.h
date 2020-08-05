#ifndef _KEY_H
#define _KEY_H

#include "stm32f1xx.h"

#define PIR_PORT 				GPIOA
#define PIR_PIN					GPIO_PIN_0

#define PIR_LED_PORT 		GPIOA
#define PIR_LED_PIN			GPIO_PIN_2

#define PIR_Read()  		HAL_GPIO_ReadPin(PIR_PORT,PIR_PIN)  //���������

#define PIR_LED_ON()		HAL_GPIO_WritePin(PIR_LED_PORT,PIR_LED_PIN,GPIO_PIN_RESET)	//����LED
#define PIR_LED_OFF()		HAL_GPIO_WritePin(PIR_LED_PORT,PIR_LED_PIN,GPIO_PIN_SET)		//�ر�LED

extern void PIR_Init(void);

#endif
