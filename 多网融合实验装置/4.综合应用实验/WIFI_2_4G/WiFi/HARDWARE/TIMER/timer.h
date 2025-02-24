#ifndef _TIMER_H
#define _TIMER_H
#include "stm32f1xx.h"

extern uint32_t Task_Count,Send_OneNET_Count;	//分时任务计数值
extern TIM_HandleTypeDef TIM2_Handler;  //定时器句柄 
void TIM2_Init(unsigned int arr,unsigned int psc);
extern uint32_t Display_Count;
extern TIM_HandleTypeDef TIM3_Handler;  //定时器句柄 
void TIM3_Init(uint16_t arr,uint16_t psc,void (*cb)(void));
#endif

