#ifndef _LED_H
#define _LED_H

#include "stm32f1xx.h"

#define 	LED_PORT 		GPIOA

#define 	LED1_PIN 		GPIO_PIN_3
#define 	LED2_PIN 		GPIO_PIN_2
#define 	LED3_PIN 		GPIO_PIN_7
#define 	LED4_PIN 		GPIO_PIN_6

#define 	LED1_ON()		HAL_GPIO_WritePin(LED_PORT,LED1_PIN,GPIO_PIN_RESET)	//����LED1
#define 	LED1_OFF()	HAL_GPIO_WritePin(LED_PORT,LED1_PIN,GPIO_PIN_SET)		//�ر�LED1

#define 	LED2_ON()		HAL_GPIO_WritePin(LED_PORT,LED2_PIN,GPIO_PIN_RESET)	//����LED2
#define 	LED2_OFF()	HAL_GPIO_WritePin(LED_PORT,LED2_PIN,GPIO_PIN_SET)		//�ر�LED2

#define 	LED3_ON()		HAL_GPIO_WritePin(LED_PORT,LED3_PIN,GPIO_PIN_RESET)	//����LED3
#define 	LED3_OFF()	HAL_GPIO_WritePin(LED_PORT,LED3_PIN,GPIO_PIN_SET)		//�ر�LED3

#define 	LED4_ON()		HAL_GPIO_WritePin(LED_PORT,LED4_PIN,GPIO_PIN_RESET)	//����LED4
#define 	LED4_OFF()	HAL_GPIO_WritePin(LED_PORT,LED4_PIN,GPIO_PIN_SET)		//�ر�LED4

#define 	LED_ON()		HAL_GPIO_WritePin(LED_PORT,LED1_PIN|LED2_PIN|LED3_PIN|LED4_PIN,GPIO_PIN_RESET)	//����ȫ��LED
#define 	LED_OFF()		HAL_GPIO_WritePin(LED_PORT,LED1_PIN|LED2_PIN|LED3_PIN|LED4_PIN,GPIO_PIN_SET)		//�ر�ȫ��LED

extern void LED_Init(void);
extern void Water_Lamp(uint16_t time);


#endif


