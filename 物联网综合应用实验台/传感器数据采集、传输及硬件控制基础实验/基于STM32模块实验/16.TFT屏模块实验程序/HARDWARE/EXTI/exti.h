#ifndef _EXTI_H
#define _EXTI_H

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

extern uint8_t Key_Value;			//获取到的按键值
extern void EXTI_Init(void);	//外部中断初始化

#endif


