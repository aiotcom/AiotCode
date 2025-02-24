#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "timer.h"
#include "mp3.h"
/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2019-04-22
*
*	版本： 		V1.0
*
*	说明： 		音乐模块
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/

void RS485_HandlerCb(void);
unsigned char _Start[5] 	= {0x7E,0X03,0XAA,0XAD,0XEF};  	//开始/暂停播放
unsigned char _Cycle3[6] = {0x7E,0X04,0XAF,0X02,0XB5,0XEF};  //所有曲目循环播放
uint16_t Cmd_MP3[2];
int main(void)
{
    HAL_Init();             					//初始化HAL库  
	Rs485_Init();							    //初始化485
	UART1_Init(115200);						    //初始化串口1
	UART2_Init(9600);						    //初始化串口2
	TIM3_Init(5000-1,640-1,RS485_HandlerCb);	//初始化定时器中断周期64M/64/10000/ = 20HZ
    
    USART3_Init(115200);
   // MP3_Init();
    HAL_Delay(3000);    
    //MP3_DispalyTarget(1);
    HAL_Delay(1000);
    //MP3_StartDisplay();
    printf("this usart3 print\r\n");
	while(1)
	{
        if(Cmd_MP3[0])
        {            
            switch(Cmd_MP3[0])
            {
                case MP3_Start_Pause:
                    MP3_StopDisplay();
                    printf("pause\r\n");
                    break;
                case MP3_Last_Song:
                    MP3_NextItemDisplay();
                    printf("nexit item\r\n");
                    break;
                case MP3_Next_Song:
                    MP3_PreItemDisplay();
                    printf("lash item\r\n");
                    break;
                case MP3_Target:
                    MP3_DispalyTarget(Cmd_MP3[1]);
                    printf("item=%d\r\n",Cmd_MP3[1]);
                    break;
            }
            Cmd_MP3[0] = 0;
        }
	}
}
//==========================================================
//	函数名称：	void RS485_HandlerCb(void)
//
//	函数功能：	通过485总线获取数据处理函数
//
//	入口参数：	void
//
//	返回参数：	无
//
//	说明：		接收通过485总线发送过来的数据请求
//==========================================================
void RS485_HandlerCb(void)
{
    static uint8_t state = 0;
    if(state == 0)
    {
        Rs485_Send(Addr_MP3,Addr_Matrixkey,Matrixkey_Get_value,0,(void*)0);
        state = 1;
    }
    else
    {
        if(!DataHandling_485(Addr_MP3))	//485数据处理
        {
            Cmd_MP3[0] = Rx_Stack.Command;
            Cmd_MP3[1] = Rx_Stack.Data[0];
            if(Cmd_MP3[0])
            {
                printf("get");
            }                
        }
        state = 0;
    }
}





