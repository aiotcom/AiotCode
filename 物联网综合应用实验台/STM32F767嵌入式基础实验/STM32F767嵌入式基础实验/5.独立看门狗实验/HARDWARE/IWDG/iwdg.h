#ifndef __IWDG_H
#define __IWDG_H

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

void IWDG_Init(unsigned char prer,unsigned int rlr);//初始化IWDG，并使能IWDG
void IWDG_Feed(void);//喂狗


#endif
