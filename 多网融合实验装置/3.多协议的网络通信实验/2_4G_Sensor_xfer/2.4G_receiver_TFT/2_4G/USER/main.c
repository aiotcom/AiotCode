#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "string.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "timer.h"
#include "main.h"
#include "24l01.h"

/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2019-03-18
*
*	版本： 		V1.2
*
*	说明： 		2.4G模块程序
*
*	修改记录：
************************************************************
************************************************************
************************************************************
**/
void RS485_HandlerCb(void);
uint8_t NRF_TxBuffer[32] = {0},NRF_RxBuffer[32];//NRF24L01 每次发送最大字节数 是32个字节
void Platform_RGB_LED_Init(void);
uint32_t GetSensorCount = 0; 
#define RF_CHANNEL 0x40 //范围 0x00~0x70 ，收发两端的信首必须一致
int main(void)
{
    uint8_t state = 0;
    HAL_Init();             	    //初始化HAL库  
	Rs485_Init();				    //初始化485
    TIM3_Init(10000-1,640-1,RS485_HandlerCb);//中断频率64M/640/10000=10HZ，中断频率10HZ
	UART1_Init(115200);				//初始化串口1
    USART3_Init(115200);            //printf 打印信息，PB10->TX,PB11->RX,通常只使用，TX功能
    NRF24L01_Init();                //初始化NRF24L01无线芯片
    
    while(NRF24L01_Check()&&1)
    {//nrf24l01硬件连接提示错误
        printf("nrf24l01 check  error\r\n");
        HAL_Delay(1000);
    }
    printf("nrf24l01 check  ok\r\n");
    NRF24L01_RX_Mode(RF_CHANNEL);
    while(1)
    {     
        if(NRF24L01_RxPacket(NRF_RxBuffer)==0)
        {//接收到数据
            printf("nrf rx\r\n");
            Rs485_Send(Addr_2_4G,Addr_LCD,SHT20_All,  4,NRF_RxBuffer); 
        }
        HAL_Delay(1);	               
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
//	说明：		定时器3中断，回调函数，每100ms调用一次
//==========================================================
void RS485_HandlerCb(void)
{

}

