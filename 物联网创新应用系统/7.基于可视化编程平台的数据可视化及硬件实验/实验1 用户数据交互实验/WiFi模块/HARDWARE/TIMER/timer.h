#ifndef _TIMER_H
#define _TIMER_H
#include "stm32f1xx.h"

extern uint8_t Usart2_Rx_Flag;
extern uint32_t Task_Count,RX_Count;		//��ʱ�������ֵ
extern TIM_HandleTypeDef TIM2_Handler;  //��ʱ����� 
void TIM2_Init(unsigned int arr,unsigned int psc);

#endif

