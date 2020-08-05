#ifndef _LED_H
#define _LED_H

#include "stm32f1xx.h"

#define 	LED_PORT 		GPIOB

#define 	LED1 				GPIO_PIN_0
#define 	LED2 				GPIO_PIN_1
#define 	LED3 				GPIO_PIN_13
#define 	LED4 				GPIO_PIN_14

#define 	LED1_ON()		HAL_GPIO_WritePin(LED_PORT,LED1,GPIO_PIN_RESET)	//����LED1
#define 	LED1_OFF()	HAL_GPIO_WritePin(LED_PORT,LED1,GPIO_PIN_SET)		//�ر�LED1

#define 	LED2_ON()		HAL_GPIO_WritePin(LED_PORT,LED2,GPIO_PIN_RESET)	//����LED2
#define 	LED2_OFF()	HAL_GPIO_WritePin(LED_PORT,LED2,GPIO_PIN_SET)		//�ر�LED2

#define 	LED3_ON()		HAL_GPIO_WritePin(LED_PORT,LED3,GPIO_PIN_RESET)	//����LED3
#define 	LED3_OFF()	HAL_GPIO_WritePin(LED_PORT,LED3,GPIO_PIN_SET)		//�ر�LED3

#define 	LED4_ON()		HAL_GPIO_WritePin(LED_PORT,LED4,GPIO_PIN_RESET)	//����LED4
#define 	LED4_OFF()	HAL_GPIO_WritePin(LED_PORT,LED4,GPIO_PIN_SET)		//�ر�LED4

#define 	LED_ON()		HAL_GPIO_WritePin(LED_PORT,LED1|LED2|LED3|LED4,GPIO_PIN_RESET)	//����ȫ��LED
#define 	LED_OFF()		HAL_GPIO_WritePin(LED_PORT,LED1|LED2|LED3|LED4,GPIO_PIN_SET)		//�ر�ȫ��LED

void LED_Init(void);
void Water_Lamp(uint16_t time);


#endif


