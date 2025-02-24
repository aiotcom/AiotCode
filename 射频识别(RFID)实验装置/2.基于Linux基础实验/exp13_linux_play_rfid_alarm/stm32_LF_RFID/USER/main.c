#include "stm32f1xx.h"
#include "delay.h"
#include "timer.h"
#include "EM4095.h"
#include "usart.h"
#include "Rs485.h"
/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2019-12-17
*
*	版本： 		V2.0
*
*	说明： 		LF-RFID模块
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/
enum{CARD_ON,CARD_OFF};
void RS485_HandlerCb(void);
uint8_t GetId = 0;
uint8_t CardID[5]={0,0,0,0,0};
uint16_t count = 0,cardstate = CARD_OFF;
int main(void)
{
	HAL_Init();              //初始化HAL库  
	Rs485_Init();    		 //初始化485
	EM4095_Init();			 //初始化EM4095
	UART1_Init(115200);		 //初始化串口1
	TIM2_Init(2000-1,64-1);	 //初始化定时器2(2ms中断)
    UART2_Init(115200);		 //初始化串口1
    TIM3_Init(10000-1,64-1,RS485_HandlerCb);	//初始化定时器中断周期64M/64/10000/ = 100HZ
	while(1)
	{
        HAL_Delay(1);
        if(EM4095_SearchHdr(CardID)){
            count     = 0;
            cardstate = CARD_ON;
            HAL_Delay(50);
            printf("*************************\r\n");
        }
        else{
            if((++count) >= 1000){
                count     = 0;
                cardstate = CARD_OFF;
                CardID[0] = 0;
                CardID[1] = 0;
                CardID[2] = 0;
                CardID[3] = 0;
            }
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
    static uint8_t mark = 0;
    if(!DataHandling_485(Addr_LF_RFID))		//接收数据
    {
        if(Rx_Stack.Src_Adr == Addr_LinuxP){	//来自LF-RFID的数据      
            Rs485_Send(Addr_LF_RFID,Addr_LinuxP,LF_RFID_ID,4,CardID);			//发送ID数据
            printf("requery\r\n");
        }
    }
}




