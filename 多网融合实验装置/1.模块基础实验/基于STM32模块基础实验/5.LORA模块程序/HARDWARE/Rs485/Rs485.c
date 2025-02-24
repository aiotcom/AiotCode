#include "Rs485.h"	
#include "stdio.h"
//==========================================================
//	函数名称：	Rs485_Init
//
//	函数功能：	初始化485
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void Rs485_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           						//开启GPIOA时钟
	
    GPIO_Initure.Pin = GPIO_PIN_8;											//PA8
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;						//推挽输出
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW; 					//低速
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);

    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);	//PA8置0   初始化等待模式
}

//==========================================================
//	函数名称：	Rs485_Config
//
//	函数功能：	控制485收发模式
//
//	入口参数：	1(485发送)   0(485接收)
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void Rs485_Config(uint8_t fag)
{
	if(fag){
		RS485_TX_EN; //开启485发送
	}
	else
		RS485_RX_EN; //开启485接收
}


