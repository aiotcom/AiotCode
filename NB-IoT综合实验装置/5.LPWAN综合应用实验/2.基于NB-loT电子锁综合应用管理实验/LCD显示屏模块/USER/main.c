#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "usart.h"
#include "Rs485.h"	
#include "TFT.h"

/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2019-01-01
*
*	版本： 		V1.0
*
*	说明： 		TFT操作实验-HAL库版本
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/

int main(void)
{
    HAL_Init();             					//初始化HAL库
		TFT_Init();             					//初始化TFT显示器端口
		Rs485_Init();											//初始化485
    UART1_Init(115200);								//初始化串口
		Lcd_Init();												//初始化LCD
		LCD_UI();													//背景UI

		while(1)
		{
				TFT_Update();									//TFT显示数据更新				
		}
}




