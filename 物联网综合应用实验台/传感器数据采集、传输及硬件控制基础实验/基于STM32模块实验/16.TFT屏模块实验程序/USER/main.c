#include "Rs485.h"
#include "usart.h"
#include "delay.h"
#include "font.h"
#include "exti.h"
#include "TFT.h"

/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2020-03-13
*
*	版本： 		V1.0
*
*	说明： 		STM32F767-TFT显示屏模块实验
*
*	修改记录：
************************************************************
************************************************************
************************************************************
**/

int main(void)
{
	HAL_Init();       	//初始化HAL库   
	TFT_Init();         //初始化TFT显示器端口
	Lcd_Init();					//初始化LCD
	Rs485_Init();				//初始化485
	UART7_Init(115200);	//初始化串口七
	TFT_UI();						//UI界面 
	EXTI_Init();				//初始化外部中断

	while(1)
	{
		Key_Handler();		//屏幕触摸按键数据处理	
	}
}



