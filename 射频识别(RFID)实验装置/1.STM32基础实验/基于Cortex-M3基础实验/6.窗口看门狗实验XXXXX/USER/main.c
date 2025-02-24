#include "stm32f1xx.h"
#include "delay.h"
#include "wwdg.h"
#include "led.h"
#include "key.h"

/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2019-12-31
*
*	版本： 		V1.0
*
*	说明： 		窗口看门狗实验-HAL库版本
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/


int main(void)
{
	HAL_Init();       //初始化HAL库    
	LED_Init();				//初始化LED	
	LED_Twinkle();		//四个LED全都闪烁两次
	LED_ON();					//四个LED全部保持常亮
  WWDG_Init(0X7F,0X5F,WWDG_PRESCALER_8); 			//计数器值为7F，窗口寄存器为5F，分频数为8

	while(1)
	{

	}
}





