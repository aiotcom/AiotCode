#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "TM1640.h"	
#include "delay.h"
#include "timer.h"
#include "Usart.h"
#include "ADC.h"

/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2019-12-11
*
*	版本： 		V2.0
*
*	说明： 		温湿度模块-光照强度采集
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/

int main(void)
{
  HAL_Init();             					//初始化HAL库
	ADC_Init();												//初始化ADC
	TM1640_Init();										//初始化TM1640
	TIM3_Init(2000-1,640-1);					//初始化定时器3(20ms)

	while(1)
	{
		Display_Data();									//获取光照数据并显示到数码管上
	}
}





