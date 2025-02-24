#include "stm32f1xx.h"
#include "delay.h"
#include "exti.h"
#include "led.h"
#include "key.h"

/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2020-03-10
*
*	版本： 		V2.0
*
*	说明： 		外部中断函数操作实验-HAL库版本
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
	EXTI_Init();			//初始化外部中断

	while(1)
	{
		if(Key_flag)			//有按键按下
		{
			if(Key_flag==1)	//按键1按下
			{
				LED_Twinkle();//LED灯闪烁
				Key_flag = 0;
			}
			else if(Key_flag==2)//按键2按下
			{
				LED_ON();
				delay_ms(2000);
				LED_OFF();
				Key_flag = 0;
			}
		}
		else
		{
			Water_Lamp(500);//LED流水灯		
		}
	}
}





