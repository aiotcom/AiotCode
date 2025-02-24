#include "stm32f1xx.h"
#include "string.h"
#include "delay.h"
#include "RC522.h"
#include "usart.h"	

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
*	说明： 		HF-RFID
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/

int main(void)
{
	HAL_Init();           		//初始化HAL库
	RC522_Init();     				//初始化RC522模块
	UART2_Init(115200);				//初始化串口2

	while(1)
	{
		IC_Card_Search();				//检测卡-检测到将数据发送
	}
}



