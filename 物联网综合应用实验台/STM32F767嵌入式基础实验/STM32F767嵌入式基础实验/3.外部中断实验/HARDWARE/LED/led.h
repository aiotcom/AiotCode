#ifndef _LED_H
#define _LED_H

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

#define 	LED_PORT 		GPIOA

#define 	LED1_PIN 		GPIO_PIN_10
#define 	LED2_PIN 		GPIO_PIN_9
#define 	LED3_PIN 		GPIO_PIN_0
#define 	LED4_PIN 		GPIO_PIN_3

#define 	LED1_ON()		HAL_GPIO_WritePin(LED_PORT,LED1_PIN,GPIO_PIN_RESET)	//点亮LED1
#define 	LED1_OFF()	HAL_GPIO_WritePin(LED_PORT,LED1_PIN,GPIO_PIN_SET)		//关闭LED1

#define 	LED2_ON()		HAL_GPIO_WritePin(LED_PORT,LED2_PIN,GPIO_PIN_RESET)	//点亮LED2
#define 	LED2_OFF()	HAL_GPIO_WritePin(LED_PORT,LED2_PIN,GPIO_PIN_SET)		//关闭LED2

#define 	LED3_ON()		HAL_GPIO_WritePin(LED_PORT,LED3_PIN,GPIO_PIN_RESET)	//点亮LED3
#define 	LED3_OFF()	HAL_GPIO_WritePin(LED_PORT,LED3_PIN,GPIO_PIN_SET)		//关闭LED3

#define 	LED4_ON()		HAL_GPIO_WritePin(LED_PORT,LED4_PIN,GPIO_PIN_RESET)	//点亮LED4
#define 	LED4_OFF()	HAL_GPIO_WritePin(LED_PORT,LED4_PIN,GPIO_PIN_SET)		//关闭LED4

#define 	LED_ON()		HAL_GPIO_WritePin(LED_PORT,LED1_PIN|LED2_PIN|LED3_PIN|LED4_PIN,GPIO_PIN_RESET)	//点亮全部LED
#define 	LED_OFF()		HAL_GPIO_WritePin(LED_PORT,LED1_PIN|LED2_PIN|LED3_PIN|LED4_PIN,GPIO_PIN_SET)		//关闭全部LED

extern void LED_Init(void);
extern void LED_Twinkle(void);
extern void Water_Lamp(uint16_t time);

#endif
