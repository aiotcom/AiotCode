#include "HC_SR04.h"
#include "TM1640.h"	
#include "delay.h"
#include "timer.h"
#include "math.h" 

//==========================================================
//	函数名称：	HCSR04_Init()
//
//	函数功能：	初始化超声波模块
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：			
//==========================================================
void HCSR04_Init(void)
{
	  GPIO_InitTypeDef GPIO_Initure;
	
		__HAL_RCC_GPIOA_CLK_ENABLE();						//开启GPIOA时钟
		__HAL_RCC_GPIOG_CLK_ENABLE();						//开启GPIOG时钟
	
		GPIO_Initure.Pin = Echo1|Echo2|Echo3|Echo4; 	//Echo1,Echo2,Echo3,Echo4
		GPIO_Initure.Mode = GPIO_MODE_INPUT;   	//输入
		GPIO_Initure.Pull = GPIO_NOPULL;				//浮空
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);
	
	  GPIO_Initure.Pin=Trigl1|Trigl2|Trigl3; 	//Trigl1,Trigl2,Trigl3
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	//高速
   	HAL_GPIO_Init(GPIOA, &GPIO_Initure);
	
	  GPIO_Initure.Pin=Trigl4; 								//Trigl4
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	//高速
   	HAL_GPIO_Init(HCSR04_GPIOT_PORT4, &GPIO_Initure);


    Trigl1_LOW();	//Trigl1初始化置0
		Trigl2_LOW()	//Trigl2初始化置0
		Trigl3_LOW()	//Trigl3初始化置0
		Trigl4_LOW()	//Trigl4初始化置0	
}

//==========================================================
//	函数名称：	HCSR04_StartMeasure()
//
//	函数功能：	超声波模块测距
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：			
//==========================================================
void HCSR04_StartMeasure(uint8_t Num)
{
	static  uint8_t Flag = 1;
	static 	uint16_t i = 0,Avg = 0;
	static  uint32_t HCSR04_Distance = 0;

	for(i=0;i<Num;i++)
	{
		Trigl3_HIGH();			//拉高Trigl3
		delay_us(20);
		Trigl3_LOW();				//拉低Trigl3

		while(!Echo3_STATE())			//等待返回
		{
			Time_Count = 0;
			HAL_NVIC_EnableIRQ(TIM2_IRQn);    	//开启ITM2中断,开始计时
			Flag = 1;
		}
		
		while(Flag)														//已经检测到高电平
		{
			if(!Echo3_STATE())									//接收完成
			{
				HAL_NVIC_DisableIRQ(TIM2_IRQn);		//关闭ITM2中断
				HCSR04_Distance	+= Time_Count*17/100;		
				Time_Count = 0;
				Flag = 0;
			}
		}
	}
	
	Avg = HCSR04_Distance/Num;
	send_LED_Display(0xC0,Avg,1);				//数码管显示距离
	HCSR04_Distance = 0;
	delay_ms(100);
}




