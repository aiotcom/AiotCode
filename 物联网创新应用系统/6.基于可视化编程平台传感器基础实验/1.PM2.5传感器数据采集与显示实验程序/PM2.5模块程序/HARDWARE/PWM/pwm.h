#ifndef _pwm_H
#define _pwm_H

#include "stm32f1xx_hal.h"

extern uint32_t TIM3_Count;
extern TIM_HandleTypeDef TIM2_Handler;     	//��ʱ��2��� 

void TIM2_Init(uint16_t arr,uint16_t psc);
void TIM2_PWM_Init(uint16_t psc,uint16_t arr);
void TIM_SetTIM2Compare2(uint32_t compare);

#endif

